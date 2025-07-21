#pragma once
#include <string>
#include <vector>
#include <map>
#include "classroom.h" // Include the Classroom class definition

using namespace std;

void start();

// Builds the conflict graph
void build_graph(const vector<string>& exam_group1,
                 const vector<string>& exam_group2,
                 const vector<string>& exam_group3,
                 map<string, vector<string>>& adj);

// Colors the graph and returns the number of colors used (days)
int color_graph(const map<string, vector<string>>& adj,
                map<string, int>& exam_colors);

// Groups exams by color/slot
map<int, vector<string>> group_exams_by_slot(
    const map<string, int>& exam_colors);

void display(int total_slots,
             const map<int, vector<string>>& schedule,
             string name,
             int semester,
             const map<string, int>& student_counts,
             const vector<Classroom>& classrooms); 