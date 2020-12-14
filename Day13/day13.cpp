#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>

#include <algorithm>
#include <cassert>
#include <charconv>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

vector<int> times;
int time;
string s;
map<int, int> m;

void load_data(){
    ifstream fin("day13.txt");
    fin >> time;

    getline(fin, s);
    getline(fin, s);

    int prev = 0;
    int count = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == ',') {

            if(s.substr(prev, i-prev) != "x") {
                times.push_back(stoi(s.substr(prev, i - prev)));
                m[stoi(s.substr(prev, i - prev))] = count;
            }
            prev = i+1;
            count ++;
        }
    }
    times.push_back(stoi(s.substr(prev)));
    m[stoi(s.substr(prev))] = count;
}



int part1(){
    int minBus = times[0];
    int minTime = times[0] - (time%minBus);

    for(int bus : times){
        int busTime = bus - (time%bus);
        if(busTime < minTime){
            minBus = bus;
            minTime = busTime;
        }
    }
    return minTime * minBus;
}
/**
 * Returns the positive modulo of a and b
 * @param a the first number
 * @param b the second number
 * @return the positive module of a and b
 */
long long posMod(int a, int b){
    long long out = a % b;
    if(out < 0) out += b;
    return out;
}
long long gcd(long long a, long long b){
    if(b == 0) return a;
    return gcd(b, a%b);
}
long long lcm(long long a, long long b){
    return a*b/gcd(a, b);
}

// uses Chinese Remainder Theorem to find the smallest value "finalTime" satisfying each of the mod conditions
long long part2(){
    long long finalTime = times[0];
    long long multiplier = times[0];

    for(int i = 1; i < times.size(); i++){
        while(finalTime % times[i] != posMod((times[i]-m[times[i]]), times[i]))
            finalTime += multiplier;

        multiplier = lcm(multiplier, times[i]);
    }
    return finalTime;
}

int main() {
    load_data();
    cout << part1() << endl;

    cout << part2() << endl;
}
