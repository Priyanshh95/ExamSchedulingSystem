#pragma once
#include <string>
#include <vector>
#include <map>
#include "classroom.h"

using namespace std;

struct Seat {
    string student;
    bool occupied;
};

void displaySeatingArrangement(const Classroom& classroom, int num_students);
void generate_seating_plan_interactive(const map<int, vector<string>>& schedule,
                                     const map<string, int>& student_counts,
                                     const vector<Classroom>& classrooms);
void generate_seating_plan_standalone(); 