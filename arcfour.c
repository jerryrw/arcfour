#include "arcfour.h"

rc4_ctx *rc4_init(rc4_byte_t *key, size_t size)
/* Algorythm for the key init function

for i from 0 to 255
    S[i] := i
endfor
j := 0
for i from 0 to 255
    j := (j + S[i] + key[i mod keylength]) mod 256
    swap values of S[i] and S[j]
endfor
*/
{
    rc4_index_t x;
    rc4_byte_t temp1, temp2;
    rc4_ctx *ctx;
    uint32_t n; // counter for whitewashing

    ctx = malloc(sizeof(rc4_ctx));
    if (ctx == NULL)
    {
        assert(errno);
    };

    // zero out the S box, and other struc vars
    for (x = 0; x < 256; x++)
    {
        ctx->S[x] = 0;
    }
    ctx->i = ctx->j = ctx->k = 0;
    temp1 = temp2 = 0;

    for (ctx->i = 0; ctx->i < 256; ctx->i++)
    {
        ctx->S[ctx->i] = ctx->i;
    }
    ctx->j = 0;

    for (ctx->i = 0; ctx->i < 256; ctx->i++)
    {
        // j := (j+S[i]+key[i mod keylength]) mod 256
        // swap S[i] and S[j]
        ctx->j = (ctx->j + ctx->S[ctx->i] + key[ctx->i % size]) % 256;

        temp1 = ctx->S[ctx->i];
        ctx->S[ctx->i] = ctx->S[ctx->j];
        ctx->S[ctx->j] = temp1;
    }
    // prep for the actual encryption function
    ctx->i = ctx->j = 0;
    rc4_skip(n, ctx); // throw away the first few bytes of the stream
    return ctx;
}

rc4_byte_t rc4_byte(rc4_ctx *ctx)
/* Algorithm for generating the key stream

i := 0
j := 0
while GeneratingOutput:
    i := (i + 1) mod 256
    j := (j + S[i]) mod 256
    swap values of S[i] and S[j]
    t := (S[i] + S[j]) mod 256
    K := S[t]
    output K
endwhile
*/

{
    rc4_index_t temp1;
    rc4_index_t t;

    ctx->i = (ctx->i + 1) % 256;
    ctx->j = (ctx->j + ctx->S[ctx->i]) % 256;

    // swap S[i] and S[j]
    temp1 = ctx->S[ctx->i];
    ctx->S[ctx->i] = ctx->S[ctx->j];
    ctx->S[ctx->j] = temp1;

    // t = (S[i] + S[j]) mod 256
    t = (ctx->S[ctx->i] + ctx->S[ctx->j]) % 256;

    // K = S[t]
    ctx->k = ctx->S[t];

    return ctx->k;
}

rc4_byte_t *rc4_encrypt(rc4_ctx *ctx, rc4_byte_t *cleartext, size_t size)
/* The actual encryption
uses rc4byte to get a byte of key stream and XOR it
with the cleartext producing a ciphertext byte
Loops over the entire length of the cleartext
*/

{
    // variables in this function are named for encryption
    // but the RC4 cipher uses the same function for decryption
    rc4_byte_t *ciphertext;
    rc4_index_t x;

    ciphertext = (rc4_byte_t *)malloc(size + 1);

    for (x = 0; x < size; x++)
    {
        ciphertext[x] = cleartext[x] ^ rc4_byte(ctx);
    }
    return ciphertext;
}
