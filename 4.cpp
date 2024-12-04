#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<char>> wordSearch;

bool check_if_xmas(int i, int j, int iIncrementator, int jIncrementator) {
    return wordSearch[i][j] == 'X' &&
           wordSearch[i + iIncrementator][j + jIncrementator] == 'M' &&
           wordSearch[i + 2 * iIncrementator][j + 2 * jIncrementator] == 'A' &&
           wordSearch[i + 3 * iIncrementator][j + 3 * jIncrementator] == 'S';
}

int find_horizontal() {
    int sum = 0;
    for (int i = 0; i < wordSearch.size(); i++) {
        for (int j = 0; j < wordSearch[0].size(); j++) {
            if ((j < wordSearch[0].size() - 3 &&
                 check_if_xmas(i, j, 0, 1))) {  // right
                sum++;
            }
            if (j >= 3 && check_if_xmas(i, j, 0, -1)) {  // left
                sum++;
            }
        }
    }
    return sum;
}

int find_vertical() {
    int sum = 0;
    for (int i = 0; i < wordSearch.size(); i++) {
        for (int j = 0; j < wordSearch[0].size(); j++) {
            if (i < wordSearch.size() - 3 && check_if_xmas(i, j, 1, 0)) { // down
                sum++;
            }
            if (i >= 3 && check_if_xmas(i, j, -1, 0)) { // up
                sum++;
            }
        }
    }
    return sum;
}

int find_diagonal() {
    int sum = 0;
    for (int i = 0; i < wordSearch.size(); i++) {
        for (int j = 0; j < wordSearch[0].size(); j++) {
            if (i < wordSearch.size() - 3) {  // down
                if (j < wordSearch[0].size() - 3 &&
                    check_if_xmas(i, j, 1, 1)) {  // right
                    sum++;
                }
                if (j >= 3 && check_if_xmas(i, j, 1, -1)) {  // left
                    sum++;
                }
            }
            if (i >= 3) {  // up
                if (j < wordSearch[0].size() - 3 &&
                    check_if_xmas(i, j, -1, 1)) {  // right
                    sum++;
                }
                if (j >= 3 && check_if_xmas(i, j, -1, -1)) {  // left
                    sum++;
                }
            }
        }
    }
    return sum;
}

bool check_if_mas(char a, char b, char c) {
    return (a == 'M' && b == 'A' && c == 'S' ||
            a == 'S' && b == 'A' && c == 'M');
}

int find_x_mas() {
    int sum = 0;
    for (int i = 0; i < wordSearch.size() - 2; i++) {
        for (int j = 0; j < wordSearch[0].size() - 2; j++) {
            if (check_if_mas(wordSearch[i][j], wordSearch[i + 1][j + 1],
                             wordSearch[i + 2][j + 2]) &&
                check_if_mas(wordSearch[i][j + 2], wordSearch[i + 1][j + 1],
                             wordSearch[i + 2][j])) {
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
        wordSearch.push_back(vector<char>(line.begin(), line.end()));
    }

    // Part One
    int sum = find_horizontal() + find_vertical() + find_diagonal();
    cout << sum << '\n';

    // Part Two
    sum = find_x_mas();
    cout << sum << '\n';
    return 0;
}