#pragma once
#include <string>
#include <vector>
#include <map>
#include "student.h"
#include "exam.h"
#include "classroom.h"

using namespace std;

void clearScreen();
vector<string> split(const string& s, char delimiter);
vector<Student> load_students(const string& filename);
vector<Exam> load_exams(const string& filename);
vector<Classroom> load_classrooms(const string& filename);
void save_schedule_to_csv(const string& filename,
                          const map<int, vector<string>>& schedule,
                          int slots_per_day,
                          const map<string, int>& student_counts,
                          const vector<Classroom>& classrooms); 