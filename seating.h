#pragma once
#include <string>
#include <vector>

struct Seat {
    std::string student;
    bool occupied;
};

void displaySeatingArrangement(const std::string& classroom, int numRows, int numCols, const std::vector<std::string>& students);
void seating_arrangement_display(); 