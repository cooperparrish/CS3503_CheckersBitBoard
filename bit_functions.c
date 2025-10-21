#include "bit_functions.h"
#include <stdio.h>

unsigned int SetBit(unsigned int value, int position) {
    if (position < 0 || position >= 32) return value;
    return value | (1U << position);
}

unsigned int ClearBit(unsigned int value, int position) {
    if (position < 0 || position >= 32) return value;
    return value & ~(1U << position);
}

unsigned int ToggleBit(unsigned int value, int position) {
    if (position < 0 || position >= 32) return value;
    return value ^ (1U << position);
}

int GetBit(unsigned int value, int position) {
    if (position < 0 || position >= 32) return 0;
    return (value >> position) & 1U;
}

int CountBits(unsigned int value) {
    int count = 0;
    while (value) {
        count += (value & 1U);
        value >>= 1;
    }
    return count;
}

unsigned int ShiftLeft(unsigned int value, int positions) {
    if (positions < 0 || positions >= 32) return 0;
    return value << positions;
}

unsigned int ShiftRight(unsigned int value, int positions) {
    if (positions < 0 || positions >= 32) return 0;
    return value >> positions;
}

void PrintBinary(unsigned int value) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (value >> i) & 1U);
        if (i % 8 == 0 && i != 0) printf(" ");
    }
    printf("\n");
}

void PrintHex(unsigned int value) {
    printf("0x%08X\n", value);
}
