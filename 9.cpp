#include <iostream>
#include <list>
#include <vector>

using namespace std;

void part_one() {
    vector<int> disk_map;

    int temp;
    unsigned int id = 0;
    bool file = true;
    while (!cin.eof()) {
        temp = (int)cin.get() - '0';
        if (file) {
            for (int i = 0; i < temp; i++) {
                disk_map.push_back(id);
            }
            id++;
        } else {
            for (int i = 0; i < temp; i++) {
                disk_map.push_back(-1);
            }
        }
        file = !file;
    }

    int left = 0;
    int right = disk_map.size() - 1;
    while (left < right) {
        while (disk_map[right] == -1 && left < right) {
            right--;
        }
        while (disk_map[left] != -1 && left < right) {
            left++;
        }
        if (disk_map[right] != -1 && disk_map[left] == -1 && left < right) {
            disk_map[left] = disk_map[right];
            left++;
            right--;
        }
    }

    while (disk_map[left] == -1) {
        left--;
    }

    unsigned long int sum = 0;
    for (int i = 0; i <= left; i++) {
        sum += i * disk_map[i];
    }
    cout << '\n' << sum;
}

enum FS { file, space };
struct element {
    FS type;
    int id;
    int length;
};

bool is_left_before_right(element& left, element& right) {
    if (left.type == space) {
        return abs(left.id) < right.id + 1;
    }
    return true;
}

void part_two() {
    list<element> disk_map;

    int temp;
    int id = 0;
    int neg_id = -1;
    bool is_file = true;
    while (cin.peek() != EOF) {
        temp = (int)cin.get() - '0';
        if (is_file) {
            disk_map.push_back(element{file, id, temp});
            id++;
        } else {
            disk_map.push_back(element{space, neg_id, temp});
            neg_id--;
        }
        is_file = !is_file;
    }

    id--;
    auto right = disk_map.end();
    right = prev(right);
    auto start_optimal = disk_map.begin();
    while (id >= 0) {
        while (right->id != id) {
            right = prev(right);
        }

        bool was_empty = false;
        for (auto left = start_optimal; left != prev(disk_map.end()) &&
                                        is_left_before_right(*left, *right);
             left = next(left)) {
            if (!was_empty && left->type == space && left->length > 0) {
                was_empty = true;
                start_optimal = left;
            }
            if (left->type == space && left->length >= right->length) {
                element temp = (*right);
                right->id = neg_id;
                neg_id--;
                right->type = space;
                if (left->length == temp.length) {
                    *left = temp;
                } else {
                    disk_map.insert(left, temp);
                    left->length -= temp.length;
                }
                break;
            }
        }
        if (right == disk_map.begin()) {
            break;
        }
        right = prev(right);
        id--;
    }

    unsigned long int sum = 0;
    unsigned long int i = 0;
    for (auto elem : disk_map) {
        for (int j = 0; j < elem.length; j++) {
            if (elem.type == file) {
                sum += i * elem.id;
            }
            i++;
        }
    }
    cout << '\n' << sum;
}

int main() {
    // part_one();
    part_two();

    return 0;
}