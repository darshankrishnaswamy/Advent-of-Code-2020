#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

vector<string> data;
vector<vector<string>> data2;

void load_data(){

    ifstream fin("day6.txt");

    while(fin.peek() != EOF) {
        string s;
        string tmp = "hello";

        while(!tmp.empty()) {
            getline(fin, tmp);
            s += tmp;
        }

        data.push_back(s);
    }
}

int getCount(const string& s) {
    bool chars[26];

    for(bool & i : chars)
        i = false;

    for (char c : s)
        chars[c-'a'] = true;

    int out = 0;
    for (bool i : chars)
        if (i)
            out ++;


    return out;
}

int part1(){
    int count = 0;
    for (const string& s : data)
        count += getCount(s);

    return count;
}

void load_data2() {
    ifstream fin("day6.txt");

    while(fin.peek() != EOF) {
        vector<string> s;
        string tmp = "hello";

        while(!tmp.empty()) {
            getline(fin, tmp);
            if(!tmp.empty())
                s.push_back(tmp);
        }

        data2.push_back(s);
    }
}

int check2(const vector<string>& v){
    int count = 0;
    int size = v.size();
    int chars[26];
    for(int &i : chars)
        i = 0;

    for(const string& s : v)
        for(char c : s)
            chars[c-'a'] += 1;

    for(int i : chars)
        if (i==size)
            count++;
    return count;
}

int part2() {
    int count = 0;
    for(const vector<string>& v : data2)
        count += check2(v);

    return count;
}

int main() {
    load_data();
    cout << part1() << endl;

    load_data2();
    cout << part2() << endl;
}


