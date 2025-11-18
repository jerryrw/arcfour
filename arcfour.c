#include "arcfour.h"

Arcfour *rc4init(int8 *key, int16 size)
{
    int16 x;
    int8 temp1, temp2;
    Arcfour *p;
    int32 n; // counter for whitewashing

    p = malloc(sizeof(struct s_arcfour));
    if (p == NULL)
    {
        assert(errno);
    };

    // zero out structure vars
    for (x = 0; x < 256; x++)
    {
        p->S[x] = 0;
    }
    p->i = p->j = p->k = 0;
    temp1 = temp2 = 0;

    for (p->i = 0; p->i < 256; p->i++)
    {
        p->S[p->i] = p->i;
    }
    p->j = 0;

    for (p->i = 0; p->i < 256; p->i++)
    {
        // j := (j+S[i]+key[i mod keylength]) mod 256
        // swap S[i] and S[j]
        p->j = (p->j + p->S[p->i] + key[p->i % size]) % 256;

        temp1 = p->S[p->i];
        p->S[p->i] = p->S[p->j];
        p->S[p->j] = temp1;
    }
    // prep for the actual encryption function
    p->i = p->j = 0;
    rc4witewash(n, p);
    return p;
}

int8 rc4byte(Arcfour *p)
{
    int16 temp1;
    int16 t;

    p->i = (p->i + 1) % 256;
    p->j = (p->j + p->S[p->i]) % 256;

    // swap S[i] and S[j]
    temp1 = p->S[p->i];
    p->S[p->i] = p->S[p->j];
    p->S[p->j] = temp1;

    // t = (S[i] + S[j]) mod 256
    t = (p->S[p->i] + p->S[p->j]) % 256;

    // K = S[t]
    p->k = p->S[t];

    return p->k;
}

int8 *rc4encrypt(Arcfour *p, int8 *cleartext, int16 size)
{
    int8 *ciphertext;
    int16 x;

    ciphertext = (int8 *)malloc(size + 1);

    for (x = 0; x < size; x++)
    {
        ciphertext[x] = cleartext[x] ^ rc4byte(p);
    }
    return ciphertext;
}
