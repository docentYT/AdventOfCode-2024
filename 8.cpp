#include <iostream>
#include <vector>

using namespace std;

bool is_in_bound(const vector<vector<char>>& map, int y, int x) {
    return y >= 0 && y < map.size() && x >= 0 && x < map[0].size();
}

void part_one(const vector<vector<char>>& map,
              vector<vector<char>>& antinodes_map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] == '.') {
                continue;
            }

            for (int k = 0; k < map.size(); k++) {
                for (int l = 0; l < map[0].size(); l++) {
                    if (map[k][l] != map[i][j]) {
                        continue;
                    }
                    if (k == i && l == j) {
                        continue;
                    }
                    const int deltaY = k - i;
                    const int deltaX = l - j;
                    if (is_in_bound(map, i - deltaY, j - deltaX)) {
                        antinodes_map[i - deltaY][j - deltaX] = '#';
                    }
                    if (is_in_bound(map, k + deltaY, l + deltaX)) {
                        antinodes_map[k + deltaY][l + deltaX] = '#';
                    }
                }
            }
        }
    }
}

void part_two(const vector<vector<char>>& map,
              vector<vector<char>>& antinodes_map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] == '.') {
                continue;
            }

            for (int k = 0; k < map.size(); k++) {
                for (int l = 0; l < map[0].size(); l++) {
                    if (map[k][l] != map[i][j]) {
                        continue;
                    }
                    if (k == i && l == j) {
                        continue;
                    }
                    int deltaY = k - i;
                    int deltaX = l - j;
                    int resonant = 0;

                    while (is_in_bound(map, i - deltaY * resonant,
                                       j - deltaX * resonant)) {
                        antinodes_map[i - deltaY * resonant]
                                     [j - deltaX * resonant] = '#';
                        resonant++;
                    }
                    deltaY = k - i;
                    deltaX = l - j;
                    resonant = 0;
                    while (is_in_bound(map, k + deltaY * resonant,
                                       l + deltaX * resonant)) {
                        antinodes_map[k + deltaY * resonant]
                                     [l + deltaX * resonant] = '#';
                        resonant++;
                    }
                }
            }
        }
    }
}

int count_antinodes(const vector<vector<char>>& map) {
    int sum = 0;
    for (auto a : map) {
        for (auto b : a) {
            if (b == '#') {
                sum++;
            }
        }
    }
    return sum;
}

int main() {
    vector<vector<char>> map;

    string line;
    while (!cin.eof()) {
        getline(cin, line);
        map.push_back(vector<char>(line.begin(), line.end()));
    }

    vector<vector<char>> antinodes_map = map;

    part_one(map, antinodes_map);
    cout << count_antinodes(antinodes_map) << '\n';

    antinodes_map = map;
    part_two(map, antinodes_map);
    cout << count_antinodes(antinodes_map);

    return 0;
}