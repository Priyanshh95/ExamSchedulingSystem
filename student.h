#pragma once
#include <string>
#include <vector>

class Student {
public:
    std::string name;
    int enrollment_no;
    int year;
    int batch;
    std::vector<std::string> subjects;
}; 