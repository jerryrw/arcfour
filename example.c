
#include "arcfour.h"

#define F fflush(stdout);

int main(void);

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
    Arcfour *rc4;
    int16 skey, stext;
    int8 *key, *from, *encrypted, *decrypted;

    key = from = encrypted = decrypted = 0;
    from = key;

    skey = stext = 0;

    key = (int8 *)"tomatoes";
    skey = strlen((char *)key);
    from = (int8 *)"Shall I compare thee to a summer's day?";
    stext = strlen((char *)from);
    printf("Initializing encryption...");
    F;

    rc4 = rc4init(key, skey);
    printf("done\n");

    printf("'%s'\n ->", from);
    encrypted = rc4encrypt(rc4, from, stext);
    printbin(encrypted, stext);
    rc4uninit(rc4);

    rc4 = rc4init(key, skey);
    decrypted = rc4decrypt(rc4, encrypted, stext);
    printf("\n'%s'\n ->", decrypted);

    return 0;
}