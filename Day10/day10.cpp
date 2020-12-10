#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;

const int NUM_ELEMENTS = 96;
int data[NUM_ELEMENTS];

void load_data(){
    ifstream fin("day10.txt");
    for(int & i : data){
        int num;
        fin >> num;
        i = num;
    }
    sort(data, data+NUM_ELEMENTS);

}

int part1(){
    int ones=1;
    int threes=1;
    for(int i = 0; i < NUM_ELEMENTS; i++){
        if(data[i+1]-data[i] == 1)
            ones++;
        else if(data[i+1]-data[i]==3)
            threes++;
    }
    return ones*threes;
}

/**
 * Solves part 2 of the question
 * A DP method that evaluates recursively from right to left
 * Let f(n) represent the number of ways to reach the end from the value of n (or 0 if n is not in the list)
 * Then f(n) = f(n+1) + f(n+2) + f(n+3).
 * The answer is f(1) + f(2) + f(3)
 * @return
 */
long long int part2() {
    map<int, long long int> dist_map; // maps n -> f(n) as described above
    dist_map[data[NUM_ELEMENTS - 1]] = 1;
    for (int i = NUM_ELEMENTS - 2; i >= 0; i--) {
        long long int val = 0;
        for (long long int j = data[i] + 1; j <= data[i] + 3; j++) {
            if (dist_map.find(j) != dist_map.end()) {
                val += dist_map[j];
            }
        }
        dist_map[data[i]] = val;
    }
    return dist_map[1]+dist_map[2]+dist_map[3];
}

int main() {
    load_data();
    cout << part1() << endl;
    cout << part2() << endl;
}
