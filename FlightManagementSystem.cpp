// File Name: assign1_fks7.cpp
//
// Author: Faith Shaffer 
// Date: 2/5/2020
// Assignment Number: 1
// CS 2308.255 Spring 2020
// Instructor: Vladyslav Prokopenko
//
// This program displays a menu and asks the user to select one of the four options. The program will either display all of the flights, show the flights that depart from a given city, find a flight with the best distence to price ratio, or exit the program.

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Flight
{
    string from;        // where a flight departs from
    string to;          // destination of a flight
    double price;       // the price for a specific flight
    double distance;    // the ditance between two cities of a given flight
};

int readFlights(ifstream& file, Flight ID[])
{
    string fromStr;
    string toStr;
    string priceStr;
    string distanceStr;
    
    int size = 0;
    while (getline(file, ID[size].from, ',')) {
        
        getline(file, toStr, ',');
        ID[size].to = toStr;
        getline(file, priceStr, ',');
        ID[size].price = stoi(priceStr);
        getline(file, distanceStr);
        ID[size].distance = stoi(distanceStr);      // stoi - converts a string to an integer
        size++;
    }
    return size;
}

void printFlights(Flight ID[], int SIZE) {          // prints all of the flights available
    for (int i = 0; i < SIZE; i++)
    {
        cout << ID[i].from << " ";
        cout << ID[i].to << " ";
        cout << ID[i].price << " ";
        cout << ID[i].distance << " " << endl;
        
    }
}

void printFlightFrom(Flight ID[], int SIZE, string COD)     // prints flights from a certain city
{
    cout << "Please enter the city of departure:" << endl;
    cin >> COD;
    
    for (int i = 0; i < SIZE; i++)
    {
        if (ID[i].from == COD) {
            cout << ID[i].from << " ";
            cout << ID[i].to << " ";
            cout << ID[i].price << " ";
            cout << ID[i].distance << " " << endl;
        }
    }
}

double findHighestDistanceToPriceRatio(Flight ID[], int SIZE, int& flightIndex)
{
    double bestRatio = 0;
    for (int i = 0; i < SIZE; i++) {
        if ((ID[i].distance / ID[i].price) > bestRatio) {
            bestRatio = ID[i].distance / ID[i].price;
            flightIndex = i;
        }
    }
    return bestRatio;
}

int main()
{
    int size;
    ifstream file("Flights.csv");
    Flight ID[100];
    int menuOption = 0;
    const int SIZE =readFlights(file, ID);
    string COD;
    int x;
    
    do {
        cout << "Select the action:" << endl;
        cout << "1) Display all Flights" << endl;
        cout << "2) Show the flights that depart from a given city" << endl;
        cout << "3) Find a flight with the best distance to price ratio" << endl;
        cout << "4) Exit the program" << endl;
        cin >> menuOption;
        switch (menuOption) {
                
            case 1:
                printFlights(ID, SIZE);
                
                
                break;
            case 2:
                printFlightFrom(ID, SIZE, COD);
                
                break;
            case 3:
                
                
                cout << "The best distance to price ratio is " << findHighestDistanceToPriceRatio(ID, SIZE, x) << " km/$." << endl;
                
                cout << ID[x].from << " ";
                cout << ID[x].to << " ";
                cout << ID[x].price << " ";
                cout << ID[x].distance << " " << endl;
                
                break;
            case 4:
                
                
                
                return 0;
        }
    }
    while (menuOption != 4);
    file.close();
}
