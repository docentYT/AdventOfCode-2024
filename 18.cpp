#include <iostream>
#include <limits>
#include <queue>

using namespace std;

constexpr int SIZE = 71;
constexpr int BYTES_TO_FALL = 1024;

char map[SIZE][SIZE] = {};

struct State {
    pair<int, int> pos;
    int length;
    vector<pair<int, int>> path;
    bool operator<(const State& other) const { return length > other.length; }
};

bool is_in_bounds(pair<int, int> coords) {
    return coords.first >= 0 && coords.first < SIZE && coords.second >= 0 &&
           coords.second < SIZE;
}

int bfs(pair<int, int> start, pair<int, int> end) {
    int dist[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            dist[i][j] = numeric_limits<int>::max();
        }
    }
    dist[start.first][start.second] = 0;

    priority_queue<State> pq;
    pq.push({start, 0});

    int min_length = numeric_limits<int>::max();
    vector<pair<int, int>> min_path;
    while (!pq.empty()) {
        auto [pos, length, path] = pq.top();
        pq.pop();
        path.push_back(pos);

        if (pos == end && length <= min_length) {
            min_length = length;
            min_path = path;
        }

        vector<pair<int, int>> next_positions = {{pos.first - 1, pos.second},
                                                 {pos.first, pos.second + 1},
                                                 {pos.first + 1, pos.second},
                                                 {pos.first, pos.second - 1}};
        for (auto next_pos : next_positions) {
            if (is_in_bounds(next_pos) &&
                map[next_pos.first][next_pos.second] != '#' &&
                dist[next_pos.first][next_pos.second] > length + 1) {
                dist[next_pos.first][next_pos.second] = length + 1;
                vector<pair<int, int>> cp = path;
                pq.push({next_pos, length + 1, path});
            }
        }
    }
    for (auto a : min_path) {
        map[a.first][a.second] = 'O';
    }
    return min_length;
}

int main() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = '.';
        }
    }

    int x, y;
    char temp;
    for (int i = 0; i < BYTES_TO_FALL; i++) {
        cin >> x >> temp >> y;
        map[y][x] = '#';
    }

    cout << bfs({0, 0}, {SIZE - 1, SIZE - 1}) << '\n';

    while (cin >> x >> temp >> y) {
        if (map[y][x] == 'O') {
            map[y][x] = '#';
            if (bfs({0, 0}, {SIZE - 1, SIZE - 1}) ==
                numeric_limits<int>::max()) {
                cout << x << ',' << y;
                break;
            }
        }
        map[y][x] = '#';
    }

    return 0;
}