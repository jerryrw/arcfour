
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
    // different types need to be initialized seperately
    key = plaintext = encrypted = decrypted = 0;
    keysize = textsize = 0;
    ctx = 0;

    // set up the key
    key = (rc4_byte_t *)"tomatoes";
    keysize = strlen((char *)key);

    // set up sample plaintext input
    plaintext = (rc4_byte_t *)"Shall I compare thee to a summer's day?";
    textsize = strlen((char *)plaintext);

    printf("Initializing encryption...");
    rc4_free(ctx); // need this before any init to stop memory leak
    ctx = NULL;
    ctx = rc4_init(key, keysize); // sets up the context with the key
    printf("done\nPlaintext ->'%s'\n", plaintext);

    printf("Encrypting...");
    encrypted = rc4_encrypt(ctx, plaintext, textsize); // the actual encryption call
    printf("done\nCiphertext->");
    print_hex(encrypted, textsize);

    printf("Initializing decryption...");
    rc4_free(ctx); // need this before any init to stop memory leak
    ctx = NULL;
    ctx = rc4_init(key, keysize); // re-initialize the context for decryption
    printf("done\n");

    printf("Decrypting...");
    decrypted = rc4_encrypt(ctx, encrypted, textsize);
    printf("done\nPlaintext->'%s'\n", decrypted);
    rc4_free(ctx); // need this before any init to stop memory leak
    ctx = NULL;
    // use at the end of this oeration helps ensure that
    // next init call does not get a mamory leak
    free(encrypted);
    free(decrypted);

    // generate a random number (just keystream data)
    size_t num_bytes = 256;
    rc4_byte_t *random_buffer;
    random_buffer = (rc4_byte_t *)malloc(num_bytes * sizeof(rc4_byte_t));
    key = (rc4_byte_t *)"hello";
    rc4_free(ctx); // need this before any init to stop memory leak
    ctx = NULL;
    ctx = rc4_init(key, strlen((const char *)key));
    for (int i = 0; i < num_bytes; i++)
    {
        random_buffer[i] = rc4_byte(ctx);
    }
    printf("Random Data from key->");
    print_hex(random_buffer, num_bytes);
    memset(random_buffer, 0, num_bytes); // zero the buffer
    free(random_buffer);
    rc4_free(ctx); // need this before any init to stop memory leak
    ctx = NULL;
    // use at the end of this oeration helps ensure that
    // next init call does not get a mamory leak
    return 0;
}