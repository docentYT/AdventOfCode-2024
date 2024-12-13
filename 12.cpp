#include <iostream>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

bool is_in_bounds(const vector<vector<char>>& garden, pair<int, int> coords) {
    return coords.first >= 0 && coords.first < garden.size() &&
           coords.second >= 0 && coords.second < garden[0].size();
}

// perimeter, area, corners
tuple<int, int, int> visit_node(vector<vector<bool>>& visited,
                                const vector<vector<char>>& garden,
                                pair<int, int> coords) {
    visited[coords.first][coords.second] = true;
    int perimeter = 4;
    int area = 1;
    int corners = 0;
    const char current_type = garden[coords.first][coords.second];
    const vector<pair<int, int>> coords_to_check{
        {coords.first - 1, coords.second},
        {coords.first, coords.second + 1},
        {coords.first + 1, coords.second},
        {coords.first, coords.second - 1}};

    for (const auto& check : coords_to_check) {
        if (is_in_bounds(garden, check)) {
            if (garden[check.first][check.second] == current_type) {
                perimeter--;
                if (!visited[check.first][check.second]) {
                    auto result = visit_node(visited, garden, check);
                    perimeter += get<0>(result);
                    area += get<1>(result);
                    corners += get<2>(result);
                }
            }
        }
    }

    // corners
    vector<tuple<pair<int, int>, pair<int, int>, pair<int, int>>>
        internal_corners_to_check{// BA
                                  // AA
                                  {{coords.first - 1, coords.second},
                                   {coords.first, coords.second - 1},
                                   {coords.first - 1, coords.second - 1}},
                                  // AB
                                  // AA
                                  {{coords.first - 1, coords.second},
                                   {coords.first, coords.second + 1},
                                   {coords.first - 1, coords.second + 1}},
                                  // AA
                                  // BA
                                  {{coords.first + 1, coords.second},
                                   {coords.first, coords.second - 1},
                                   {coords.first + 1, coords.second - 1}},
                                  // AA
                                  // AB
                                  {{coords.first + 1, coords.second},
                                   {coords.first, coords.second + 1},
                                   {coords.first + 1, coords.second + 1}}};

    for (const auto& check : internal_corners_to_check) {
        if (is_in_bounds(garden, get<0>(check)) &&
            garden[get<0>(check).first][get<0>(check).second] == current_type &&
            is_in_bounds(garden, get<1>(check)) &&
            garden[get<1>(check).first][get<1>(check).second] == current_type &&
            is_in_bounds(garden, get<2>(check)) &&
            garden[get<2>(check).first][get<2>(check).second] != current_type) {
            corners++;
        }
    }

    vector<tuple<pair<int, int>, pair<int, int>>> external_corners_to_check{
        // --
        // |A
        {{coords.first - 1, coords.second}, {coords.first, coords.second - 1}},
        // --
        // A|
        {{coords.first - 1, coords.second}, {coords.first, coords.second + 1}},
        // |A
        // --
        {{coords.first + 1, coords.second}, {coords.first, coords.second - 1}},
        // A|
        // --
        {{coords.first + 1, coords.second}, {coords.first, coords.second + 1}}};

    for (const auto& check : external_corners_to_check) {
        if ((!is_in_bounds(garden, get<0>(check)) ||
             garden[get<0>(check).first][get<0>(check).second] !=
                 current_type) &&
            (!is_in_bounds(garden, get<1>(check)) ||
             garden[get<1>(check).first][get<1>(check).second] !=
                 current_type)) {
            corners++;
        }
    }

    return {perimeter, area, corners};
}

pair<int, int> dfs(const vector<vector<char>>& garden) {
    vector<vector<bool>> visited(garden.size(),
                                 vector<bool>(garden[0].size(), false));

    int sum_part_one = 0;
    int sum_part_two = 0;
    for (int i = 0; i < garden.size(); i++) {
        for (int j = 0; j < garden[0].size(); j++) {
            if (!visited[i][j]) {
                auto result = visit_node(visited, garden, {i, j});
                sum_part_one += get<0>(result) * get<1>(result);
                sum_part_two += get<2>(result) * get<1>(result);
            };
        }
    }
    return {sum_part_one, sum_part_two};
}

int main() {
    vector<vector<char>> garden;

    string line;
    while (!cin.eof()) {
        getline(cin, line);
        garden.push_back(vector<char>(line.begin(), line.end()));
    }

    auto results = dfs(garden);
    cout << results.first << '\n' << results.second;

    return 0;
}