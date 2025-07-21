#include "seating.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "classroom.h"
#include <limits> // Required for numeric_limits

using namespace std;

void displaySeatingArrangement(const Classroom& classroom, int num_students) {
    // For now, we'll ask for rows/cols, as this data isn't in classrooms.csv
    int numRows, numCols;
    cout << "\n\t\tFor classroom " << classroom.room_id << " (Capacity: " << classroom.capacity << "), enter seating dimensions.";
    cout << "\n\t\tEnter the number of rows: ";
    cin >> numRows;
    while(cin.fail() || numRows <= 0) {
        cout << "\n\t\tInvalid input. Please enter a positive number for rows: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> numRows;
    }

    cout << "\t\tEnter the number of columns: ";
    cin >> numCols;
    while(cin.fail() || numCols <= 0) {
        cout << "\n\t\tInvalid input. Please enter a positive number for columns: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> numCols;
    }

    if (numRows * numCols < num_students) {
        cout << "\n\t\tWarning: The provided dimensions (" << numRows * numCols << " seats) are not enough for " << num_students << " students.\n";
    }

    vector<vector<Seat>> seats(numRows, vector<Seat>(numCols));
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            seats[i][j].student = "Empty";
            seats[i][j].occupied = false;
        }
    }

    int student_placed = 0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (student_placed < num_students) {
                seats[i][j].student = "Student " + to_string(student_placed + 1);
                seats[i][j].occupied = true;
                student_placed++;
                if (j < numCols - 1) { // Skip one seat for social distancing
                    j++;
                }
            }
        }
    }

    cout << "\n\nSeating Arrangement for Classroom: " << classroom.room_id << "\n";
    cout << "-----------------------------------\n";
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            cout << seats[i][j].student;
            cout << (seats[i][j].student.size() < 8 ? "\t\t" : "\t");
        }
        cout << "\n";
    }
    cout << "-----------------------------------\n";
}

void generate_seating_plan_interactive(const map<int, vector<string>>& schedule,
                                     const map<string, int>& student_counts,
                                     const vector<Classroom>& classrooms) {
    cout << "\n\t\tEnter the exam code to generate a seating plan for: ";
    string exam_code;
    cin >> exam_code;

    int num_students = 0;
    if (student_counts.count(exam_code)) {
        num_students = student_counts.at(exam_code);
    } else {
        cout << "\n\t\tInvalid exam code.\n";
        return;
    }

    // Find the classroom assigned to this exam
    // This is a simplified search. A more robust way would be to store assignments.
    const Classroom* assigned_classroom = nullptr;
    for (const auto& cls : classrooms) {
        if (cls.capacity >= num_students) {
            assigned_classroom = &cls;
            break;
        }
    }

    if (assigned_classroom) {
        displaySeatingArrangement(*assigned_classroom, num_students);
    } else {
        cout << "\n\t\tCould not find a suitable classroom for this exam.\n";
    }
}

void generate_seating_plan_standalone() {
    cout << "\n\n\t\t--- Generate Seating Plan for a Single Exam ---\n";

    vector<Classroom> classrooms = load_classrooms("classrooms.csv");
    if (classrooms.empty()) {
        cerr << "\n\t\tError: Could not load classrooms.csv. Cannot proceed.\n";
        return;
    }

    string exam_code;
    int num_students;

    cout << "\n\t\tEnter the exam code (e.g., CS101): ";
    cin >> exam_code;
    cout << "\t\tEnter the total number of students for this exam: ";
    cin >> num_students;
    while(cin.fail() || num_students < 0) {
        cout << "\n\t\tInvalid input. Please enter a non-negative number for students: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> num_students;
    }

    const Classroom* assigned_classroom = nullptr;
    for (const auto& cls : classrooms) {
        if (cls.capacity >= num_students) {
            assigned_classroom = &cls;
            break;
        }
    }

    if (assigned_classroom) {
        displaySeatingArrangement(*assigned_classroom, num_students);
    } else {
        cout << "\n\t\tCould not find a suitable classroom for " << num_students << " students.\n";
    }
} 