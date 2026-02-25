#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include "bit.h"

int getBit(char *s, unsigned int bitIndex){
    assert(s && bitIndex >= 0);
    unsigned int byte = bitIndex / BITS_PER_BYTE;
    unsigned int indexFromLeft = bitIndex % BITS_PER_BYTE;
    /* 
        Since we split from the highest order bit first, the bit we are interested
        will be the highest order bit, rather than a bit that occurs at the end of the
        number. 
    */
    unsigned int offset = (BITS_PER_BYTE - (indexFromLeft) - 1) % BITS_PER_BYTE;
    unsigned char byteOfInterest = s[byte];
    unsigned int offsetMask = (1 << offset);
    unsigned int maskedByte = (byteOfInterest & offsetMask);
    /*
        The masked byte will still have the bit in its original position, to return
        either 0 or 1, we need to move the bit to the lowest order bit in the number.
    */
    unsigned int bitOnly = maskedByte >> offset;
    return bitOnly;
}

// Bit Comparison Function

int bit_comparisons(const char *a, const char *b) {
    int bits = 0;

    for (int i = 0; ; i++) {
        unsigned char ca = (unsigned char) a[i];
        unsigned char cb = (unsigned char) b[i];

        // Compare whole string including the "\0" byte
        if (ca == cb) {
            bits += BITS_PER_BYTE;
            if (ca == '\0') return bits;
            continue;
        }

        // Stop at the first different bit
        for (int bit = BITS_PER_BYTE - 1; bit >= 0; bit--) {
            unsigned char ba = (ca >> bit) & 1u;
            unsigned char bb = (cb >> bit) & 1u;
            bits++;
            if (ba != bb) return bits;
        }
    }
}
