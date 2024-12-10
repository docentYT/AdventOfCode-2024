#include <iostream>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

vector<vector<int>> map;

bool in_bounds(int y, int x) {
    return (y >= 0 && y < map.size() && x >= 0 && x < map[0].size());
}

set<pair<int, int>> find_trail_part_one(int current_number, int y, int x) {
    set<pair<int, int>> return_value = {};
    if (map[y][x] != current_number) {
        return return_value;
    }
    if (current_number == 9) {
        return_value.insert({y, x});
        return return_value;
    }

    if (in_bounds(y - 1, x))
        return_value.merge(find_trail_part_one(current_number + 1, y - 1, x));
    if (in_bounds(y + 1, x))
        return_value.merge(find_trail_part_one(current_number + 1, y + 1, x));
    if (in_bounds(y, x - 1))
        return_value.merge(find_trail_part_one(current_number + 1, y, x - 1));
    if (in_bounds(y, x + 1))
        return_value.merge(find_trail_part_one(current_number + 1, y, x + 1));

    return return_value;
}

int part_one() {
    int sum = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] == 0) {
                sum += find_trail_part_one(0, i, j).size();
            }
        }
    }
    return sum;
};

int find_trail_part_two(int current_number, int y, int x) {
    if (map[y][x] != current_number) {
        return 0;
    }
    if (current_number == 9) {
        return 1;
    }

    int sum = 0;
    if (in_bounds(y - 1, x))
        sum += find_trail_part_two(current_number + 1, y - 1, x);
    if (in_bounds(y + 1, x))
        sum += find_trail_part_two(current_number + 1, y + 1, x);
    if (in_bounds(y, x - 1))
        sum += find_trail_part_two(current_number + 1, y, x - 1);
    if (in_bounds(y, x + 1))
        sum += find_trail_part_two(current_number + 1, y, x + 1);

    return sum;
}

int part_two() {
    int sum = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] == 0) {
                sum += find_trail_part_two(0, i, j);
            }
        }
    }
    return sum;
}

int main() {
    string line;
    while (!cin.eof()) {
        getline(cin, line);
        stringstream ss(line);

        vector<int> row;
        char temp;
        while (ss >> temp) {
            row.push_back((int)temp - '0');
        }
        map.push_back(row);
    }

    cout << part_one() << '\n' << part_two();
}