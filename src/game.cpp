#include <iostream>
#include "game.h"

using namespace std;

void print_board(string (&board)[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << board[i][j] << " ";
            if (j < 2) {
                cout << "|";
            }
        }
        if (i < 2) {
            cout << endl << "-----------" << endl;
        } else {
            cout << endl;
        }
    }
}

// 0 - game not over, 1 - 'X' wins, 2 - 'O' wins, 3 - draw
int is_game_over(string (&board)[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (board[i][1] != " " && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return (board[i][0] == "X") ? 1 : 2;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (board[1][i] != " " && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return (board[0][i] == "X") ? 1 : 2;
        }
    }
    if (board[1][1] != " " && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return (board[1][1] == "X") ? 1 : 2;
    }
    if (board[1][1] != " " && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return (board[1][1] == "X") ? 1 : 2;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == " ") {
                return 0;
            }
        }
    }
    return 3;
}

double get_reward(string (&board)[3][3], const string& agent) {
    if (is_game_over(board) == 1) {
        return (agent == "X") ? 1.0 : -1.0;
    } else if (is_game_over(board) == 2) {
        return (agent == "O") ? 1.0 : -1.0;
    } else {
        return 0.0;
    }
}
