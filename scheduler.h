#pragma once
#include <string>
#include <vector>
#include <map>

void start();
void initialize(int n1, std::string arr1[], int n2, std::string arr2[], int n3, std::string arr3[], std::map<std::string, std::vector<std::string>> &adj, std::map<std::string,int> &color);
std::map<int, std::vector<std::string>> schedule(std::map<std::string, std::vector<std::string>> &adj, std::map<std::string, int> &color, int &max_days);
void display(int days, std::map<int, std::vector<std::string>> &hash, std::string name, int semester); 