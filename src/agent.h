#ifndef Q_LEARNING_AGENT_H
#define Q_LEARNING_AGENT_H

#include <string>
#include <map>
#include <random>

using namespace std;

static random_device rand_dev;
static mt19937 gen(rand_dev());
static uniform_real_distribution<double> dist(0, 1);


void make_agent_move(string (&board)[3][3], string agent, map<pair<string, pair<int, int>>, double> &Q);

pair<int, int> get_action(string state, map<pair<string, pair<int, int>>, double> &Q, double epsilon);

#endif
