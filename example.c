/**
 * @brief Main function demonstrating RC4 usage for encryption and decryption.
 *
 * This example demonstrates the full lifecycle: key setup -> initialization ->
 * encryption -> re-initialization -> decryption -> random data generation.
 * Note the explicit calls to rc4_free() after each context use to prevent
 * memory leaks, which is critical in resource management for this library.
 */
#include "arcfour.h"

int main(void) {
  rc4_ctx* ctx;
  size_t keysize, textsize;
  rc4_byte_t *key, *plaintext, *encrypted, *decrypted;

  // Initialize pointers and variables to NULL/zero to suppress compiler
  // warnings.
  key = plaintext = encrypted = decrypted = 0;
  keysize = textsize = 0;
  ctx = NULL;

  // --- Step 1: Setup Key and Context ---
  key = (rc4_byte_t*)"tomatoes";
  keysize = strlen((char*)key);

  printf("Initializing encryption...");
  // Must free any existing context before creating a new one.
  if (ctx != NULL) rc4_free(ctx);
  ctx = rc4_init(key, keysize);  // Sets up the context state using the KSA.
  printf("done\nPlaintext ->'%s'\n", plaintext);

  // --- Step 2: Encryption ---
  printf("Encrypting...");
  encrypted =
      rc4_encrypt(ctx, plaintext,
                  textsize);  // Generates keystream and XORs it with plaintext.
  printf("done\nCiphertext->");
  print_hex(encrypted, textsize);

  // --- Step 3: Decryption (Symmetric Property Check) ---
  printf("\nInitializing decryption...");
  if (ctx != NULL) rc4_free(ctx);  // Free old context.
  ctx = rc4_init(
      key, keysize);  // Re-initialize the context state for the second pass.
  printf("done\n");

  printf("Decrypting...");
  // Decryption is mathematically identical to encryption in RC4 (XOR property).
  decrypted = rc4_encrypt(ctx, encrypted, textsize);
  printf("done\nPlaintext->'%s'\n", decrypted);
  rc4_free(ctx);  // Clean up context.

  // --- Step 4: Random Data Generation (Testing state persistence) ---
  size_t num_bytes = 256;
  rc4_byte_t* random_buffer;

  // Use a simple key to generate random-like data for testing purposes.
  key = (rc4_byte_t*)"hello";
  if (ctx != NULL) rc4_free(ctx);  // Clean up previous context.
  ctx = rc4_init(key, strlen((const char*)key));

  random_buffer = (rc4_byte_t*)malloc(num_bytes * sizeof(rc4_byte_t));
  for (int i = 0; i < num_bytes; i++) {
    // Each call generates a new byte, advancing the internal state of 'ctx'.
    random_buffer[i] = rc4_byte(ctx);
  }
  printf("Random Data from key->");
  print_hex(random_buffer, num_bytes);

  // Cleanup resources
  rc4_free(ctx);  // Final context cleanup.
  free(encrypted);
  free(decrypted);
  free(random_buffer);

  return 0;
}