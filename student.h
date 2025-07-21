#pragma once
#include <string>
#include <vector>

using namespace std;

class Student {
public:
    string name;
    int enrollment_no;
    int year;
    string batch; // Changed from int to string
    vector<string> subjects;
}; 