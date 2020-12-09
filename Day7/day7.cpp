#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;
struct bag{
    string color;
    vector<pair<string, int>> children;
};

vector<bag> bags;
map<string, bag> bag_map;

/**
 * Splits a string at commas (and removes the spaces at the front)
 * @param str the string to split
 * @return a list of the strings
 */
vector<string> split_at_comma(string str){
    vector<string> out;
    int prevInd = 0;
    for(int i = 0; i < str.size(); i++){
        if(str[i] == ','){
            out.push_back(str.substr(prevInd, i-prevInd));
            prevInd = i+2;
        }
    }
    out.push_back(str.substr(prevInd, str.length() - prevInd - 1));
    return out;
}

/**
 * Reads a string and returns a pair<string, int> containing the color of the bag and the quantity
 * @param str the string describing the child bag (ex: "2 faded red bags")
 * @return a pair of the color and quantity (ex: pair of "faded red bags" and the number 2)
 */
pair<string, int> get_child(const string& str){
    int spaceInd = 0;
    for(int i = 0; i < str.length(); i++){
        if (str[i] == ' '){
            spaceInd = i;
            break;
        }
    }
    int count = stoi(str.substr(0, spaceInd));
    int bagInd = 0;
    for(int i = 0; i < str.length(); i++){
        if(str.substr(i, 3) == "bag"){
            bagInd = i;
            break;
        }
    }

    string color = str.substr(spaceInd+1, bagInd-spaceInd-2);
    pair<string, int> p;
    p.first = color;
    p.second = count;
    return p;
}

/**
 * Reads in a list of bags and returns a list of children
 * @param str
 * @return
 */
vector<pair<string, int>> get_bags(const string& str){
    vector<pair<string, int>> out;
    if(str == "no other bags.") return out;
    vector<string> v = split_at_comma(str);
    for(string s : v){
        out.push_back(get_child(s));
    }
    return out;

}

void load_data(){
    ifstream fin("day7.txt");
    for(int i = 0; i < 594; i++){
        string line;
        getline(fin, line);
        int bagInd = 0;
        for(int j = 0; j < line.size()-5; j++){
            if(line.substr(j, 4) == "bags"){
                bagInd = j;
                break;
            }
        }
        bag out;
        string color = line.substr(0, bagInd-1);
        out.color = color;
        string rest = line.substr(bagInd+13);
        out.children = get_bags(rest);
        bags.push_back(out);

    }

    for(const bag& i : bags)
        bag_map[i.color] = i;

}

bool validate_bag(const bag& b){
    for(const pair<string, int>& p : b.children){
        if(p.first == "shiny gold") return true;
        if(validate_bag(bag_map[p.first])) return true;
    }

    return false;
}

int part1(){
    int count = 0;
    for(const bag& b : bags){
        if(validate_bag(b)) count++;
    }
    return count;
}

int count(const string& name){
    bag b = bag_map[name];
    if(b.children.empty()) return 0;
    else{
        int c = 0;
        for (const pair<string, int>& p : b.children){
            c += p.second;
            c += p.second * count(p.first);
        }
        return c;
    }
}

int part2(){
    return count("shiny gold");
}

int main() {
    load_data();

    cout << part1() << endl;

    cout << part2() << endl;
    return 0;
}
