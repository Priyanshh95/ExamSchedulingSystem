#include "seating.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void displaySeatingArrangement(const string& classroom, int numRows, int numCols, const vector<string>& students) {
    vector<vector<Seat>> seats(numRows, vector<Seat>(numCols));

    // Initialize seats with empty and not occupied
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            seats[i][j].student = "Empty";
            seats[i][j].occupied = false;
        }
    }

    // Assign students to seats
    int studentIndex = 0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (studentIndex < students.size()) {
                seats[i][j].student = students[studentIndex];
                seats[i][j].occupied = true;
                studentIndex += 2; // Skip one seat
                if (j < numCols - 1) {
                    j++; // Skip one seat
                }
            }
        }
    }

    // Display seating arrangement
    cout << "Seating Arrangement for Classroom: " << classroom << "\n";
    cout << "-----------------------------------\n";
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            cout << seats[i][j].student;
            if (seats[i][j].occupied) {
                // Pad with spaces for alignment
                cout << " ";
                if (seats[i][j].student.size() < 6) {
                    cout << "\t\t"; // Extra tab for shorter names
                } else {
                    cout << "\t";
                }
            } else {
                cout << "(Empty)\t"; // Mark empty seats
            }
        }
        cout << "\n";
    }
    cout << "-----------------------------------\n";
}

// to display the final seating arrangement

void seating_arrangement_display() {
    
    string classroom;
    int numRows, numCols, totalSeats, startRoll, endRoll;

    cout << "Enter the classroom name: ";
    getline(cin >> ws, classroom);

    cout << "Enter the number of rows: ";
    cin >> numRows;

    cout << "Enter the number of columns: ";
    cin >> numCols;

    totalSeats = numRows * numCols;

    cout << "Enter the starting roll number: ";
    cin >> startRoll;

    cout << "Enter the ending roll number: ";
    cin >> endRoll;

    if (startRoll <= 0 || endRoll <= 0 || startRoll > endRoll) {
        cout << "Invalid roll numbers. Starting roll must be less than or equal to the ending roll.\n";
        
    }

    vector<string> students;
    for (int roll = startRoll; roll <= endRoll; ++roll) {
        students.push_back("Student " + to_string(roll));
    }

    if (totalSeats > 0) {
        displaySeatingArrangement(classroom, numRows, numCols, students);
    } else {
        cout << "Invalid input. Total number of seats must be positive.\n";
        
    }

} 