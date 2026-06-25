#include <float.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "cipher.h"
#include "analysis.h"

#define ENCRYPTION (1 << 2)
#define DECRYPTION (1 << 3)
#define BRUTEFORCE (1 << 4)
#define CHI_SQUARED (1 << 5)

void bruteforce(char *ciphertext) {
    char buf[2048];

    for(int i = 0; i < 26; i++) {
        decrypt(ciphertext, buf, i);
        printf("k = %2i -- %s\n", i, buf);
    }
}

void print_chi_squared_result(char *ciphertext, float *chi_squared_result) {
    float best_result = FLT_MAX;
    int best_key;

    char buf[2048];

    for(int i = 0; i < 26; i++) {

        if(best_result > chi_squared_result[i]) {
            best_result = chi_squared_result[i];
            best_key = i;
        }

        decrypt(ciphertext, buf, i);
        printf("%.2f -- key: %i -- %s\n", chi_squared_result[i], i, buf);
    }


    decrypt(ciphertext, buf, best_key);
    printf("\nMost Likely Key:\n\t%.2f -- key: %i -- %s\n", chi_squared_result[best_key], best_key, buf);

}

int main(int argc, char **argv) {
    uint8_t flags = 0;
    int option;
    int key;
    while((option = getopt(argc, argv, "hfcedk:ba")) != -1) {
        switch(option) {
            case 'h':
            break;
            case 'f':
            flags |= FOREIGN_CHARS;
            break;
            case 'c':
            flags |= CASE_SENSITIVITY;
            break;
            case 'e':
            flags |= ENCRYPTION;
            break;
            case 'd':
            flags |= DECRYPTION;
            break;
            case 'k':
            key = (int)strtol(optarg, NULL, 10);    
            break;
            case 'b':
            flags |= BRUTEFORCE;
            break;
            case 'a':
            flags |= CHI_SQUARED;
            break;
        }
    }

    char *input;

    if(optind < argc) {
        input = argv[optind];
    }

    char output[2048];
    float chi_squared_output[26];

    if(flags & ENCRYPTION) {
        encrypt(input, output, key, flags);
        printf("%s\n", output);

        goto exit;
    }

    if(flags & DECRYPTION) {
        decrypt(input, output, key);
        printf("%s\n", output);

        goto exit;
    }

    if(flags & BRUTEFORCE) {
        bruteforce(input);
        goto exit;
    }

    if(flags & CHI_SQUARED) {
        chi_squared(input, chi_squared_output);
        print_chi_squared_result(input, chi_squared_output); }

exit:
    return 0;
}
