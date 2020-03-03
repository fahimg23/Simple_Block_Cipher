#include <stdint.h>

#ifndef ENCRYPT_H
#define ENCRYPT_H

/*
Implements simple ECB (electronic code book) type 64 bit block cipher
*/

#define CEIL(a,b) ((a / b) + ((a % b) != 0)) // ceil of a/b
#define BLOCK_SIZE_IN_BYTES 8 // KEY SIZE IN BYTES

typedef struct plain_text {
  char* ptx_buf;
  size_t size_in_bytes;
} plain_text;

typedef struct cipher_text {
  char* ctx_buf;
  size_t size_in_bytes;
} cipher_text;

uint64_t generate_rand_key64();
cipher_text* encrypt(plain_text* ptx, uint64_t key);
plain_text* decrypt(cipher_text* ptx, uint64_t key);

#endif
