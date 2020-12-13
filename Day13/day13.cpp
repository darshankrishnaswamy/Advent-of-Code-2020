#include <iostream>
#include <fstream>
#include <vector>
#include <map>
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
        if(s[i] == ','){

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

long long myMod(int a, int b){
    long long out = a % b;
    if(out < 0) out += b;
    return out;
}

long long part2(){
    long long finalTime = times[0];
    long long multiplier = times[0];

    for(int i = 1; i < times.size(); i++){
        int n = 0;
        while(finalTime % times[i] != myMod((times[i]-m[times[i]]), times[i]))
            finalTime += multiplier;

        multiplier *= times[i];
    }
    return finalTime;
}

int main() {
    load_data();
    cout << part1() << endl;

    cout << part2() << endl;
}
