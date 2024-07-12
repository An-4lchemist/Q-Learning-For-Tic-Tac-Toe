#ifndef Q_LEARNING_TRAINING_H
#define Q_LEARNING_TRAINING_H

#include <map>
#include <string>

const int TRAINING_EPISODES = 100000;
const double ALPHA = 0.5;
const double GAMMA = 0.9;

using namespace std;

string convert_board_to_string(string (&board)[3][3]);

void train(map<pair<string, pair<int, int>>, double> &Q);

#endif
