#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "checkers.h"

int main() {
    Game game;
    init_game(&game);

    printf("=== BitBoard Checkers ===\n");
    printf("Controls: Enter 'row col to_row to_col' (e.g., 5 0 4 1)\n");
    printf("r/R = Red (Regular/King) & b/B = Black (Regular/King)\n");

    int winner = -1;
    while (winner == -1) {
        print_board(&game);
        printf("\n%s's turn > ", game.current_player == 0 ? "Red" : "Black");

        int fr, fc, tr, tc;
        if (scanf("%d %d %d %d", &fr, &fc, &tr, &tc) != 4) {
            break; // Exit on bad input or EOF
        }

        int move_type = is_valid_move(&game, fr, fc, tr, tc);
        if (!move_type) {
            printf("Invalid move! Rules:\n");
            printf("- Must move diagonally on dark squares\n");
            printf("- Regular pieces move FORWARD only (Red moves up numbers, Black moves down)\n");
            printf("- Must jump opponents if adjacent\n");
            continue;
        }

        make_move(&game, fr, fc, tr, tc);
        winner = check_win(&game);
    }

    if (winner != -1) {
        print_board(&game);
        printf("\nGAME OVER! %s Wins!\n", winner == 0 ? "Red" : "Black");
    }

    return 0;
}