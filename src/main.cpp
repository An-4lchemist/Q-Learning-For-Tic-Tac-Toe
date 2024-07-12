#include <iostream>
#include <fstream>
#include "testing.h"
#include "training.h"

using namespace std;

void serialize(map<pair<string, pair<int, int>>, double> &Q, const string& fname) {
    ofstream file ("table/" + fname + ".txt");
    if (file.is_open()) {
        for (auto &q: Q) {
            file << q.first.first << endl;
            file << q.first.second.first << endl;
            file << q.first.second.second << endl;
            file << setprecision(std::numeric_limits<int>::max()) << q.second << endl;
        }
        file.close();
    } else {
        cout << "error serializing";
    }
}

void deserialize(map<pair<string, pair<int, int>>, double> &Q, const string& fname) {
    ifstream file ("table/" + fname + ".txt");
    if (file.is_open()) {
        string line, state;
        int row, col;
        double q_val;
        int prev = 0;
        while (getline(file, line)) {
            switch (prev) {
                case 0:
                    state = line;
                    break;
                case 1:
                    row = stoi(line);
                    break;
                case 2:
                    col = stoi(line);
                    break;
                case 3:
                    q_val = stod(line);
                    Q[make_pair(state, make_pair(row, col))] = q_val;
                    break;
                default:
                    cout << "error deserializing";
                    break;
            }
            prev = (prev + 1) % 4;
        }
        file.close();
    } else {
        cout << "error deserializing - file not found";
    }
}

int main() {

    map<pair<string, pair<int, int>>, double> Q;

    train(Q);

    serialize(Q, "5");

    while (true) {
        test(Q);
        cout << "Play again? (y/n)" << endl;
        string choice;
        cin >> choice;
        if (choice != "y") {
            break;
        }
    }

    return 0;
}
