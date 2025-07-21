#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void clearScreen() {
    cout<<"\033[2J\033[1;1H";
}

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
} 