#include <iostream>
#include <fstream>
#include <set>
using namespace std;

int part1(set<int> nums, int target);
int part2(set<int> nums, int target);

int main() {
    ifstream fin("nums.txt");
    set<int> nums;
    for (int i = 0; i < 200; i++) {
        int val;
        fin >> val;
        nums.insert(val);
    }

    cout << part1(nums, 2020) << endl;
    cout << part2(nums, 2020) << endl;

}

int part1(set<int> nums, int target) {
    for (int num1 : nums) {
        int goal = target - num1;
        if (nums.find(goal) != nums.end())
            return num1 * goal;
    }
    return -1;
}

int part2(set<int> nums, int target) {
    for (int num1 : nums) {
        for (int num2 : nums) {
            int goal = target - num1 - num2;
            if (nums.find(goal) != nums.end())
                return num1 * num2 * goal;
        }
    }
    return -1;
}



