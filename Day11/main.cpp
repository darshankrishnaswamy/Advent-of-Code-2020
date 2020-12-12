#include <iostream>
#include <fstream>

using namespace std;

const int WIDTH = 92;
const int HEIGHT = 92;
string grid[HEIGHT];

int vectors[8][2];

void load_data(){
    ifstream fin("day11.txt");
    for(auto & row : grid) {
        fin >> row;
    }
    int ind = 0;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if(i==0 && j==0) continue;
            vectors[ind][0] = i;
            vectors[ind][1] = j;
            ind++;
        }
    }
}

int getOcc(int x, int y){
    int count = 0;
    for(auto & v : vectors){
        if(x + v[1] >= 0 && x + v[1] < WIDTH && y+v[0] >=0 && y+v[0] < HEIGHT){
            char c = grid[x+v[1]][y+v[0]];
            if(c == '#') count++;
        }
    }
    return count;
}

char occupiedHelper(int x, int y){
    int count = getOcc(x, y);
    if(count >= 4) return 'L';
    else return '#';
}

char emptyHelper(int x, int y){
    int count = getOcc(x, y);
    if(count >= 1) return 'L';
    else return '#';
}

char change(int x, int y){
    char c = grid[x][y];
    if(c == '#'){
        return occupiedHelper(x, y);
    }
    else if(c=='L')
        return emptyHelper(x, y);
    else
        return '.';
}

bool single_sim(){
    bool out = true;
    char new_grid[WIDTH][HEIGHT];
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            new_grid[i][j] = change(i, j);
        }
    }

    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            if(grid[i][j] != new_grid[i][j]) out=false;
            grid[i][j] = new_grid[i][j];

        }
    }
    return out;

}

int part1(){


    while(!single_sim()){
        single_sim();
    }

    single_sim();
    single_sim();

    int out = 0;
    for(auto & i : grid) {
        for (char j : i) {
            if (j == '#')
                out++;
        }
    }
    return out;
}

int getOcc2(int x, int y){
    int count = 0;
    for(auto & v : vectors) {
        int i = 1;
        while(x + v[1]*i >= 0 && x + v[1]*i < WIDTH && y+v[0]*i >=0 && y+v[0]*i < HEIGHT) {
//            cout << i << endl;
            char c = grid[x + v[1]*i][y + v[0]*i];
            if(c == 'L')
                break;
            else if (c == '#') {
                count++;
                break;
            }
            else
                i++;
        }
    }
    return count;
}
char occupiedHelper2(int x, int y){
    int count = getOcc2(x, y);
    if(count >= 5) return 'L';
    else return '#';
}

char emptyHelper2(int x, int y){
    int count = getOcc2(x, y);
    if(count >= 1) return 'L';
    else return '#';
}

char change2(int x, int y){
    char c = grid[x][y];
    if(c == '#'){
        return occupiedHelper2(x, y);
    }
    else if(c=='L')
        return emptyHelper2(x, y);

}

bool single_sim2(){
    bool out = true;
    char new_grid[WIDTH][HEIGHT];
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            new_grid[i][j] = change2(i, j);
        }
    }

    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            if(grid[i][j] != new_grid[i][j]) out=false;
            grid[i][j] = new_grid[i][j];

        }
    }
    return out;

}

int part2(){
    int i = 0;

    while(!single_sim2()){
    }

    int out = 0;
    for(auto & i : grid) {
        for (char j : i) {
            if (j == '#')
                out++;
        }
    }
    return out;
}

int main() {

    load_data();
    cout << part1() << endl;

    load_data();
    cout << part2() << endl;

}
