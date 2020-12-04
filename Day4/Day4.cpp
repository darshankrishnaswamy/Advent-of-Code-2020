#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <regex>

using namespace std;

set<string> ecls;
vector<map<string, string>> a;

vector<string> splitAtSpaces(string str) {
    vector<string> strings;
    int prevInd = 0;
    for(int i = 0; i < str.length(); i++){
        if(str[i] == ' ') {
            strings.push_back(str.substr(prevInd, i - prevInd));
            prevInd = i+1;
        }
    }
    strings.push_back(str.substr(prevInd, str.length() - prevInd));
    return strings;
}

string getKey(const string& str) {
    int indexOfColon = str.find(':');
    return str.substr(0, indexOfColon);
}

string getValue(const string& str){
    int indexOfColon = str.find(':');
    return str.substr(indexOfColon+1);
}

void loadData() {
    ifstream fin("Day4.txt");
    ecls.insert("amb");
    ecls.insert("blu");
    ecls.insert("brn");
    ecls.insert("gry");
    ecls.insert("grn");
    ecls.insert("hzl");
    ecls.insert("oth");

    map<string, string> current;
    for(int i = 0; i < 1139; i++) {
        string b;
        getline(fin, b);
        if (b.empty()) {
            a.push_back(current);
            current.clear();
        } else {
            vector<string> c = splitAtSpaces(b);
            for (const string &q : c)
                current[getKey(q)] = getValue(q);
        }
    }
}


bool contains(map<string, string> person, string str){
    return person.find(str) != person.end();
}


bool valid(map<string, string> person){
    return contains(person,"byr") && contains(person, "iyr") && contains(person, "eyr") && contains(person, "hgt") &&
         contains(person, "hcl") && contains(person, "ecl") && contains(person, "pid");
}

bool validByr(int yr){
    return 1920<= yr && yr <= 2002;
}

bool validHgt(const string& hgt){
    regex heightRegex("[0-9]*[a-z]{2}");

    if(!regex_match(hgt, heightRegex)) return false;

    int height = stoi(hgt.substr(0, hgt.length() - 2));

    if (hgt.substr(hgt.length() - 2) == "in")
        return 59 <= height && height <= 76;
    else if (hgt.substr(hgt.length() - 2) == "cm")
        return 150 <= height && height <= 193;
    else
        return false;
}


bool validIyr(int yr){
    return 2010 <= yr && yr <= 2020;
}

bool validEyr(int yr){
    return 2020 <= yr && yr <= 2030;
}

bool validHcl(const string& hcl){
    regex hclRegex("#[0-9a-f]{6}");
    return regex_match(hcl, hclRegex);
}

bool validEcl(const string& ecl){
    return ecls.find(ecl) != ecls.end();
}

bool validPid(string pid){
    regex pidRegex("[0-9]{9}");
    return regex_match(pid, pidRegex);
}



bool valid2(map<string, string> person){
    if(!valid(person)) return false;
    if(!validByr(stoi(person["byr"]))) return false;
    if(!validHgt(person["hgt"])) return false;
    if(!validIyr(stoi(person["iyr"]))) return false;
    if(!validEyr(stoi(person["eyr"]))) return false;
    if(!validHcl(person["hcl"])) return false;
    if(!validEcl(person["ecl"])) return false;
    if(!validPid(person["pid"])) return false;

    return true;
}



int main() {

    loadData();
    int count1 = 0, count2 = 0;
    for(const map<string, string>& p : a) {

        if(valid(p))
            count1++;

        if(valid2(p))
            count2++;
    }

    cout << count1 << endl;
    cout << count2 << endl;

    return 0;
}
