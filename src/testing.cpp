#include <iostream>
#include "testing.h"
#include "game.h"
#include "agent.h"

using namespace std;

void input_humans_choice(string &human, string &agent) {
    cout << "Choose" << endl <<
         "1> X" << endl <<
         "2> O" << endl;

    int choice;
    cin >> choice;
    if (choice == 1) {
        human = "X";
        agent = "O";
    } else if (choice == 2) {
        human = "O";
        agent = "X";
    } else {
        cout << "Invalid choice" << endl;
        exit(1);
    }
}

// 0 - valid, 1 - invalid
int input_humans_move(int &row, int &col) {
    cout << "Enter row and column (1-3)" << endl;
    cin >> row >> col;
    row--;
    col--;
    if (row < 0 || row > 2 || col < 0 || col > 2) {
        return 1;
    }
    return 0;
}

void test(map<pair<string, pair<int, int>>, double> &Q) {
    cout << "Testing -" << endl;

    string human, agent, player;
    input_humans_choice(human, agent);

    string board[3][3] = {{" ", " ", " "},
                          {" ", " ", " "},
                          {" ", " ", " "}};

    if (human == "O") {
        make_agent_move(board, agent, Q);
    }
    print_board(board);

    while (is_game_over(board) == 0) {
        int row, col;
        int invalid = input_humans_move(row, col);
        if (invalid || board[row][col] != " ") {
            cout << "Invalid move" << endl;
            continue;
        }

        board[row][col] = human;

        print_board(board);

        if (is_game_over(board) != 0) {
            break;
        }

        make_agent_move(board, agent, Q);
        cout << "///////////" << endl;
        print_board(board);

        // human = (human == "X") ? "O" : "X";
    }

    int result = is_game_over(board);
    if (result == 3) {
        cout << "Draw" << endl;
    } else {
        cout << (((result == 1 && human == "X") || (result == 2 && human == "O")) ?
                 "human wins" : "agent wins")
             << endl;
    }
}