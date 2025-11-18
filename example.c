
#include "arcfour.h"

#define FLUSH fflush(stdout);

// int main(void);

void printbin(int8 *input, const int16 size)
{
    int16 i;
    int8 *p;

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
    Arcfour *rc4context;
    int16 keysize, textsize;
    int8 *key, *cleartext, *encrypted, *decrypted;

    // zero out the pointers to initial values stops compiler warnings
    key = cleartext = encrypted = decrypted = 0;
    cleartext = key;
    keysize = textsize = 0;

    // set up the key
    key = (int8 *)"tomatoes";
    keysize = strlen((char *)key);
    // set up sample plaintext input
    cleartext = (int8 *)"Shall I compare thee to a summer's day?";
    textsize = strlen((char *)cleartext);

    printf("Initializing encryption...");
    FLUSH;
    rc4context = rc4init(key, keysize); // sets up the context with the key
    printf("done\n");

    printf("Plaintext ->");
    FLUSH;
    printf("'%s'\n", cleartext);

    printf("Encrypting...");
    FLUSH;
    encrypted = rc4encrypt(rc4context, cleartext, textsize); // the actual encryption call
    printf("done\nCiphertext->");
    FLUSH;
    printbin(encrypted, textsize);

    rc4uninit(rc4context); // reset the context to be able to decrypt

    printf("Initializing decryption...");
    FLUSH;
    rc4context = rc4init(key, keysize); // re-initialize the context for decryption
    printf("done\n");

    printf("Decrypting...");
    FLUSH;
    decrypted = rc4decrypt(rc4context, encrypted, textsize);
    printf("done\n");
    printf("'%s'\n", decrypted);

    return 0;
}