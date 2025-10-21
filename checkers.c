#include "checkers.h"
#include <stdio.h>
#include <stdlib.h>

// Helper to get bit index (0-63) from row/col
// Returns -1 if not a dark square
static int get_pos(int r, int c) {
    if (r < 0 || r > 7 || c < 0 || c > 7) return -1;
    if ((r + c) % 2 == 0) return -1; // Light square
    return r * 8 + c;
}

void init_game(Game* game) {
    game->red_pieces = 0;
    game->red_kings = 0;
    game->black_pieces = 0;
    game->black_kings = 0;
    game->current_player = 0; // Red starts

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            int pos = get_pos(r, c);
            if (pos != -1) {
                // Black on top 3 rows (0,1,2)
                if (r < 3) game->black_pieces |= (1ULL << pos);
                // Red on bottom 3 rows (5,6,7)
                if (r > 4) game->red_pieces |= (1ULL << pos);
            }
        }
    }
}

void print_board(Game* game) {
    printf("\n   0 1 2 3 4 5 6 7\n");
    printf("  -----------------\n");
    for (int r = 0; r < 8; r++) {
        printf("%d |", r);
        for (int c = 0; c < 8; c++) {
            int pos = r * 8 + c;
            unsigned long long bit = 1ULL << pos;

            if ((r + c) % 2 == 0) {
                printf(" ."); // Light square
            }
            else {
                if (game->red_pieces & bit) printf(" r");
                else if (game->red_kings & bit) printf(" R");
                else if (game->black_pieces & bit) printf(" b");
                else if (game->black_kings & bit) printf(" B");
                else printf("  "); // Empty dark square
            }
        }
        printf(" |\n");
    }
    printf("  -----------------\n");
}

int is_valid_move(Game* game, int fr, int fc, int tr, int tc) {
    int from = get_pos(fr, fc);
    int to = get_pos(tr, tc);

    // Basic validation
    if (from == -1 || to == -1) return 0; // Not dark squares

    unsigned long long all_red = game->red_pieces | game->red_kings;
    unsigned long long all_black = game->black_pieces | game->black_kings;
    unsigned long long occupied = all_red | all_black;

    // Square must be empty
    if (occupied & (1ULL << to)) return 0;

    // Check current player owns the piece
    int is_red = (game->current_player == 0);
    unsigned long long own_pieces = is_red ? all_red : all_black;
    if (!(own_pieces & (1ULL << from))) return 0;

    // Check piece type (king or regular)
    int is_king = is_red ? (game->red_kings & (1ULL << from))
        : (game->black_kings & (1ULL << from));

    int dr = tr - fr;
    int dc = tc - fc;

    // Simple Move (distance 1)
    if (abs(dr) == 1 && abs(dc) == 1) {
        if (!is_king) {
            // Red moves UP (-), Black moves DOWN (+)
            if (is_red && dr > 0) return 0;
            if (!is_red && dr < 0) return 0;
        }
        return 1; // Valid simple move
    }

    // Jump Move (distance 2)
    if (abs(dr) == 2 && abs(dc) == 2) {
        if (!is_king) {
            if (is_red && dr > 0) return 0;
            if (!is_red && dr < 0) return 0;
        }

        // Check jumped piece
        int mid_r = (fr + tr) / 2;
        int mid_c = (fc + tc) / 2;
        int mid_pos = get_pos(mid_r, mid_c);  // FIXED: use get_pos consistently
        if (mid_pos == -1) return 0;

        unsigned long long opponent = is_red ? all_black : all_red;

        if (opponent & (1ULL << mid_pos)) {
            return 2; // Valid jump
        }
    }

    return 0; // Invalid
}

void make_move(Game* game, int fr, int fc, int tr, int tc) {
    int from = get_pos(fr, fc);
    int to = get_pos(tr, tc);    

    if (from == -1 || to == -1) return; 

    unsigned long long from_bit = 1ULL << from;
    unsigned long long to_bit = 1ULL << to;
    int is_red = (game->current_player == 0);

    // Move the piece
    if (is_red) {
        if (game->red_pieces & from_bit) {
            game->red_pieces &= ~from_bit;
            game->red_pieces |= to_bit;
        }
        else {
            game->red_kings &= ~from_bit;
            game->red_kings |= to_bit;
        }
    }
    else {
        if (game->black_pieces & from_bit) {
            game->black_pieces &= ~from_bit;
            game->black_pieces |= to_bit;
        }
        else {
            game->black_kings &= ~from_bit;
            game->black_kings |= to_bit;
        }
    }

    // Handle captures
    if (abs(tr - fr) == 2) {
        int mid_r = (fr + tr) / 2;
        int mid_c = (fc + tc) / 2;
        int mid_pos = get_pos(mid_r, mid_c);  
        if (mid_pos != -1) {
            unsigned long long mid_bit = 1ULL << mid_pos;
            
            // Remove opponent piece

            game->red_pieces &= ~mid_bit;
            game->red_kings &= ~mid_bit;
            game->black_pieces &= ~mid_bit;
            game->black_kings &= ~mid_bit;
        }
    }

    // Handle Promotion
    if (is_red && tr == 0) {
        if (game->red_pieces & to_bit) {
            game->red_pieces &= ~to_bit;
            game->red_kings |= to_bit;
        }
    }
    else if (!is_red && tr == 7) {
        if (game->black_pieces & to_bit) {
            game->black_pieces &= ~to_bit;
            game->black_kings |= to_bit;
        }
    }

    // Switch turns
    game->current_player = 1 - game->current_player;
}

int check_win(Game* game) {
    if ((game->red_pieces | game->red_kings) == 0) return 1;   // Black wins
    if ((game->black_pieces | game->black_kings) == 0) return 0; // Red wins
    return -1; // Continue
}