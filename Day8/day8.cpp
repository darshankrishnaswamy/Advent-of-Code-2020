#include <iostream>
#include <fstream>
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
}
