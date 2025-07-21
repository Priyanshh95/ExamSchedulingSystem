#pragma once
#include <string>
#include <vector>
#include "student.h"
#include "exam.h"
#include "classroom.h"

using namespace std;

void clearScreen();
vector<string> split(const string& s, char delimiter);
vector<Student> load_students(const string& filename);
vector<Exam> load_exams(const string& filename);
vector<Classroom> load_classrooms(const string& filename); 