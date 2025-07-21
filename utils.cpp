#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream> // Added for file operations

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

std::vector<Student> load_students(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening " << filename << std::endl;
        return students;
    }

    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() == 4) {
            Student s;
            s.name = tokens[0];
            s.enrollment_no = std::stoi(tokens[1]);
            s.year = std::stoi(tokens[2]);
            s.batch = std::stoi(tokens[3]);
            students.push_back(s);
        }
    }
    return students;
}

std::vector<Exam> load_exams(const std::string& filename) {
    std::vector<Exam> exams;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening " << filename << std::endl;
        return exams;
    }

    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() == 3) {
            Exam e;
            e.exam_code = tokens[0];
            e.subject_name = tokens[1];
            e.semester = std::stoi(tokens[2]);
            exams.push_back(e);
        }
    }
    return exams;
}

std::vector<Classroom> load_classrooms(const std::string& filename) {
    std::vector<Classroom> classrooms;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening " << filename << std::endl;
        return classrooms;
    }

    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() == 4) {
            Classroom c;
            c.room_id = tokens[0];
            c.capacity = std::stoi(tokens[3]);
            classrooms.push_back(c);
        }
    }
    return classrooms;
} 