#include <iostream>
#include <sstream>

using namespace std;

constexpr int TIMES = 100;
constexpr int ROWS = 103;
constexpr int COLUMNS = 101;

void predict_robot_position(pair<int, int>& position,
                            const pair<int, int>& velocity) {
    position.first = (position.first + velocity.first * TIMES) % ROWS;
    if (position.first < 0) {
        position.first = ROWS + position.first;
    }
    position.second = (position.second + velocity.second * TIMES) % COLUMNS;
    if (position.second < 0) {
        position.second = COLUMNS + position.second;
    }
}

int main() {
    int map[ROWS][COLUMNS]{};

    string line;
    pair<int, int> robot_position;
    pair<int, int> robot_velocity;
    while (getline(cin, line)) {
        stringstream ss(line);
        ss.ignore(2);
        ss >> robot_position.second;
        ss.ignore(1);
        ss >> robot_position.first;
        ss.ignore(3);
        ss >> robot_velocity.second;
        ss.ignore(1);
        ss >> robot_velocity.first;

        predict_robot_position(robot_position, robot_velocity);
        map[robot_position.first][robot_position.second]++;
    }

    int quadrant_TL = 0;
    int quadrant_TR = 0;
    int quadrant_BL = 0;
    int quadrant_BR = 0;

    for (int i = 0; i < ROWS / 2; i++) {
        for (int j = 0; j < COLUMNS / 2; j++) {
            quadrant_TL += map[i][j];
        }
        for (int j = COLUMNS / 2 + 1; j < COLUMNS; j++) {
            quadrant_TR += map[i][j];
        }
    }
    for (int i = ROWS / 2 + 1; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS / 2; j++) {
            quadrant_BL += map[i][j];
        }
        for (int j = COLUMNS / 2 + 1; j < COLUMNS; j++) {
            quadrant_BR += map[i][j];
        }
    }

    cout << quadrant_TL * quadrant_TR * quadrant_BL * quadrant_BR;

    return 0;
}