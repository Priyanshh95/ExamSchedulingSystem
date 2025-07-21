#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
#include <sstream>
#include "scheduler.h"
#include "seating.h"
#include "utils.h"

using namespace std;
#define endl "\n"

void show_main_menu() {
    cout << "\n\n\t\t----------------- Exam Scheduling System Menu -----------------\n";
    cout << "\t\t1. Generate Full Exam Schedule (with classroom assignment)\n";
    cout << "\t\t2. Generate Seating Plan for a Single Exam\n";
    cout << "\t\t3. Exit\n";
    cout << "\t\t-----------------------------------------------------------------\n";
    cout << "\t\tEnter your choice: ";
}

int main()
{   
    int choice;
    do {
        show_main_menu();
        cin >> choice;

        // Input validation
        if (cin.fail()) {
            cin.clear(); // clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
            choice = 0; // set choice to a value that hits the default case
        }
        
        clearScreen();

        switch(choice) {
            case 1:
                run_exam_scheduler();
                break;
            case 2:
                generate_seating_plan_standalone();
                break;
            case 3:
                cout << "\n\n\t\tThank you for using the Exam Scheduling System!\n";
                break;
            default:
                cout << "\n\t\tInvalid choice. Please try again.\n";
        }
        if (choice != 3) {
            cout << "\n\t\tPress Enter to return to the menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            clearScreen();
        }
    } while(choice != 3);

	return 0;
}
