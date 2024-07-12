#ifndef Q_LEARNING_GAME_H
#define Q_LEARNING_GAME_H

#include <string>

using namespace std;

void print_board(string (&board)[3][3]);

// 0 - game not over, 1 - 'X' wins, 2 - 'O' wins, 3 - draw
int is_game_over(string (&board)[3][3]);

double get_reward(string (&board)[3][3], const string& agent);

#endif
