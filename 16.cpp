#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

constexpr int MAX_MAZE_SIZE = 200;

struct State {
    pair<int, int> pos;
    int dir, cost;
    bool operator<(const State& other) const { return cost > other.cost; }
    vector<pair<int, int>> path;
};

int dx[] = {1, 0, -1, 0};  // index is a direction
int dy[] = {0, 1, 0, -1};  // index is a direction
int dist[MAX_MAZE_SIZE][MAX_MAZE_SIZE][4];

int bfs(vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {
    // We don't need to use distance heuristic - the best path does not
    // necessarily lead towards the destination first.
    priority_queue<State> pq;
    pq.push({start, 0, 0, {start}});  // Start facing east
    dist[start.first][start.second][0] = 0;

    for (int i = 0; i < MAX_MAZE_SIZE; ++i) {
        for (int j = 0; j < MAX_MAZE_SIZE; ++j) {
            for (int k = 0; k < 4; ++k) {
                dist[i][j][k] = numeric_limits<int>::max();
            }
        }
    }

    int max_cost = numeric_limits<int>::max();
    while (!pq.empty()) {
        auto [pos, dir, cost, path] = pq.top();
        pq.pop();

        if (pos == end && cost <= max_cost) {
            max_cost = cost;
            for (auto place : path) {
                maze[place.first][place.second] = 'O';
            }
        }

        // Rotate left
        int new_dir = (dir + 3) % 4;
        if (dist[pos.first][pos.second][new_dir] >=
            cost +
                1000) {  // Should be '>' if we would like to find only one path
            dist[pos.first][pos.second][new_dir] = cost + 1000;
            pq.push({pos, new_dir, cost + 1000, path});
        }

        // Rotate right
        new_dir = (dir + 1) % 4;
        if (dist[pos.first][pos.second][new_dir] >=
            cost +
                1000) {  // Should be '>' if we would like to find only one path
            dist[pos.first][pos.second][new_dir] = cost + 1000;
            pq.push({pos, new_dir, cost + 1000, path});
        }

        // Move forward
        pair<int, int> next_pos = {pos.first + dy[dir], pos.second + dx[dir]};
        if (maze[next_pos.first][next_pos.second] != '#' &&
            dist[next_pos.first][next_pos.second][dir] >=
                cost + 1) {  // Should be '>' if we would like to find only one
                             // path
            path.push_back(next_pos);
            pq.push({next_pos, dir, cost + 1, path});
        }
    }
    return max_cost;
}

pair<int, int> find_in_maze(const vector<vector<char>>& maze,
                            char looking_for) {
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[0].size(); j++) {
            if (maze[i][j] == looking_for) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

int main() {
    vector<vector<char>> maze;

    string line;
    while (!cin.eof()) {
        getline(cin, line);
        maze.push_back(vector<char>(line.begin(), line.end()));
    }

    auto start = find_in_maze(maze, 'S');
    auto end = find_in_maze(maze, 'E');

    cout << bfs(maze, start, end) << '\n';
    int benches = 0;
    for (auto row : maze) {
        benches += count(row.begin(), row.end(), 'O');
    }
    cout << benches;

    return 0;
}
