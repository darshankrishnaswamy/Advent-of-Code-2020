#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int NUM_LINES = 786;

struct command{
    char letter;
    int number;
};

vector<command> command_list;

void load_data(){
    ifstream fin("day12.txt");
    for(int i = 0; i < NUM_LINES; i++){
        string s;
        fin >> s;
        char dir = s[0];
        int num = stoi(s.substr(1));
        command c{dir, num};
        command_list.push_back(c);
    }

}

int part1(){
    int x = 0, y = 0;
    int dir = 0; // 0 -> E, 1 -> N, 2 -> W, 3 -> S
    for(command c : command_list){
        if(c.letter == 'N')
            y += c.number;

        else if(c.letter == 'S')
            y -= c.number;

        else if(c.letter == 'E')
            x += c.number;

        else if(c.letter == 'W')
            x -= c.number;

        else if(c.letter == 'L') {
            dir += c.number / 90;
            dir %= 4;
        }

        else if(c.letter == 'R') {
            dir += 3 * c.number / 90;
            dir %= 4;
        }

        else if(c.letter == 'F'){
            if(dir == 0)
                x += c.number;
            else if(dir == 1)
                y += c.number;
            else if(dir==2)
                x -= c.number;
            else if(dir == 3)
                y -= c.number;
        }
    }

    return abs(x) + abs(y);
}


pair<int, int> rotateL(int x, int y, int deg){
    if(deg == 0) return {x, y};
    else if(deg == 90) return {-y, x};
    else if(deg == 180) return {-x, -y};
    else return {y, -x};
}

pair<int, int> rotateR(int x, int y, int deg){
    if(deg == 0) return {x, y};
    else if(deg == 90) return {y, -x};
    else if(deg == 180) return {-x, -y};
    else return {-y, x};
}

// part 2
int part2(){
    int x = 0, y = 0;
    int xW = 10, yW = 1; // relative
    for(command c : command_list){
        if(c.letter == 'N')
            yW+= c.number;

        else if(c.letter == 'S')
            yW -= c.number;

        else if(c.letter == 'E')
            xW += c.number;

        else if(c.letter == 'W')
            xW -= c.number;

        else if(c.letter == 'R') {
            pair<int, int> newPos = rotateR(xW, yW, c.number);
            xW = newPos.first, yW = newPos.second;
        }

        else if(c.letter == 'L'){
            pair<int, int> newPos = rotateL(xW, yW, c.number);
            xW = newPos.first, yW = newPos.second;
        }

        else if(c.letter == 'F'){
            x += c.number * xW;
            y += c.number * yW;
        }
    }

    return abs(x) + abs(y);

}

int main() {
    load_data();
    cout << part1() << endl;
    cout << part2() << endl;
}
