#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int countOccurrences(const vector<int> vect, int& startIndex, int number) {
    int occurrences = 0;
    while (vect[startIndex] < number) {
        startIndex++;
    }
    while (vect[startIndex] == number) {
        startIndex++;
        occurrences++;
    }
    return occurrences;
}

int main() {
    vector<int> a;
    vector<int> b;

    while (cin) {
        int numberA = -1;
        int numberB = -1;
        cin >> numberA >> numberB;
        a.push_back(numberA);
        b.push_back(numberB);
    }
    a.pop_back();
    b.pop_back();
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    // Part One
    int sum = 0;
    for (int i = 0; i < a.size(); i++) {
        sum += abs(a[i] - b[i]);
    }
    cout << sum << '\n';

    // Part Two
    int similarity = 0;
    int startIndex = 0;
    int previousNumber = 0;
    int previousAdd = 0;
    for (int number : a) {
        if (number != previousNumber) {
            previousAdd = number * countOccurrences(b, startIndex, number);
            previousNumber = number;
        }
        similarity += previousAdd;
    }
    cout << similarity;
}