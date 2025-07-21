#include "scheduler.h"
#include "seating.h"
#include "utils.h"
#include "exam.h"
#include "classroom.h"
#include "student.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
#include <sstream>

using namespace std;

void build_graph(const vector<string>& exam_group1,
                 const vector<string>& exam_group2,
                 const vector<string>& exam_group3,
                 map<string, vector<string>>& adj) {
    auto add_edges = [&](const vector<string>& group) {
        for (size_t i = 0; i < group.size(); ++i) {
            for (size_t j = 0; j < group.size(); ++j) {
                if (i != j) {
                    adj[group[i]].push_back(group[j]);
                }
            }
        }
    };
    add_edges(exam_group1);
    add_edges(exam_group2);
    add_edges(exam_group3);
}

int color_graph(const map<string, vector<string>>& adj, map<string, int>& exam_colors) {
    vector<string> exams;
    for (const auto& pair : adj) {
        exams.push_back(pair.first);
        exam_colors[pair.first] = -1;
    }

    int max_colors = 0;
    if (!exams.empty()) {
        exam_colors[exams[0]] = 1;
        max_colors = 1;
    }

    for (size_t i = 1; i < exams.size(); ++i) {
        vector<bool> available_colors(exams.size() + 1, true);
        const auto& neighbors = adj.at(exams[i]);
        for (const auto& neighbor : neighbors) {
            if (exam_colors[neighbor] != -1) {
                available_colors[exam_colors[neighbor]] = false;
            }
        }

        int color;
        for (color = 1; color <= (int)exams.size(); ++color) {
            if (available_colors[color]) {
                break;
            }
        }
        exam_colors[exams[i]] = color;
        if (color > max_colors) {
            max_colors = color;
        }
    }
    return max_colors;
}

map<int, vector<string>> group_exams_by_slot(const map<string, int>& exam_colors) {
    map<int, vector<string>> schedule;
    for (const auto& pair : exam_colors) {
        schedule[pair.second].push_back(pair.first);
    }
    return schedule;
}

void start() {
    cout << "\n\n\n\t\t----------------------------Welcome To Exam Time Table Scheduler------------------------\n\n\n\n";

    vector<Exam> all_exams = load_exams("exam.csv");
    if (all_exams.empty()) {
        cerr << "Could not load exams. Exiting." << endl;
        return;
    }

    string name = "JIIT";
    cout << "\n\t\t\tEnter Odd(1) or Even(2) Semester: ";
    int semester_choice;
    cin >> semester_choice;
    clearScreen();

    vector<string> sem1_exams, sem2_exams, sem3_exams;
    if (semester_choice == 1) { // Odd semester
        for (const auto& exam : all_exams) {
            if (exam.semester == 1) sem1_exams.push_back(exam.exam_code);
            if (exam.semester == 3) sem2_exams.push_back(exam.exam_code);
            if (exam.semester == 5) sem3_exams.push_back(exam.exam_code);
        }
    } else { // Even semester
        for (const auto& exam : all_exams) {
            if (exam.semester == 2) sem1_exams.push_back(exam.exam_code);
            if (exam.semester == 4) sem2_exams.push_back(exam.exam_code);
            if (exam.semester == 6) sem3_exams.push_back(exam.exam_code);
        }
    }

    map<string, vector<string>> adj;
    build_graph(sem1_exams, sem2_exams, sem3_exams, adj);

    map<string, int> exam_colors;
    int days_required = color_graph(adj, exam_colors);

    map<int, vector<string>> exam_schedule = group_exams_by_slot(exam_colors);

    display(days_required, exam_schedule, name, semester_choice);
}

void display(int days, const map<int, vector<string>>& schedule, string name, int semester) {
    cout << "\n\t\t\tNumber of Days to take Examinations would be: " << days << "\n";
    cout << "\n\t\t\tHow many Maximum number of Slots per Day you Want? ";
    int slots;
    cin >> slots;
    clearScreen();

    cout << "\n\n\t\t----------------------------- Examination Schedule ------------------------------";
    cout << "\n\n\t\t\t\t\tCollege: " << name << "\tSemester: " << (semester == 1 ? "ODD" : "EVEN");
    int day_cnt = 1, slot_cnt = 1;
    cout << "\n\n\t\t\t-----------------------Day " << day_cnt << "-----------------------\n\n";
    for (auto const& pair : schedule) {
        cout << "\t\t\t\tSlot " << slot_cnt << " -> ";
        const std::vector<std::string>& exams = pair.second;
        for (size_t i = 0; i < exams.size(); ++i) {
            cout << exams[i] << (i == exams.size() - 1 ? "" : " , ");
        }
        cout << "\n";
        slot_cnt++;
        if (slot_cnt > slots) {
            day_cnt++;
            slot_cnt = 1;
            cout << "\n\t\t\t-----------------------Day " << day_cnt << "-----------------------\n\n";
        }
    }
    seating_arrangement_display();
} 