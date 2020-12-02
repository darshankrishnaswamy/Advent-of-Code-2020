#include <iostream>
#include <fstream>

using namespace std;

struct line{
    int min{};
    int max{};
    char letter{};
    string word;
};

static line lines[1000];

int* parseMinMax(const string& str) {
    int separatorIndex; // index of the '-' character in the string
    for(int i = 0; i < str.length(); i++)
        if(str[i] == '-')
            separatorIndex = i;
    static int out[2];
    out[0] = stoi(str.substr(0, separatorIndex));
    out[1] = stoi(str.substr(separatorIndex+1));

    return out;
}

void loadData() {
    ifstream fin("day2.txt");
    for(auto & i : lines){
        line currentLine;
        string token1, token2, token3;
        fin >> token1;
        int* minMax = parseMinMax(token1);
        currentLine.min = *minMax;
        currentLine.max = *(minMax+1);
        fin >> token2;
        currentLine.letter = token2[0];
        fin >> token3;
        currentLine.word = token3;
        i = currentLine;
    }
}

int countChar(const string &s, char c) {
    int count = 0;
    for(char i : s)
        if(i == c)
            count++;

    return count;
}

bool valid1(const line &l) {
    int count = countChar(l.word, l.letter);
    if(l.min <= count && count <= l.max)
        return true;

    return false;
}
int part1() {
    int count = 0;
    for(const line &l : lines)
        if(valid1(l))
            count++;

    return count;
}

bool valid2(const line &l) {
    if(l.word[l.min-1] == l.letter ^ l.word[l.max-1] == l.letter)
        return true;

    return false;
}

int part2() {
    int count = 0;
    for(const line &l : lines)
        if(valid2(l))
            count++;

    return count;
}


int main() {
    loadData();

    cout << part1() << endl;
    cout << part2() << endl;

    return 0;
}



