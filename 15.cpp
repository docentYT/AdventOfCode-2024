#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// #define PART_TWO

pair<int, int> find_robot(const vector<vector<char>>& map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] == '@') {
                return {i, j};
            }
        }
    }
    throw;
}

#ifndef PART_TWO
bool move_boxes(pair<int, int> start, char movement,
                vector<vector<char>>& map) {
    int offset_y = 0;
    int offset_x = 0;
    while (map[start.first + offset_y][start.second + offset_x] == 'O') {
        if (movement == '>') {
            offset_x++;
        } else if (movement == '<') {
            offset_x--;
        } else if (movement == 'v') {
            offset_y++;
        } else if (movement == '^') {
            offset_y--;
        }
    }

    if (map[start.first + offset_y][start.second + offset_x] == '#') {
        return false;
    }
    map[start.first + offset_y][start.second + offset_x] = 'O';
    return true;
}
#endif

#ifdef PART_TWO
bool move_boxes_vertically(vector<vector<char>>& map,
                           vector<pair<int, int>> boxes, char direction) {
    int offset = -1;
    if (direction == 'v') {
        offset = 1;
    }
    // No more boxes to push
    if (boxes.empty()) {
        return true;
    }

    vector<pair<int, int>> next_boxes;
    for (pair<int, int>& box : boxes) {
        // Normalize box coords
        if (map[box.first][box.second] == ']') {
            box.second--;
        }

        // If wall touched cannot push boxes
        if (map[box.first + offset][box.second] == '#' ||
            map[box.first + offset][box.second + 1] == '#') {
            return false;
        }

        // Find next boxes
        if (map[box.first + offset][box.second] == '[' ||
            map[box.first + offset][box.second] == ']') {
            next_boxes.push_back({box.first + offset, box.second});
        }
        if (map[box.first + offset][box.second + 1] == '[' ||
            map[box.first + offset][box.second + 1] == ']') {
            next_boxes.push_back({box.first + offset, box.second + 1});
        }
    }

    bool can_move = move_boxes_vertically(map, next_boxes, direction);
    if (!can_move) {
        return false;
    }

    // Move boxes on map
    for (const pair<int, int>& box : boxes) {
        map[box.first + offset][box.second] = '[';
        map[box.first + offset][box.second + 1] = ']';
        map[box.first][box.second] = '.';
        map[box.first][box.second + 1] = '.';
    }

    return true;
}

bool move_boxes_horizontally(vector<vector<char>>& map, pair<int, int> start,
                             char direction) {
    int offset = 0;
    while (map[start.first][start.second + offset] == '[' ||
           map[start.first][start.second + offset] == ']') {
        offset += (direction == '>') ? 1 : -1;
    }

    if (map[start.first][start.second + offset] == '#') {
        return false;
    }
    while (offset > 0) {
        map[start.first][start.second + offset] =
            map[start.first][start.second + offset - 1];
        offset--;
    }
    while (offset < 0) {
        map[start.first][start.second + offset] =
            map[start.first][start.second + offset + 1];
        offset++;
    }
    return true;
}

bool move_boxes(pair<int, int> start, char movement,
                vector<vector<char>>& map) {
    if ((movement == 'v' || movement == '^') &&
        (map[start.first][start.second] == '[' ||
         map[start.first][start.second] == ']')) {
        return move_boxes_vertically(map, {start}, movement);
    }

    return move_boxes_horizontally(map, start, movement);
}
#endif

void move_robot(pair<int, int>& position, char movement,
                vector<vector<char>>& map) {
    auto move_on_map = [&map, &position, movement](int y, int x) {
        if (map[position.first + y][position.second + x] == '#') {
            return;
        }
        position.first += y;
        position.second += x;
        if (move_boxes(position, movement, map)) {
            map[position.first][position.second] = '@';
            map[position.first - y][position.second - x] = '.';
        } else {
            position.first -= y;
            position.second -= x;
        }
    };
    if (movement == '^') {
        move_on_map(-1, 0);
    } else if (movement == '>') {
        move_on_map(0, 1);
    } else if (movement == 'v') {
        move_on_map(1, 0);
    } else if (movement == '<') {
        move_on_map(0, -1);
    }
}

int get_sum_of_gps_coordinates(const vector<vector<char>>& map, char box_char) {
    int sum = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] == box_char) {
                sum += 100 * i + j;
            }
        }
    }
    return sum;
}

queue<char> get_movements(std::istream& is) {
    string line;
    queue<char> movements;
    while (!is.eof()) {
        getline(is, line);
        for (char ch : line) {
            movements.push(ch);
        }
    }
    return movements;
}

void run_movements(vector<vector<char>>& map, pair<int, int> position,
                   queue<char>& movements) {
    while (!movements.empty()) {
        char movement = movements.front();
        movements.pop();
        move_robot(position, movement, map);
    }
}

#ifndef PART_TWO
int main() {
    vector<vector<char>> map;
    string line;
    while (!cin.eof()) {
        getline(cin, line);
        if (line.empty()) {
            break;
        }
        map.push_back(vector<char>(line.begin(), line.end()));
    }

    queue<char> movements = get_movements(cin);
    pair<int, int> robot_position = find_robot(map);
    run_movements(map, robot_position, movements);
    cout << get_sum_of_gps_coordinates(map, 'O');

    return 0;
}
#else
int main() {
    vector<vector<char>> map;
    string line;
    while (!cin.eof()) {
        getline(cin, line);
        if (line.empty()) {
            break;
        }
        vector<char> row;
        for (char ch : line) {
            if (ch == 'O') {
                row.push_back('[');
                row.push_back(']');
            } else if (ch == '@') {
                row.push_back('@');
                row.push_back('.');
            } else {
                row.push_back(ch);
                row.push_back(ch);
            }
        }
        map.push_back(row);
    }

    queue<char> movements = get_movements(cin);
    pair<int, int> robot_position = find_robot(map);
    run_movements(map, robot_position, movements);
    cout << get_sum_of_gps_coordinates(map, '[');

    return 0;
}
#endif