#include "agent.h"
#include <list>

void make_agent_move(string (&board)[3][3], string agent, map<pair<string, pair<int, int>>, double> &Q) {
    string state;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            state += board[i][j];
        }
    }

    pair<int, int> ai_action = get_action(state, Q, -1);
    board[ai_action.first][ai_action.second] = agent;

}

pair<int, int> get_action(string state, map<pair<string, pair<int, int>>, double> &Q, double epsilon) {

    list<pair<int, int>> actions;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state[i * 3 + j] == ' ') {
                actions.push_back(make_pair(i, j));
            }
        }
    }

    if (epsilon != -1 && dist(gen) < epsilon) {
        uniform_int_distribution<int> dist2(0, (int) actions.size() - 1);
        int index = dist2(gen);
        auto it = actions.begin();
        advance(it, index);
        return *it;
    }

    double max_q_val;
    pair<int, int> max_action;
    int found = 0;
    for (pair<int, int> &action: actions) {
        auto it = Q.find(make_pair(state, action));
        if (it != Q.end()) {
            double q_val = Q[make_pair(state, action)];
            if (found == 0) {
                found = 1;
                max_q_val = q_val;
                max_action = action;
            }
            if (q_val > max_q_val) {
                max_q_val = q_val;
                max_action = action;
            }
        }
    }
    if (found == 0) {
        uniform_int_distribution<int> dist2(0, (int) actions.size() - 1);
        int index = dist2(gen);
        auto it = actions.begin();
        advance(it, index);
        return *it;
    }
    return max_action;
}
