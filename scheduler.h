#pragma once
#include <string>
#include <vector>
#include <map>

void start();

// Builds the conflict graph
void build_graph(const std::vector<std::string>& exam_group1,
                 const std::vector<std::string>& exam_group2,
                 const std::vector<std::string>& exam_group3,
                 std::map<std::string, std::vector<std::string>>& adj);

// Colors the graph and returns the number of colors used (days)
int color_graph(const std::map<std::string, std::vector<std::string>>& adj,
                std::map<std::string, int>& exam_colors);

// Groups exams by color/slot
std::map<int, std::vector<std::string>> group_exams_by_slot(
    const std::map<std::string, int>& exam_colors);

void display(int days, const std::map<int, std::vector<std::string>>& schedule, std::string name, int semester); 