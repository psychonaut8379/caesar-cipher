#include <stdbool.h>
#include <stdint.h>

#include "cipher.h"

void encrypt(char *plaintext, char *ciphertext, int key, uint8_t flags) {
    char *c = plaintext;
    while(*c != '\0') {
        if(*c > 64 && *c < 91) {
            *ciphertext = SHIFT_UPPERCASE(*c, key);
            ciphertext++;
        } else if(*c > 96 && *c < 123) {
            if(flags & CASE_SENSITIVITY)
                *ciphertext = SHIFT_LOWERCASE(*c, key);
            else 
                *ciphertext = SHIFT_UPPERCASE((*c) - 32, key);

            ciphertext++;
        } else if(flags & FOREIGN_CHARS) {
            *ciphertext = *c;
            ciphertext++;
        }

        c++;
    }
}

void decrypt(char *ciphertext, char *plaintext, int key) {
    char *c = ciphertext;
    while(*c != '\0') {
        if(*c > 64 && *c < 91) {
            *plaintext = SHIFT_UPPERCASE(*c, -key);
            plaintext++;
        } else if(*c > 96 && *c < 123) {
            *plaintext = SHIFT_LOWERCASE(*c, -key);
            plaintext++;
        } else {
            *plaintext = *c;
            plaintext++;
        }
        
        c++;
    }
}