#include <iostream>
#include <sstream>

// #define PART_TWO

using namespace std;

typedef pair<long int, long int> p;

long int get_cost(p buttonA, p buttonB, p prize) {
    // A[0]*a + B[0]*b = P[0]
    // A[1]*a + B[1]*b = P[1]
    p buttonACopy = buttonA;
    p buttonBCopy = buttonB;
    p prizeCopy = prize;

    //  B[1] * (A[0]*a + B[0]*b) =  B[1] * P[0]
    // -B[0] * (A[1]*a + B[1]*b) = -B[0] * P[1]
    buttonACopy.first *= buttonBCopy.second;
    buttonBCopy.first *= buttonBCopy.second;
    prizeCopy.first *= buttonBCopy.second;
    buttonACopy.second *= -buttonB.first;
    buttonBCopy.second *= -buttonB.first;
    prizeCopy.second *= -buttonB.first;

    //  (B[1]A[0] - B[0]A[1])a + (B[1]B[0] - B[0]B[1])a = B[1]P[0] - B[0]P[1] =>
    //  (B[1]A[0] - B[0]A[1])a = B[1]P[0] - B[0]P[1]
    buttonACopy.first += buttonACopy.second;
    buttonBCopy.first += buttonBCopy.second;
    prizeCopy.first += prizeCopy.second;

    if (prizeCopy.first % buttonACopy.first == 0) {
        long int a = prizeCopy.first / buttonACopy.first;

        if ((prize.first - (buttonA.first * a)) % buttonB.first == 0) {
            long int b = (prize.first - (buttonA.first * a)) / buttonB.first;
            return 3 * a + b;
        }
    }

    return -1;
}

int main() {
    p buttonA;
    p buttonB;
    p prize;

    string line;
    string temp;
    int line_number = 1;
    long int sum = 0;
    while (getline(cin, line)) {
        if (line.empty()) {
            continue;
        }
        stringstream ss(line);
        if (line_number == 1) {
            ss >> temp >> temp;
            ss.ignore(3);
            ss >> buttonA.first;
            ss.ignore(4);
            ss >> buttonA.second;
            line_number++;
        } else if (line_number == 2) {
            ss >> temp >> temp;
            ss.ignore(3);
            ss >> buttonB.first;
            ss.ignore(4);
            ss >> buttonB.second;
            line_number++;
        } else {
            ss >> temp;
            ss.ignore(3);
            ss >> prize.first;
            ss.ignore(4);
            ss >> prize.second;
            #ifdef PART_TWO
            prize.first += 10000000000000;
            prize.second += 10000000000000;
            #endif
            line_number = 1;

            long int result = get_cost(buttonA, buttonB, prize);
            if (result != -1) {
                sum += result;
            }
        }
    }
    cout << sum << '\n';
    return 0;
}
