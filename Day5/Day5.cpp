#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> posns;

void load_data(){
    ifstream fin("day5.txt");
    for(int i = 0; i < 846; i++) {
        string a;
        fin >> a;
        posns.push_back(a);
    }
}
int process(string a){
    int yPosn;
    int min = 0, max = 127;
    for(int i = 0; i < 6; i++) {
        char c = a[i];
        if(c == 'B')
            min = (min+max+1)/2;
        else
            max = (min+max)/2;
    }
    if(a[6] == 'B') yPosn = max;
    else yPosn = min;

    int xPosn;

    int min2 = 0, max2 = 7;
    for(int i = 7; i < 9; i++) {
        char c = a[i];
        if(c == 'R')
            min2 = (min2+max2+1)/2;
        else
            max2 = (min2+max2)/2;
    }
    if(a[9] == 'R')
        xPosn = max2;
    else
        xPosn = min2;

    return 8*yPosn + xPosn;


}

int part1(){
    int max = 0;
    for (const string& a : posns) {
        int i = process(a);
        if (i > max)
            max = i;
    }
    return max;
}

int part2(){
    vector<int> ids;
    ids.reserve(posns.size());
    for (const string& a : posns)
        ids.push_back(process(a));

    sort(ids.begin(), ids.end());

    for(int i = 1; i < ids.size()-100; i++)
        if(ids[i] != ids[i-1]+1)
            return ids[i]-1;

    return -1;
}

int main() {
    load_data();

    cout << part1() << endl;

    cout << part2() << endl;


}

