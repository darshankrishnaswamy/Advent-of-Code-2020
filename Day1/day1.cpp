#include <iostream>
#include <fstream>
#include <set>
using namespace std;
static const int TARGET = 2020;

int part1(set<int> &nums) {
    for (int num1 : nums) {
        int goal = TARGET - num1;
        if (nums.find(goal) != nums.end())
            return num1 * goal;
    }
    return -1;
}

int part2(const set<int> &nums) {
    for (int num1 : nums) {
        for (int num2 : nums) {
            int goal = TARGET - num1 - num2;
            if (nums.find(goal) != nums.end())
                return num1 * num2 * goal;
        }
    }
    return -1;
}

int main() {
    ifstream fin("nums.txt");
    set<int> nums;
    for (int i = 0; i < 200; i++) {
        int val;
        fin >> val;
        nums.insert(val);
    }

    cout << part1(nums) << endl;
    cout << part2(nums) << endl;

}



