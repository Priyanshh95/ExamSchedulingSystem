#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream> // Added for file operations
#include <algorithm> // For std::find_if
#include <map>

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

void save_schedule_to_csv(const string& filename,
                          const map<int, vector<string>>& schedule,
                          int slots_per_day,
                          const map<string, int>& student_counts,
                          const vector<Classroom>& classrooms) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file " << filename << " for writing." << endl;
        return;
    }

    file << "Day,Slot,ExamCode,StudentCount,ClassroomID,ClassroomCapacity\n";

    if (schedule.empty()) {
        return;
    }

    int total_slots = 0;
    for(const auto& pair : schedule) {
        total_slots = max(total_slots, pair.first);
    }
    
    int total_days = (total_slots + slots_per_day - 1) / slots_per_day;

    map<int, map<int, vector<Classroom>>> daily_slot_classrooms;
    for (int d = 1; d <= total_days; ++d) {
        for (int s = 1; s <= slots_per_day; ++s) {
            daily_slot_classrooms[d][s] = classrooms;
        }
    }

    for (auto const& pair : schedule) {
        int color = pair.first;
        const vector<string>& exams_in_slot = pair.second;

        int current_day = (color - 1) / slots_per_day + 1;
        int current_slot_in_day = (color - 1) % slots_per_day + 1;

        for (const auto& exam_code : exams_in_slot) {
            int num_students = student_counts.count(exam_code) ? student_counts.at(exam_code) : 0;
            
            vector<Classroom>& available_classrooms = daily_slot_classrooms[current_day][current_slot_in_day];
            
            auto it = find_if(available_classrooms.begin(), available_classrooms.end(),
                               [&](const Classroom& c) { return c.capacity >= num_students; });

            if (it != available_classrooms.end()) {
                file << current_day << ","
                     << current_slot_in_day << ","
                     << exam_code << ","
                     << num_students << ","
                     << it->room_id << ","
                     << it->capacity << "\n";
                available_classrooms.erase(it); // Mark classroom as used for this slot
            } else {
                file << current_day << ","
                     << current_slot_in_day << ","
                     << exam_code << ","
                     << num_students << ","
                     << "N/A" << ","
                     << "N/A" << "\n";
            }
        }
    }

    cout << "\n\t\tSchedule successfully saved to " << filename << endl;
} 