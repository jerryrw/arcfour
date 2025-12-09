// developer docs for MacOS shared libraries:
// https://developer.apple.com/library/archive/documentation/DeveloperTools/Conceptual/DynamicLibraries/100-Articles/DynamicLibraryDesignGuidelines.html
//
// Helpful article:
// https://yrom.net/blog/2023/04/19/how-to-explicitly-control-exported-symbols-of-dyamic-shared-libraries/

#pragma once
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stddef.h>

// #define EXPORT __atribute__((visibility("default")))
// doing this differently using an external file for MacOS

#define rc4_decrypt(p, x, y) rc4_encrypt(p, x, y) // decryption is the same as encrypting
#define rc4_uninit(x) free(x)

// it is recomended to skip the first 2048 bits of the stream for statistical purposes
#define rc4_skip(x, y)         \
    for (x = 0; x < 2049; x++) \
        (volatile rc4_byte_t) rc4_byte(y); // explicitly tell compiler to not optimize

typedef uint8_t rc4_byte_t;
typedef uint16_t rc4_index_t;

typedef struct rc4_ctx
{
    rc4_byte_t S[256];
    rc4_index_t i, j, k;
} rc4_ctx;

rc4_ctx *rc4_init(rc4_byte_t *, size_t);
rc4_byte_t rc4_byte(rc4_ctx *);
rc4_byte_t *rc4_encrypt(rc4_ctx *, rc4_byte_t *, size_t);
