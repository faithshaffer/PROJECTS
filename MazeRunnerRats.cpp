// File Name: assign7_fks7.cpp
//
// Author: Faith Shaffer
// Date: 12/2/19
// Assignment Number: 7
// CS 1428.003 Fall 2019
// Instructor: Jill Seaman

/* This program inputs the maze time of each rat from the user, displays each name with the weight, time and rating of each rat, and calculates the average weight of the rats and which one was the fastest.
*/

#include <iostream>
#include <iomanip>
using namespace std;

int const NUM_OF_RATS = 7; // Constant that equals the number of rats

// Structure that stores variables name, weight, time.
struct ratLab {
    string name; // Holds names of all of the rats.
    float weight; // Holds weight of each rat.
    int time; // Hold the maze times of each rat.
    
};

// Stores names and weights of the rats
ratLab rats[NUM_OF_RATS] = {
    {"Ben",6.5},
    {"Fred",5.8},
    {"Splinter",7.7},
    {"Lima Bean",6.5},
    {"Black Bean",5.8},
    {"Big Pook",9.8},
    {"Tiger",7.7}
    
};

// Function that finds the average weight of rats.
double averageWeight() {
    float sum = 0.0, avg=0;
    int length=7;
    
    for (int i=0; i < length; i++) {
        sum += rats[i].weight;
    }
    
    avg = (sum / length);
    cout << setprecision(2);
    
    return avg;
}

// Finds the rat with the fastest time.
int fastestTime() {
    int n = 7;
    int fastestRat =0;
    for (int i=0; i<n; i++) {
        if (rats[fastestRat].time > rats[i].time) {
            fastestRat= i;
        }
    }

    return fastestRat;
}

// Function that displays the name, weigt, time, and rating of the rats.
void displayTable(ratLab[]) {
        cout<<endl
        <<setw(14)<<left<<"Name"<<setw(7)<<right<<"Weight"<<setw(6)<<right
        <<"Time"<<setw(2)<<""<<"Rating"<< endl;
        
        for(int i=0;i<NUM_OF_RATS; i++)
        {
            // IF TIME IS LESS THAN 30 OUTPUTS "SUPERIOR"
            if (rats[i].time<30)
            {
                cout<<setw(14)<<left<<rats[i].name<<setw(6)<<right<<rats[i].weight
                <<setw(6)<<right<<rats[i].time<< setw(3)<<""<<"Superior"<<endl;
            }
            //IF TIME IS GREATER THAN 30 BUT LESS THAN 35 OUTPUTS "NORMAL"
            else if (rats[i].time>=30 && rats[i].time<35)
            {
                cout<<setw(14)<<left<<rats[i].name<<setw(6)<<right<<rats[i].weight
                <<setw(6)<<right<<rats[i].time<< setw(3)<<""<<"Normal"<<endl;
            }
            //IF TIME IS GREATER THAN 35 OUTPUTS "SLOW"
            else if (rats[i].time>=35)
            {
                cout<<setw(14)<<left<<rats[i].name<<setw(6)<<right<<rats[i].weight
                <<setw(6)<<right<<rats[i].time<< setw(3)<<""<<"Slow"<<endl;
            }
            
            
        }
}

// Inputs maze times of each rat from user.
void mazeTimes() {
    const int numOfRats = 7;
    int times[numOfRats];
    cout << "Enter the maze time for each rat: " << endl;
    
    for (int i=0; i < numOfRats; i++) {
        cout << rats[i].name << ": ";
        cin >> rats[i].time;
    }
    return;
}

int main() {
    mazeTimes();
    displayTable(rats);
    cout << endl;
    cout << "Average weight: " << averageWeight() << endl;
    int x = fastestTime();
    cout << "Fastest Rat: " << rats[x].name << " Time: " << rats[x].time << endl;
    
    return 0;
}

