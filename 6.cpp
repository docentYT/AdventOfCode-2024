#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int obstacle_count = 0;

vector<vector<char>> original_map;

void print_map(const vector<vector<char>>& map) {
    for (auto line : map) {
        for (auto c : line) {
            cout << c;
        }
        cout << '\n';
    }
}

pair<int, int> guard_position;

pair<int, int> find_guard(const vector<vector<char>>& map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '^') {
                return make_pair(i, j);
            }
        }
    }
    throw;
}

void guard_rotate(pair<int, int>& direct) {
    if (direct.first == -1) {
        direct.first = 0;
        direct.second = 1;
    } else if (direct.second == 1) {
        direct.first = 1;
        direct.second = 0;
    } else if (direct.first == 1) {
        direct.first = 0;
        direct.second = -1;
    } else if (direct.second == -1) {
        direct.first = -1;
        direct.second = 0;
    }
}

bool is_extending_map_bounds(const pair<int, int>& pos, const pair<int, int>& direct,
                             const vector<vector<char>>& map) {
    return (pos.first + direct.first < 0 || pos.first + direct.first >= map.size() ||
            pos.second + direct.second < 0 || pos.second + direct.second >= map[0].size());
}

void guard_move(pair<int, int>& pos, pair<int, int>& direct, vector<vector<char>>& map,
                bool search_for_loop, pair<int, int> custom_barrier);

set<pair<int, int>> vis_main = {};
void check_if_loop(pair<int, int> pos, pair<int, int> direct) {
    const pair<int, int> barrier_pos = make_pair(pos.first + direct.first, pos.second + direct.second);
    if (barrier_pos ==
        guard_position) {
        return;
    }
    if (vis_main.find(barrier_pos) !=
        vis_main.end()) {
        return;
    }
    set<pair<pair<int, int>, pair<int, int>>> visited = {};
    while (!is_extending_map_bounds(pos, direct, original_map)) {
        if (visited.find(make_pair(pos, direct)) !=
            visited.end()) {
            obstacle_count++;
            return;
        }

        visited.insert(make_pair(pos, direct));
        guard_move(pos, direct, original_map, false, barrier_pos);
    }
}

void guard_move(pair<int, int>& pos, pair<int, int>& direct, vector<vector<char>>& map,
                bool search_for_loop = true, pair<int, int> custom_barrier = make_pair(-1, -1)) {
    if (map[pos.first + direct.first][pos.second + direct.second] != '#' && (pos.first + direct.first != custom_barrier.first || pos.second + direct.second != custom_barrier.second)) {
        pos.first += direct.first;
        pos.second += direct.second;
    } else {
        guard_rotate(direct);
    }
    if (search_for_loop) {
        check_if_loop(pos, direct);
        vis_main.insert(pos);
    }
    map[pos.first][pos.second] = 'X';
}

int count_visited(vector<vector<char>>& map) {
    int sum = 0;
    for (auto line : map) {
        for (auto ch : line) {
            if (ch == 'X' || ch == '^') {
                sum++;
            }
        }
    }
    return sum;
}

int main() {
    string line;
    while (!cin.eof()) {
        getline(cin, line);
        original_map.push_back(vector<char>(line.begin(), line.end()));
    }

    vector<vector<char>> map = original_map;
    guard_position = find_guard(map);
    pair<int, int> guard_direction = {-1, 0};

    while (!is_extending_map_bounds(guard_position, guard_direction, map)) {
        guard_move(guard_position, guard_direction, map);
    }

    cout << count_visited(map) << '\n' << obstacle_count;

    return 0;
}