
#include "arcfour.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FLUSH fflush(stdout);

int main(void)
{
    rc4_ctx *ctx;
    size_t keysize, textsize;
    rc4_byte_t *key, *plaintext, *encrypted, *decrypted;

    // zero out the pointers to initial values stops compiler warnings
    key = plaintext = encrypted = decrypted = 0;
    plaintext = key;
    keysize = textsize = 0;

    // set up the key
    key = (rc4_byte_t *)"tomatoes";
    keysize = strlen((char *)key);

    // set up sample plaintext input
    plaintext = (rc4_byte_t *)"Shall I compare thee to a summer's day?";
    textsize = strlen((char *)plaintext);

    printf("Initializing encryption...");
    FLUSH;
    ctx = rc4_init(key, keysize); // sets up the context with the key
    printf("done\n");
    FLUSH
    printf("Plaintext ->");
    FLUSH;
    printf("'%s'\n", plaintext);

    printf("Encrypting...");
    FLUSH;
    encrypted = rc4_encrypt(ctx, plaintext, textsize); // the actual encryption call
    printf("done\nCiphertext->");
    FLUSH;
    print_hex(encrypted, textsize);

    printf("Initializing decryption...");
    FLUSH;
    ctx = rc4_init(key, keysize); // re-initialize the context for decryption
    printf("done\n");

    printf("Decrypting...");
    FLUSH;
    decrypted = rc4_encrypt(ctx, encrypted, textsize);
    printf("done\nPlaintext->");
    printf("'%s'\n", decrypted);

    // generate a random number
    size_t num_bytes = 256;
    rc4_byte_t *random_buffer;
    random_buffer = (rc4_byte_t *)malloc(num_bytes * sizeof(rc4_byte_t));
    key = (rc4_byte_t *)"hello";
    ctx = rc4_init(key, strlen((const char *)key));
    for (int i = 0; i < num_bytes; i++)
    {
        random_buffer[i] = rc4_byte(ctx);
    }
    printf("Random Data from key->");
    print_hex(random_buffer, num_bytes);
    memset(random_buffer, 0, num_bytes); // zero the buffer
    free(random_buffer);
    return 0;
}