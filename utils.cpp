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

vector<Student> load_students(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << endl;
        return students;
    }

    string line;
    // Skip header
    getline(file, line);

    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        if (tokens.size() == 4) {
            Student s;
            s.name = tokens[0];
            s.enrollment_no = stoi(tokens[1]);
            s.year = stoi(tokens[2]);
            s.batch = stoi(tokens[3]);
            students.push_back(s);
        }
    }
    return students;
}

vector<Exam> load_exams(const string& filename) {
    vector<Exam> exams;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << endl;
        return exams;
    }

    string line;
    // Skip header
    getline(file, line);

    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        if (tokens.size() == 3) {
            Exam e;
            e.exam_code = tokens[0];
            e.subject_name = tokens[1];
            e.semester = stoi(tokens[2]);
            exams.push_back(e);
        }
    }
    return exams;
}

vector<Classroom> load_classrooms(const string& filename) {
    vector<Classroom> classrooms;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << endl;
        return classrooms;
    }

    string line;
    // Skip header
    getline(file, line);

    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        if (tokens.size() == 4) {
            Classroom c;
            c.room_id = tokens[0];
            c.capacity = stoi(tokens[3]);
            classrooms.push_back(c);
        }
    }
    return classrooms;
} 