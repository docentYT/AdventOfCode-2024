#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool is_safe(int prev, int next, bool increasing) {
    return (increasing && next - prev >= 1 && next - prev <= 3) ||
           (!increasing && prev - next >= 1 && prev - next <= 3);
}

vector<int> get_report_from_line(const string& line) {
    vector<int> report;
    istringstream iss(line);
        int level;
        while (iss >> level) {
            report.push_back(level);
        }
    return report;
}

void part_one() {
    int sum = 0;
    while (!cin.eof()) {
        string line;
        getline(cin, line);

        vector<int> report = get_report_from_line(line);
        bool safe = true;

        if (report[0] == report[1]) {
            safe = false;
            continue;
        }
        bool increasing = report[0] < report[1];
        for (int i = 1; i < report.size(); i++) {
            if (!is_safe(report[i - 1], report[i], increasing)) {
                safe = false;
                break;
            }
        }
        if (safe) {
            sum++;
        }
    }

    cout << sum << '\n';
}

void part_two() {
    int sum = 0;
    while (!cin.eof()) {
        string line;
        getline(cin, line);

        vector<int> report = get_report_from_line(line);
        bool safe = true;
        bool can_tolerate = true;
        int start_index = 0;

        if (report[0] == report[1]) {
            if (report[1] != report[2]) {
                can_tolerate = false;
                start_index = 1;
            } else {
                safe = false;
                continue;
            }
        }
        bool increasing = report[start_index] < report[start_index + 1];
        for (int i = start_index + 1; i < report.size(); i++) {
            if (!is_safe(report[i - 1], report[i], increasing)) {
                if (!can_tolerate) {
                    safe = false;
                    break;
                }
                if (i + 1 == report.size()) {
                    continue;
                } else if (is_safe(report[i - 1], report[i + 1], increasing)) {
                    i += 1;
                } else if (is_safe(report[i - 2], report[i], increasing)) {
                    i += 1;
                } else {
                    increasing = !increasing;
                    can_tolerate = false;
                    i = start_index + 2;
                }
                can_tolerate = false;
            }
        }
        if (safe) {
            sum++;
        }
    }

    cout << sum << '\n';
}

int main() {
    // part_one(); // 411
    part_two();
    return 0;
}