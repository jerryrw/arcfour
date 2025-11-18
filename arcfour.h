#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

// #define EXPORT __atribute__((visibility("default")))
#define rc4decrypt(p, x, y) rc4encrypt(p, x, y)
#define rc4uninit(x) free(x)
#define MS 500
#define rc4witewash(x, y)                \
    for (x = 0; x < (MS * 1000000); x++) \
        (volatile int8) rc4byte(y);

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

struct s_arcfour
{
    int8 S[256];
    int16 i, j, k;
};
typedef struct s_arcfour Arcfour;

Arcfour *rc4init(int8 *, int16);
int8 rc4byte(Arcfour *);
int8 *rc4encrypt(Arcfour *, int8 *, int16);
