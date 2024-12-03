#include <iostream>

using namespace std;

void part_one() {
    int a, b;
    int sum = 0;
    while (!cin.eof()) {
        if (cin.get() == 'm' && cin.get() == 'u' && cin.get() == 'l' &&
            cin.get() == '(' && cin >> a && cin.get() == ',' && cin >> b && cin.get() == ')') {
            sum += a * b;
        }
    }
    cout << sum;
}

void part_two() {
    int a, b;
    int sum = 0;
    bool enabled = true;
    while (!cin.eof()) {
        if (cin.get() == 'm' && cin.get() == 'u' && cin.get() == 'l' &&
            cin.get() == '(' && cin >> a && cin.get() == ',' && cin >> b &&
            cin.get() == ')') {
            if (enabled) {
                sum += a * b;
            }
        } else {
            if (cin.eof()) {
                break;
            }
            cin.unget();
            if (cin.get() == 'd' && cin.get() == 'o') {
                if (cin.get() == 'n' && cin.get() == '\'' && cin.get() == 't' &&
                    cin.get() == '(' && cin.get() == ')') {
                    enabled = false;
                } else {
                    cin.unget();
                    if (cin.get() == '(' && cin.get() == ')') {
                        enabled = true;
                    } else {
                        cin.unget();
                    }
                }
            }
        }
    }
    cout << sum;
}

int main() {
    // part_one();
    part_two();
    return 0;
}