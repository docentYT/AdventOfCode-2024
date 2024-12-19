#include <bitset>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Registers {
    long int A, B, C;
};

vector<int> program;

long int operand_to_combo_value(int operand, const Registers& registers) {
    switch (operand) {
        case 0:
        case 1:
        case 2:
        case 3:
            return operand;
        case 4:
            return registers.A;
        case 5:
            return registers.B;
        case 6:
            return registers.C;
        default:
            throw invalid_argument("Operand must be between 0 and 6.");
    }
}

vector<int> run(vector<int> program, Registers registers) {
    vector<int> output;
    int instruction_pointer = 0;
    int operand;

    auto adv = [&registers](int value) {
        registers.A = registers.A / pow(2, value);
    };
    auto bxl = [&registers](int value) { registers.B ^= value; };
    auto bst = [&registers](long int value) { registers.B = value % 8; };
    auto jnz = [&registers, &instruction_pointer](int value) {
        instruction_pointer = (registers.A != 0) ? value : instruction_pointer;
    };
    auto bxc = [&registers]() { registers.B ^= registers.C; };
    auto out = [&registers, &output](long int value) {
        output.push_back(value % 8);
    };
    auto bdv = [&registers](long int value) {
        registers.B = registers.A / pow(2, value);
    };
    auto cdv = [&registers](long int value) {
        registers.C = registers.A / pow(2, value);
    };

    while (true) {
        if (instruction_pointer >= program.size()) {
            break;
        }

        int instruction = program[instruction_pointer++];
        operand = program[instruction_pointer++];

        long int combo = operand_to_combo_value(operand, registers);
        switch (instruction) {
            case 0:
                adv(combo);
                break;
            case 1:
                bxl(operand);
                break;
            case 2:
                bst(combo);
                break;
            case 3:
                jnz(operand);
                break;
            case 4:
                bxc();
                break;
            case 5:
                out(combo);
                break;
            case 6:
                bdv(combo);
                break;
            case 7:
                cdv(combo);
                break;
            default:
                break;
        }
    }
    return output;
}

void part_one(Registers registers) {
    auto output = run(program, registers);

    if (output.empty()) {
        return;
    }
    for (int i = 0; i < output.size() - 1; i++) {
        cout << output[i];
        cout << ',';
    }
    cout << output[output.size() - 1];
}

long int part_two(int out_to_check_from_end, long int a_reg_value,
                  long int min_a_reg_value) {
    if (out_to_check_from_end >= program.size()) {
        return a_reg_value;
    }

    for (int i = 0; i < 8; i++) {
        long int new_candidate = a_reg_value << 3;
        new_candidate = new_candidate | i;
        auto output = run(program, {new_candidate, 0, 0});

        if (out_to_check_from_end < output.size() &&
            program[program.size() - 1 - out_to_check_from_end] ==
                output[output.size() - 1 - out_to_check_from_end]) {
            long int value = part_two(out_to_check_from_end + 1, new_candidate,
                                      min_a_reg_value);
            if (value < min_a_reg_value) {
                min_a_reg_value = value;
                break;
            }
        }
    }
    return min_a_reg_value;
}

int main() {
    Registers registers;
    cin.ignore(12);
    cin >> registers.A;
    cin.ignore(12);
    cin >> registers.B;
    cin.ignore(12);
    cin >> registers.C;

    cin.ignore(10);
    string line;
    cin >> line;
    stringstream ss(line);
    int temp;
    while (!ss.eof()) {
        ss >> temp;
        program.push_back(temp);
        ss.ignore();
    }

    part_one(registers);
    cout << '\n';
    cout << part_two(0, 0, numeric_limits<long int>::max());

    return 0;
}