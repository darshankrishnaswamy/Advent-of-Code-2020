#include <iostream>
#include <fstream>
<<<<<<< HEAD
#include <set>
#include <queue>

using namespace std;

long long part1(){
    ifstream fin("day8.txt");
    queue<long long> q;
    set<long long> s;
    for(int i = 0; i < 25; i++) {
        long long j;
        fin >> j;
        s.insert(j);
        q.push(j);
    }
    for(int i = 0; i < 975; i++){
        long long j;
        fin >> j;
        bool found = false;
        for(long long a : s){
            if(s.find(j-a) != s.end()){
                found = true;
            }
        }

        if(found) {
            long long to_remove = q.front();
            q.pop();
            s.erase(to_remove);
            s.insert(j);
            q.push(j);
        }
        else{
            return j;
        }
    }
    return -1;

}

long long part2(){
    ifstream fin("day8.txt");
    long long data[1000];
    for(long long & i : data){
        fin >> i;
    }
    int lower = 0, upper = 0;
    long long sum = data[0];
    long long desired = part1();
    while(sum != desired){
        if(sum < desired) {
            upper ++;
            sum += data[upper];
        }
        else{
            sum -= data[lower];
            lower ++;
        }
    }
    long long min=INTMAX_MAX, max=0;
    for(int i = lower; i <= upper; i++){
        if(data[i] > max) max = data[i];
        if(data[i] < min) min = data[i];
    }
    return min + max;

}
int main() {
    cout << part1() << endl;
    cout << part2() << endl;
    return 0;
=======
#include <vector>
#include <set>
using namespace std;

vector<pair<string, int>> ops;

void load_data(){
    ifstream fin("day8.txt");
    for(int i = 0; i < 623; i++){
        pair<string, int> p;
        fin >> p.first >> p.second;
        ops.push_back(p);
    }
}

int part1(vector<pair<string, int>> _ops){
    int acc = 0;
    set<int> visited;
    int curr = 0;
    while(visited.find(curr) == visited.end()) {
        pair<string, int> p = _ops[curr];
        visited.insert(curr);
        if(p.first == "acc"){
            acc += p.second;
            curr++;
        }
        else if(p.first == "jmp"){
            curr += p.second;
        }
        else{
            curr ++;
        }
    }
    return acc;
}

/**
 * Returns the value of the accumulator if it does not loop infinitely, otherwise -1
 * @param _ops the list of operations
 * @return The accumulator value, or -1 if it loops infinitely
 */
int check_infinite(vector<pair<string, int>> _ops){
    int acc = 0;
    set<int> visited;
    int curr = 0;
    while(visited.find(curr) == visited.end()) {
        if(curr == 622) return acc;
        pair<string, int> p = _ops[curr];
        visited.insert(curr);
        if(p.first == "acc"){
            acc += p.second;
            curr++;
        }
        else if(p.first == "jmp"){
            curr += p.second;
        }
        else{
            curr ++;
        }
    }
    return -1;
}

int part2(vector<pair<string, int>> _ops){
    for(int i = 0; i < _ops.size(); i++){
        if(_ops[i].first == "nop"){
            _ops[i].first = "jmp";
            int b = check_infinite(_ops);
            if(b != -1)
                return b;
            else
                _ops[i].first = "nop";
        }
        if(_ops[i].first == "jmp"){
            _ops[i].first = "nop";
            int b = check_infinite(_ops);
            if(b != -1)
                return b;
            else
                _ops[i].first = "jmp";
        }
    }
    return -4;
}

int main() {
    load_data();
    cout << part1(ops) << endl;
    cout << part2(ops) << endl;
>>>>>>> 0400831c0c0f79641b731da4c861fda386402b97
}
