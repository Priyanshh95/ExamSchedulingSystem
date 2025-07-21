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

    // Load all necessary data from CSV files
    vector<Exam> all_exams = load_exams("exam.csv");
    vector<Student> all_students = load_students("students.csv");
    vector<Classroom> all_classrooms = load_classrooms("classrooms.csv");

    if (all_exams.empty() || all_students.empty() || all_classrooms.empty()) {
        cerr << "Error loading data files. Please ensure exam.csv, students.csv, and classrooms.csv are present and not empty." << endl;
        return;
    }

    // --- Estimate student counts per exam ---
    // This is an estimation because we don't have direct student-to-exam enrollment data.
    // We assume students of a certain year take all exams of the corresponding semesters.
    map<int, int> students_per_year;
    for (const auto& s : all_students) {
        students_per_year[s.year]++;
    }

    map<string, int> student_counts_per_exam;
    int year_for_sem_group1 = 2023; // Most recent year
    int year_for_sem_group2 = 2022;
    int year_for_sem_group3 = 2021; // Oldest year (placeholder)

    string name = "JIIT";
    cout << "\n\t\t\tEnter Odd(1) or Even(2) Semester: ";
    int semester_choice;
    cin >> semester_choice;
    clearScreen();

    vector<string> sem1_exams, sem2_exams, sem3_exams;
    if (semester_choice == 1) { // Odd semester
        for (const auto& exam : all_exams) {
            if (exam.semester == 1) {
                sem1_exams.push_back(exam.exam_code);
                student_counts_per_exam[exam.exam_code] = students_per_year[year_for_sem_group1];
            }
            if (exam.semester == 3) {
                sem2_exams.push_back(exam.exam_code);
                student_counts_per_exam[exam.exam_code] = students_per_year[year_for_sem_group2];
            }
            if (exam.semester == 5) {
                sem3_exams.push_back(exam.exam_code);
                student_counts_per_exam[exam.exam_code] = students_per_year[year_for_sem_group3]; // Assumed count
            }
        }
    } else { // Even semester
        for (const auto& exam : all_exams) {
            if (exam.semester == 2) {
                sem1_exams.push_back(exam.exam_code);
                student_counts_per_exam[exam.exam_code] = students_per_year[year_for_sem_group1];
            }
            if (exam.semester == 4) {
                sem2_exams.push_back(exam.exam_code);
                student_counts_per_exam[exam.exam_code] = students_per_year[year_for_sem_group2];
            }
            if (exam.semester == 6) {
                sem3_exams.push_back(exam.exam_code);
                student_counts_per_exam[exam.exam_code] = students_per_year[year_for_sem_group3]; // Assumed count
            }
        }
    }

    map<string, vector<string>> adj;
    build_graph(sem1_exams, sem2_exams, sem3_exams, adj);

    map<string, int> exam_colors;
    int total_slots = color_graph(adj, exam_colors);

    map<int, vector<string>> exam_schedule = group_exams_by_slot(exam_colors);

    display(total_slots, exam_schedule, name, semester_choice, student_counts_per_exam, all_classrooms);
}

void display(int total_slots,
             const map<int, vector<string>>& schedule,
             string name,
             int semester,
             const map<string, int>& student_counts,
             const vector<Classroom>& classrooms) {
    cout << "\n\t\t\tTotal slots required for all exams: " << total_slots << "\n";
    cout << "\n\t\t\tHow many Maximum number of Slots per Day you Want? ";
    int slots_per_day;
    cin >> slots_per_day;
    clearScreen();

    int total_days = (total_slots + slots_per_day - 1) / slots_per_day;
    cout << "\n\t\t\tThis schedule will take " << total_days << " days.\n";

    cout << "\n\n\t\t----------------------------- Examination Schedule ------------------------------";
    cout << "\n\n\t\t\t\t\tCollege: " << name << "\tSemester: " << (semester == 1 ? "ODD" : "EVEN");

    map<int, map<int, vector<Classroom>>> daily_slot_classrooms;
    for (int d = 1; d <= total_days; ++d) {
        for (int s = 1; s <= slots_per_day; ++s) {
            daily_slot_classrooms[d][s] = classrooms;
        }
    }

    int day_cnt = 0;
    for (auto const& pair : schedule) {
        int color = pair.first;
        const vector<string>& exams_in_slot = pair.second;

        int current_day = (color - 1) / slots_per_day + 1;
        int current_slot_in_day = (color - 1) % slots_per_day + 1;

        if (current_day > day_cnt) {
            day_cnt = current_day;
            cout << "\n\n\t\t\t-----------------------Day " << day_cnt << "-----------------------\n\n";
        }

        cout << "\t\t\t\tSlot " << current_slot_in_day << ":\n";

        for (const auto& exam_code : exams_in_slot) {
            int num_students = student_counts.count(exam_code) ? student_counts.at(exam_code) : 0;

            vector<Classroom>& available_classrooms = daily_slot_classrooms[current_day][current_slot_in_day];
            
            auto it = find_if(available_classrooms.begin(), available_classrooms.end(),
                               [&](const Classroom& c) { return c.capacity >= num_students; });

            cout << "\t\t\t\t  - Exam: " << exam_code << " (" << num_students << " students) -> ";
            if (it != available_classrooms.end()) {
                cout << "Classroom: " << it->room_id << " (Capacity: " << it->capacity << ")\n";
                available_classrooms.erase(it);
            } else {
                cout << "No suitable classroom found!\n";
            }
        }
    }
    seating_arrangement_display();
} 