#ifndef ARCFOUR_H
#define ARCFOUR_H

#include <stddef.h>
#include <stdint.h>

// test git
/* Type definitions for RC4 */
typedef unsigned char rc4_byte_t;

// used to skip the first 2048 bytes of output for statistical purposes
#define rc4_skip(x, y)       \
  for (x = 0; x < 2049; x++) \
    (volatile rc4_byte_t)    \
        rc4_byte(y);  // explicitly tell compiler to not optimize

/* RC4 context structure - maintains state between operations */
typedef struct {
  rc4_byte_t S[256]; /* S-box (substitution box) - permutation of 0-255 */
  rc4_byte_t i;      /* Index i for PRGA (MUST be 8-bit) */
  rc4_byte_t j;      /* Index j for PRGA (MUST be 8-bit) */
} rc4_ctx;

/* Function prototypes */
/*
 * @brief Prints the hexadecimal representation of a byte array.
 *
 * @param data Pointer to the raw byte data to print.
 * @param len The number of bytes in the data buffer.
 */
void print_hex(unsigned char* data, size_t len);
/*
 * @brief Initializes the RC4 context structure (S-box and initial state).
 *
 * This function sets up the substitution box (S) using the provided key.
 * The resulting pointer must be passed to rc4_free() when done.
 *
 * @param key Pointer to the raw encryption key bytes.
 * @param size Length of the key in bytes.
 * @return rc4_ctx* A pointer to the newly initialized RC4 context structure, or
 * NULL if initialization fails.
 */
rc4_ctx* rc4_init(rc4_byte_t* key, size_t size);
/*
 * @brief Generates and returns one keystream byte using the current context
 * state (PRGA).
 *
 * This function updates the internal state of the RC4 context structure.
 *
 * @param ctx Pointer to the initialized RC4 context.
 * @return rc4_byte_t The next pseudo-random keystream byte.
 */
rc4_byte_t rc4_byte(rc4_ctx* ctx);
/*
 * @brief Encrypts or decrypts a plaintext buffer using the RC4 stream cipher.
 *
 * Note: RC4 is symmetric; encryption and decryption use the same keystream. The
 * function allocates memory for the output ciphertext/plaintext which must be
 * freed by the caller using rc4_free().
 *
 * @param ctx Pointer to the initialized RC4 context.
 * @param plaintext Pointer to the input data buffer (plaintext or ciphertext).
 * @param size The number of bytes in the input buffer.
 * @return rc4_byte_t* A pointer to the newly allocated output buffer containing
 * the encrypted/decrypted data.
 */
rc4_byte_t* rc4_encrypt(rc4_ctx* ctx, rc4_byte_t* plaintext, size_t size);
/*
 * @brief Frees the memory allocated for an RC4 context structure.
 *
 * Must be called after rc4_init() returns a pointer to clean up resources.
 *
 * @param ctx The RC4 context structure to free.
 */
void rc4_free(rc4_ctx* ctx);
/*
 * @brief Encrypts or decrypts an entire file using the RC4 stream cipher.
 *
 * Reads data from inpath, processes it with the key, and writes the result to
 * outpath. The function returns 0 on success, and a negative error code
 * otherwise.
 *
 * @param inpath Path to the input (plaintext or ciphertext) file.
 * @param outpath Path where the encrypted/decrypted output will be written.
 * @param key Pointer to the raw encryption key bytes.
 * @param keylen Length of the key in bytes.
 * @return int Returns 0 on success, negative error code otherwise.
 */
int rc4_encrypt_file(const char* inpath, const char* outpath, rc4_byte_t* key,
                     size_t keylen);

#endif /* ARCFOUR_H */