#include <float.h>

#include "analysis.h"

float frequencies[] = {
    8.2,
    1.5, 
    2.8, 
    4.3,
    12.7, 
    2.2, 
    2.0, 
    6.1, 
    7.0,
    0.16, 
    0.77,
    4.0, 
    2.4, 
    6.7, 
    7.5, 
    1.9,
    0.12, 
    6.0, 
    6.3, 
    9.1,
    2.8,
    0.9,
    2.4,
    0.15,
    2.0,
    0.074 
};

static int get_letter_count(char *s) {
    int lc = 0;
    while(*s != '\0') { 
        if(*s > 64 && *s < 91)
            lc++;
        else if(*s > 96 && *s < 123)
            lc++;

        s++;
    }

    return lc;
}

static void get_expected_counts(char *s, float *expected_counts) {
    int letter_count = get_letter_count(s);

    for(int i = 0; i < 26; i++) {
        expected_counts[i] = (frequencies[i] / 100) * letter_count;
    }
}

static void get_observed_counts(char *s, int *observed_counts) {
    int index = 0;
    while(*s != '\0') { 
        if(*s > 64 && *s < 91)
            observed_counts[*s - 65]++;
        else if(*s > 96 && *s < 123)
            observed_counts[*s - 97]++;

        s++;
    }
}

static float chi_squared_internal(float *expected_counts, int *observed_counts, int index, int shift) {
    return ((observed_counts[index] - expected_counts[(index - shift + 26) % 26]) * (observed_counts[index] - expected_counts[(index - shift + 26) % 26])) / expected_counts[(index - shift + 26) % 26];
}

void chi_squared(char *s, float *output) {
    float expected_counts[26];
    int observed_counts[26] = {0};

    get_expected_counts(s, expected_counts);
    get_observed_counts(s, observed_counts);

    for(int i = 0; i < 26; i++) {
        float result = 0;

        for(int j = 0; j < 26; j++) {
            result += chi_squared_internal(expected_counts, observed_counts, j, i);
        }

        output[i] = result;
    }
}