#include "arcfour.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * RC4 (Rivest Cipher 4) Implementation
 * Exact implementation from RFC 6229
 */

/*
 * print_hex - prints 8 bit binary data in hex string format
 * to stdout
 * */
void print_hex(unsigned char *data, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        printf("%02x ", data[i]);
    }
    printf("\n");
}
/*
 * rc4_init - Initialize RC4 context with a key
 * Key Scheduling Algorithm (KSA)
 */
rc4_ctx *rc4_init(rc4_byte_t *key, size_t keylen)
{
    unsigned int i, j;
    rc4_byte_t temp;
    rc4_ctx *ctx;

    ctx = (rc4_ctx *)malloc(sizeof(rc4_ctx));
    if (ctx == NULL)
    {
        return NULL;
    }

    /* Initialize S-box */
    for (i = 0; i < 256; i++)
    {
        ctx->S[i] = (rc4_byte_t)i;
    }

    /* KSA main loop */
    j = 0;
    for (i = 0; i < 256; i++)
    {
        j = (j + ctx->S[i] + key[i % keylen]) % 256;

        /* Swap S[i] and S[j] */
        temp = ctx->S[i];
        ctx->S[i] = ctx->S[j];
        ctx->S[j] = temp;
    }

    /* Initialize PRGA indices */
    ctx->i = 0;
    ctx->j = 0;

    // this works for use but does not pass one test due to the nature of the test
    // for (int x = 0; x < 2049; x++)
    //     (volatile rc4_byte_t) rc4_byte(ctx); // explicitly tell compiler to not optimize

    return ctx;
}

/*
 * rc4_byte - Generate next keystream byte
 * Pseudo-Random Generation Algorithm (PRGA)
 */
rc4_byte_t rc4_byte(rc4_ctx *ctx)
{
    rc4_byte_t temp;
    unsigned int t;

    /* Increment i (with wrapping) */
    ctx->i = (ctx->i + 1) % 256;

    /* Add S[i] to j (with wrapping) */
    ctx->j = (ctx->j + ctx->S[ctx->i]) % 256;

    /* Swap S[i] and S[j] */
    temp = ctx->S[ctx->i];
    ctx->S[ctx->i] = ctx->S[ctx->j];
    ctx->S[ctx->j] = temp;

    /* Generate keystream byte */
    t = (ctx->S[ctx->i] + ctx->S[ctx->j]) % 256;

    return ctx->S[t];
}

/*
 * rc4_encrypt - Encrypt data with RC4
 */
rc4_byte_t *rc4_encrypt(rc4_ctx *ctx, rc4_byte_t *plaintext, size_t size)
{
    size_t x;
    rc4_byte_t *ciphertext;

    ciphertext = (rc4_byte_t *)malloc(size + 1);
    if (ciphertext == NULL)
    {
        return NULL;
    }

    for (x = 0; x < size; x++)
    {
        ciphertext[x] = plaintext[x] ^ rc4_byte(ctx);
    }

    ciphertext[size] = '\0';
    return ciphertext;
}

/*
 * rc4_free - Free RC4 context
 */
void rc4_free(rc4_ctx *ctx)
{
    if (ctx != NULL)
    {
        free(ctx);
    }
}

int rc4_encrypt_file(const char *inpath, const char *outpath, rc4_byte_t *key, size_t keylen)
{
    FILE *in = NULL, *out = NULL;
    rc4_ctx *ctx = NULL;
    unsigned char buf[4096];
    size_t n;

    if (inpath == NULL || outpath == NULL || key == NULL || keylen == 0)
        return -1;

    in = fopen(inpath, "rb");
    if (in == NULL)
        return -1;

    out = fopen(outpath, "wb");
    if (out == NULL)
    {
        fclose(in);
        return -1;
    }

    ctx = rc4_init(key, keylen);
    if (ctx == NULL)
    {
        fclose(in);
        fclose(out);
        return -1;
    }

    while ((n = fread(buf, 1, sizeof(buf), in)) > 0)
    {
        for (size_t i = 0; i < n; i++)
            buf[i] ^= rc4_byte(ctx);

        if (fwrite(buf, 1, n, out) != n)
        {
            rc4_free(ctx);
            fclose(in);
            fclose(out);
            return -1;
        }
    }

    rc4_free(ctx);
    fclose(in);
    fclose(out);
    return 0;
}