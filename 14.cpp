#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

constexpr int ROWS = 103;
constexpr int COLUMNS = 101;

struct Robot {
    pair<int, int> pos, vel;
};

Robot parse_input_line(string& line) {
    Robot robot;
    stringstream ss(line);
    ss.ignore(2);
    ss >> robot.pos.second;
    ss.ignore(1);
    ss >> robot.pos.first;
    ss.ignore(3);
    ss >> robot.vel.second;
    ss.ignore(1);
    ss >> robot.vel.first;
    return robot;
}

void predict_robot_position(Robot& robot, int seconds) {
    robot.pos.first = (robot.pos.first + robot.vel.first * seconds) % ROWS;
    if (robot.pos.first < 0) {
        robot.pos.first = ROWS + robot.pos.first;
    }
    robot.pos.second =
        (robot.pos.second + robot.vel.second * seconds) % COLUMNS;
    if (robot.pos.second < 0) {
        robot.pos.second = COLUMNS + robot.pos.second;
    }
}

void part_one() {
    int map[ROWS][COLUMNS]{};

    string line;
    while (getline(cin, line)) {
        auto robot = parse_input_line(line);

        predict_robot_position(robot, 100);
        map[robot.pos.first][robot.pos.second]++;
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
}

bool is_easter_egg(int map[ROWS][COLUMNS]) {
    // When none of the robots are in the same place (works for my input)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (map[i][j] >= 2) {
                return false;
            }
        }
    }
    return true;
}

void part_two() {
    int map[ROWS][COLUMNS]{};
    vector<Robot> robots;

    string line;
    while (getline(cin, line)) {
        robots.push_back(parse_input_line(line));
    }

    int seconds = 1;
    while (!is_easter_egg(map) || seconds == 1) {  // Firstly the map is empty
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLUMNS; j++) {
                map[i][j] = 0;
            }
        }
        for (auto robot : robots) {
            predict_robot_position(robot, seconds);
            map[robot.pos.first][robot.pos.second]++;
        }
        seconds++;
    }
    cout << seconds - 1;
}

int main() {
    part_one();
    // part_two();

    return 0;
}