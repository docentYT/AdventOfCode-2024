#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

using namespace std;

// cache[times left][number]
map<int, map<unsigned long int, unsigned long int>> cache{};
unsigned long int blink(const unsigned long int number, const int times) {
    if (cache.find(times) != cache.end()) {
        if (cache[times].find(number) != cache[times].end()) {
            return cache[times][number];
        }
    } else {
        cache.insert({times, {}});
    }
    unsigned long int stone_counter = 0;
    if (times == 0) {
        stone_counter = 1;
    } else if (number == 0) {
        stone_counter = blink(1, times - 1);
    } else {
        const string str = to_string(number);
        const int str_length = str.length();
        if (str_length % 2 == 0) {
            stone_counter +=
                blink(stoi(str.substr(0, str_length / 2)), times - 1);
            stone_counter += blink(
                stoi(str.substr(str_length / 2, str_length - str_length / 2)),
                times - 1);
        } else {
            stone_counter = blink(number * 2024, times - 1);
        }
    }
    cache[times].insert(make_pair(number, stone_counter));
    return stone_counter;
}

int main() {
    list<unsigned long int> stones;

    int number;
    while (cin >> number) {
        stones.push_back(number);
    }

    unsigned long int sum_part_one = 0;
    unsigned long int sum_part_two = 0;
    for (auto stone : stones) {
        sum_part_one += blink(stone, 25);
        sum_part_two += blink(stone, 75);
    }

    cout << sum_part_one << '\n' << sum_part_two;

    return 0;
}