
#include "arcfour.h"

#define FLUSH fflush(stdout);

void printbin(rc4_byte_t *input, const rc4_index_t size)
{
    rc4_index_t i;
    rc4_byte_t *p;

    assert(size > 0);

    for (i = size, p = input; i; i--, p++)
    {
        if (!(i % 2))
            printf(" ");
        printf("%02X", *p);
    }
    printf("\n");
    return;
}

int main(void)
{
    rc4_ctx *rc4context;
    rc4_index_t keysize, textsize;
    rc4_byte_t *key, *cleartext, *encrypted, *decrypted;

    // zero out the pointers to initial values stops compiler warnings
    key = cleartext = encrypted = decrypted = 0;
    cleartext = key;
    keysize = textsize = 0;

    // set up the key
    key = (rc4_byte_t *)"tomatoes";
    keysize = strlen((char *)key);
    // set up sample plaintext input
    cleartext = (rc4_byte_t *)"Shall I compare thee to a summer's day?";
    textsize = strlen((char *)cleartext);

    printf("Initializing encryption...");
    FLUSH;
    rc4context = rc4_init(key, keysize); // sets up the context with the key
    printf("done\n");

    printf("Plaintext ->");
    FLUSH;
    printf("'%s'\n", cleartext);

    printf("Encrypting...");
    FLUSH;
    encrypted = rc4_encrypt(rc4context, cleartext, textsize); // the actual encryption call
    printf("done\nCiphertext->");
    FLUSH;
    printbin(encrypted, textsize);

    rc4_uninit(rc4context); // reset the context to be able to decrypt

    printf("Initializing decryption...");
    FLUSH;
    rc4context = rc4_init(key, keysize); // re-initialize the context for decryption
    printf("done\n");

    printf("Decrypting...");
    FLUSH;
    decrypted = rc4_decrypt(rc4context, encrypted, textsize);
    printf("done\n");
    printf("'%s'\n", decrypted);

    return 0;
}