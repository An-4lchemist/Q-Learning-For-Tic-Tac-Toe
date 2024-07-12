#include <iostream>
#include <list>
#include <random>
#include "training.h"
#include "game.h"
#include "agent.h"

using namespace std;

void make_opp_move(string (&board)[3][3], string player) {
    list<pair<int, int>> actions;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == " ") {
                actions.push_back(make_pair(i, j));
            }
        }
    }
    uniform_int_distribution<int> dist2(0, (int) actions.size() - 1);
    int index = dist2(gen);
    auto it = actions.begin();
    advance(it, index);
    pair<int, int> action = *it;
    board[action.first][action.second] = player;
}

string convert_board_to_string(string (&board)[3][3]) {
    string board_string;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board_string += board[i][j];
        }
    }
    return board_string;
}

void train(map<pair<string, pair<int, int>>, double> &Q) {
//    srand((unsigned) time(nullptr));
    random_device rand_dev;
    mt19937 gen(rand_dev());
    uniform_real_distribution<double> dist(0, 1);
    // dist(gen)

    int episode_count = 0;
    double EPSILON = 0.7;

    string player = "X";
    while (episode_count < TRAINING_EPISODES) {
        string board[3][3] = {
                {" ", " ", " "},
                {" ", " ", " "},
                {" ", " ", " "}
        };
        player = (player == "X") ? "O" : "X";
        if (player == "O") {
            make_opp_move(board, (player == "X") ? "O" : "X");
        }

        while (is_game_over(board) == 0) {
            string state = convert_board_to_string(board);
            pair<int, int> ai_action = get_action(state, Q, EPSILON);

            board[ai_action.first][ai_action.second] = player;

            // make opponent move here
            if (is_game_over(board) == 0) {
                make_opp_move(board, (player == "X") ? "O" : "X");
            }

            double reward = get_reward(board, player);

            string new_state = convert_board_to_string(board);

            list<pair<int, int>> actions;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (new_state[i * 3 + j] == ' ') {
                        actions.push_back(make_pair(i, j));
                    }
                }
            }

            double max_q_val;
            int found = 0;
            for (pair<int, int> &action: actions) {
                auto it = Q.find(make_pair(new_state, action));
                if (it != Q.end()) {
                    double q_val = Q[make_pair(new_state, action)];
                    if (found == 0) {
                        found = 1;
                        max_q_val = q_val;
                    }
                    if (q_val > max_q_val) {
                        max_q_val = q_val;
                    }
                }
            }
            if (found == 0) {
                max_q_val = 0.0;
            }
            double old_q_val = Q[make_pair(state, ai_action)];
            Q[make_pair(state, ai_action)] = old_q_val + ALPHA * (reward + GAMMA * max_q_val - old_q_val);
        }
        episode_count++;
        if (episode_count % 10000 == 0) {
            EPSILON *= 0.9;
            cout << "Episode " << episode_count << endl;
        }
    }
}