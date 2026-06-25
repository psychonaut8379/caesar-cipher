#ifndef CIPHER_H
#define CIPHER_H

#include <stdint.h>

#define SHIFT_UPPERCASE(c, k) ((((((c) - 'A' + (k)) % 26) + 26) % 26) + 'A')
#define SHIFT_LOWERCASE(c, k) ((((((c) - 'a' + (k)) % 26) + 26) % 26) + 'a')

#define FOREIGN_CHARS (1 << 0)
#define CASE_SENSITIVITY (1 << 1)

void encrypt(char *plaintext, char *ciphertext, int key, uint8_t cipher_flags);
void decrypt(char *ciphertext, char *plaintext, int key);

#endif