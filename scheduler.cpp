#include "scheduler.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
#include <sstream>
#include "seating.h"
#include "utils.h"

using namespace std;

void initialize(int n1, string arr1[], int n2, string arr2[], int n3, string arr3[], map<string, vector<string>> &adj, map<string, int> &color) {
    
    for(int i=0;i<n1; i++) {
        for(int j=0;j<n1; j++) {
            if(i!=j)
            adj[arr1[i]].push_back(arr1[j]);
        }
    }
    for(int i=0;i<n2; i++) {
        for(int j=0;j<n2; j++) {
            if(i!=j)
            adj[arr2[i]].push_back(arr2[j]);
        }
    }
    for(int i=0;i<n3; i++) {
        for(int j=0;j<n3; j++) {
            if(i!=j)
            adj[arr3[i]].push_back(arr3[j]);
        }
    }
    
    //Initialize the color of each node to -1
    for(auto x: adj) {
        color[x.first]=-1;
    }

    color[adj.begin()->first]=1;
    vector<bool> alreadyAssigned(n1+n2+n3);

    auto it= adj.begin();
    it++;
    map<string, vector<string>>::iterator i;
    for(i=it; i!=adj.end(); i++) {
        fill(alreadyAssigned.begin(), alreadyAssigned.end(), false);

        for (auto av : adj[i->first])
            if (color[av] != -1)
                alreadyAssigned[color[av]] = true;

        int c;
        for (c = 1; c <= n1+n2+n3 ; c++)
            if (alreadyAssigned[c] == false)
                break;

        color[i->first] = c;
    }
}


map<int, vector<string>> schedule(map<string, vector<string>> &adj, map<string, int> &color, int &max_days) {
    map<int, vector<string>> hash;
    for (auto ele: adj) {
        // cout << "Vertex  " << ele.first << " ---> Color " << color[ele.first] << endl;
        hash[color[ele.first]].push_back(ele.first);
    }

    int mx=INT_MIN;
    for(auto ele: color)
    {
        mx= max(mx, ele.second);
    }

    //cout << "\nNumber of colors required: " << mx << endl;
    
    max_days=mx;
    
    return hash;
}

void display(int days, map<int, vector<string>> &hash, string name, int semester) {
    
    cout<<"\n\t\t\tNumber of Days to take Examinations would be: "<<days<<"\n";
    
    cout<<"\n\t\t\tHow many Maximum number of Slots per Day you Want? ";
    int slots; cin>>slots;
    
    // Clearing Screen
    clearScreen();
    
    cout<<"\n\n\t\t----------------------------- Examination Schedule ------------------------------";
    cout<<"\n\n\t\t\t\t\tCollege: "<<name<<"\tSemester: "<<((semester==1?"ODD":"EVEN"));
    int day_cnt=1, slot_cnt=1; 
    cout<<"\n\n\t\t\t-----------------------Day "<<day_cnt<<"-----------------------\n\n";
    for(auto it: hash) {
        cout<<"\t\t\t\tSlot "<<slot_cnt<<" -> ";
        for(auto k: it.second) cout<<k<<" , ";
        cout<<"\n";
        slot_cnt++;
        if(slot_cnt>slots) {
            day_cnt++;
            slot_cnt=1;
            cout<<"\n\t\t\t-----------------------Day "<<day_cnt<<"-----------------------\n\n";
        }
    }
    seating_arrangement_display();
}

void start() {
    cout<<"\n\n\n\t\t----------------------------Welcome To Exam Time Table Scheduler------------------------\n\n\n\n";
    
    string name="JIIT";
    cout<<"\n\t\t\tEnter Odd(1) or Even(2) Semester: ";
    int semester; 
    cin>>semester;
    
    // Clearing Screen
    clearScreen();
    cout<<"\n\n\t\t-----------------Currently Supporting upto 3 Semesters-------------------";
    
    cout<<"\n\n\t\t\tEnter no. of Semester "<<semester<<" subjects: ";
    int n1=5; 
    
    cout<<"\n\t\t\tEnter subject codes: ";
    string arr1[n1];
    

    // Open the CSV file
    ifstream file("exam.csv");
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }
    int i = 0;
    // Variables to store each line and tokens
    string line;
    vector<string> tokens;

    // Skip the header line
    getline(file, line);

    // Read each line of the file
    while (getline(file, line)) {
        // Split the line by comma
        tokens = split(line, ',');

        // Check if the semester is 1
        if(semester==1){
            if (tokens.size() >= 3 && tokens[2] == "1") {
            // Print the exam code
            arr1[i]=tokens[0];
            i++;
        }
        }
        else{
            if (tokens.size() >= 3 && tokens[2] == "2") {
            // Print the exam code
            arr1[i]=tokens[0];
            i++;
        }
        }
        
    }

    // Close the file
    file.close();
    // Clearing Screen
    clearScreen();
    
    cout<<"\n\n\t\t\tEnter no. of Semester "<<(semester==1?"3":"4")<<" subjects including the previous semester overload subjects:  ";
    int n2=5;
    cout<<"\n\t\t\tEnter subject codes: ";
    string arr2[n2];
    // Open the CSV file
    ifstream file2("exam.csv");
    if (!file2.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }
    i = 0;
    // Variables to store each line and tokens
    string line2;
    vector<string> tokens2;

    // Skip the header line
    getline(file2, line2);

    // Read each line of the file
    while (getline(file2, line2)) {
        // Split the line by comma
        tokens2 = split(line2, ',');

        // Check if the semester is 1
        if(semester==1){
            if (tokens2.size() >= 3 && tokens2[2] == "3") {
            // Print the exam code
            arr2[i]=tokens2[0];
            i++;
        }
        }
        else{
            if (tokens2.size() >= 3 && tokens2[2] == "4") {
            // Print the exam code
            arr2[i]=tokens2[0];
            i++;
        }
        }
    }

    // Close the file
    file.close();
    
    // Clearing Screen
    clearScreen();

    cout<<"\n\t\t\tEnter no. of Semester "<<(semester==1?"5":"7")<<" subjects including the previous semster overloads: ";
    int n3=5;
    string arr3[n3];
    cout<<"\n\t\t\tEnter subject codes: ";
    // Open the CSV file
    ifstream file3("exam.csv");
    if (!file3.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }
    i = 0;
    // Variables to store each line and tokens
    string line3;
    vector<string> tokens3;

    // Skip the header line
    getline(file3, line3);

    // Read each line of the file
    while (getline(file3, line3)) {
        // Split the line by comma
        tokens3 = split(line3, ',');

        // Check if the semester is 1
        if(semester==1){
            if (tokens3.size() >= 3 && tokens3[2] == "5") {
            // Print the exam code
            arr3[i]=tokens3[0];
            i++;
        }
        }
        else{
            if (tokens3.size() >= 3 && tokens3[2] == "6") {
            // Print the exam code
            arr3[i]=tokens3[0];
            i++;
        }
        }
    }

    // Close the file
    file.close();

    // Clearing Screen
    clearScreen();
    
    // Initializing Graph 
    map<string, vector<string>> adj;
    map<string, int> color; 
    initialize(n1,arr1,n2,arr2,n3,arr3, adj, color);
    
    // Scheduling the Slots
    int max_days=-1;
    map<int, vector<string>> exam_schedule = schedule(adj,color, max_days);
    
    // Displaying the Results 
    display(max_days, exam_schedule, name, semester);
    
} 