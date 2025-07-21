#pragma once
#include <string>
#include <vector>

using namespace std;

class Student {
public:
    string name;
    int enrollment_no;
    int year;
    int batch;
    vector<string> subjects;
}; 