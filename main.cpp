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

using namespace std ;
#define endl "\n"

int main()
{   
    bool choice = false;
    do {
        start();
        cout<<"\n\n\t\tDo You wish to continue Again.. Press (1 for Yes) & (2 for No): ";
        string inp; 
        cin>>inp;
        if(inp=="1") choice = true; 
        else choice = false;
        clearScreen();
    } while(choice);
	return 0;
}
