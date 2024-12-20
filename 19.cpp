#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, long int> cache;

long int how_many_designs_possible(const vector<string>& towels,
                                   const string& pattern) {
    if (pattern.empty()) {
        return 1;
    }

    if (cache.find(pattern) != cache.end()) {
        return cache[pattern];
    }

    long int counter = 0;
    for (string_view towel : towels) {
        if (pattern.rfind(towel, 0) == 0) {
            string new_pattern = pattern.substr(towel.size());
            counter += how_many_designs_possible(towels, new_pattern);
        }
    }
    cache[pattern] = counter;
    return counter;
}

int main() {
    vector<string> towels;

    string line;
    getline(cin, line);
    stringstream ss(line);
    string towel;
    while (getline(ss, towel, ',')) {
        towel.erase(remove(towel.begin(), towel.end(), ' '), towel.end());
        towels.push_back(towel);
    }

    cin.ignore(1);  // empty line

    long int part_one = 0;
    long int part_two = 0;
    string pattern;
    while (getline(cin, pattern)) {
        long int possibilities = how_many_designs_possible(towels, pattern);
        if (possibilities > 0) {
            part_one++;
        }
        part_two += possibilities;
    }

    cout << part_one << '\n' << part_two;

    return 0;
}