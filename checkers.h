#ifndef CHECKERS_H
#define CHECKERS_H

typedef struct {
    unsigned long long red_pieces;   // Regular red pieces
    unsigned long long red_kings;    // Red kings
    unsigned long long black_pieces; // Regular black pieces
    unsigned long long black_kings;  // Black kings
    int current_player;              // 0 = Red, 1 = Black
} Game;

// Core game functions
void init_game(Game* game);
void print_board(Game* game);
int is_valid_move(Game* game, int fr, int fc, int tr, int tc);
void make_move(Game* game, int fr, int fc, int tr, int tc);
int check_win(Game* game);

#endif