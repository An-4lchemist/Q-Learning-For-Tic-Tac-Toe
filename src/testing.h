#ifndef Q_LEARNING_TESTING_H
#define Q_LEARNING_TESTING_H

#include <string>
#include <map>

using namespace std;

void input_humans_choice(string &human, string &agent);

// 0 - valid, 1 - invalid
int input_humans_move(int &row, int &col);

void test(map<pair<string, pair<int, int>>, double> &Q);

#endif
