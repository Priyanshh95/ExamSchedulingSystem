#pragma once
#include <string>
#include <vector>
#include "student.h"
#include "exam.h"
#include "classroom.h"

void clearScreen();
std::vector<std::string> split(const std::string& s, char delimiter);
std::vector<Student> load_students(const std::string& filename);
std::vector<Exam> load_exams(const std::string& filename);
std::vector<Classroom> load_classrooms(const std::string& filename); 