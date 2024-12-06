#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// a must be printed before all pages in rules[a] vector
vector<int> rules[100] = {};

int main() {
    int sum_correct, sum_incorrect = 0;
    int a, b;
    char separator;

    string line;
    while (!cin.eof()) {
        getline(cin, line);
        stringstream ss(line);
        if (line[2] == '|') {
            ss >> a >> separator >> b;
            rules[a].push_back(b);
        } else {
            vector<int> update{};
            while (!ss.eof()) {
                ss >> a >> separator;
                update.push_back(a);
            }

            bool correct = true;
            for (int i = 0; i < update.size(); i++) {
                for (int j = 0; j < i; j++) {
                    if (std::find(rules[update[i]].begin(),
                                  rules[update[i]].end(),
                                  update[j]) != rules[update[i]].end()) {
                        correct = false;
                        swap(update[i], update[j]);
                    }
                }
            }
            if (correct) {
                sum_correct += update[update.size() / 2];
            }
            if (!correct) {
                sum_incorrect += update[update.size() / 2];
            }
        }
    }

    cout << sum_correct << '\n' << sum_incorrect;

    return 0;
}