#ifndef BIT_FUNCTIONS_H
#define BIT_FUNCTIONS_H

// Core bit manipulation
unsigned int SetBit(unsigned int value, int position);
unsigned int ClearBit(unsigned int value, int position);
unsigned int ToggleBit(unsigned int value, int position);
int GetBit(unsigned int value, int position);

// Counting & Finding
int CountBits(unsigned int value);

// Shift Operations
unsigned int ShiftLeft(unsigned int value, int positions);
unsigned int ShiftRight(unsigned int value, int positions);

// Print bits & hex
void PrintBinary(unsigned int value);
void PrintHex(unsigned int value);

#endif