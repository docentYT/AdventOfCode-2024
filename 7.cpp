#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<unsigned long int> search_combinations(unsigned long int test,
                                   vector<unsigned long int>& numbers,
                                   unsigned long int start_index, bool concate) {
    if (start_index == 0) {
        return {numbers[start_index], numbers[start_index]};
    }
    vector<unsigned long int> result;
    for (unsigned long int number : search_combinations(test, numbers, start_index - 1, concate)) {
        unsigned long int add = number + numbers[start_index];
        unsigned long int multiply = number * numbers[start_index];
        if (add <= test) {
            result.push_back(add);
        }
        if (multiply <= test) {
            result.push_back(multiply);
        }
        if (concate) {
            unsigned long int concate =
                stoul(to_string(number) + to_string(numbers[start_index]));
            if (concate <= test) {
                result.push_back(concate);
            }
        }
    }
    return result;
}

unsigned long int part_one_sum = 0;
unsigned long int part_two_sum = 0;
int main() {
    string line;
    while (!cin.eof()) {
        getline(cin, line);
        stringstream ss(line);
        unsigned long int test;
        ss >> test;
        ss.get();  // ':' char
        vector<unsigned long int> numbers;
        unsigned long int number;
        while (ss >> number) {
            numbers.push_back(number);
        }
        vector<unsigned long int> results =
            search_combinations(test, numbers, numbers.size() - 1, false);
        for (unsigned long int result : results) {
            if (result == test) {
                part_one_sum += test;
                break;
            }
        }

        results = search_combinations(test, numbers, numbers.size() - 1, true);
        for (unsigned long int result : results) {
            if (result == test) {
                part_two_sum += test;
                break;
            }
        }
    }
    cout << part_one_sum << '\n' << part_two_sum;
    return 0;
}