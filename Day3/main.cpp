#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
static vector<string> strings;

void loadData() {
    ifstream fin("day3.txt");
    for(int i = 0; i < 323; i++) {
        string line;
        fin >> line;
        strings.push_back(line);
    }
}

int count(int xIncr, int yIncr) {
    int x=0, y=0;
    int count = 0;
    int stringLength = strings[0].length();
    while(y < strings.size()){
        if(strings[y][x] == '#')
            count ++;
        x = (x+xIncr)%stringLength;
        y += yIncr;
    }

    return count;
}

int part1() {
    return count(3, 1);
}

unsigned long int part2() {
    unsigned long int total = 1;

    total *= count(1, 1);
    total *= count(3, 1);
    total *= count(5, 1);
    total *= count(7, 1);
    total *= count(1, 2);

    return total;
}

int main() {
    loadData();
    cout << part1() << endl;
    cout << part2() << endl;
}
