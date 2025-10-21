# BitBoard Checkers Game

A Checkers game implementation using bitboard data structures and bit manipulation.

## Author
[Cooper Parrish]
CS 3503 - Computer Organization & Architecture

## Project Overview
This project demonstrates efficient bit manipulation techniques by implementing a checkers game engine using bitboards, where each bit in a 64-bit integer represents a board square.

## Files Included
- `main.c` - Main game loop and user interface
- `checkers.c` - Core game logic and bitboard operations
- `checkers.h` - Game structure and function declarations
- `bit_functions.c` - Bit manipulation library 
- `bit_functions.h` - Bit manipulation function declarations
- `MakeFile` - Build configuration
- `README.md` - This file

  
<img width="1919" height="1033" alt="Screenshot 2025-10-20 231858" src="https://github.com/user-attachments/assets/0c6c3fec-b1f5-4995-b41c-a1cb7392376e" />

## Gameplay Instructions 
Enter moves as: "from_row from_col to_row to_col"

### Example Moves 
5 0 4 1 -> Move piece from (5,0) to (4,1)
5 2 3 4 -> Jump opponent piece (if at 4,3)

### Legend
r/R = Red (regular/king) | b/B = Black (regular/king) | . = Light square | = Empty
