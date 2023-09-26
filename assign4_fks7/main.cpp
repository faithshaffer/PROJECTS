// File Name: assign4_fks7.zip
//
// Author: Faith Shaffer
// Date: 4/8/2020
// Assignment Number: 4
// CS 2308.255 Spring 2020
// Instructor: Vladyslav Prokopenko
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "user.h"
#include "user.cpp"

using namespace std;

vector<User> loadUserDatabase(istream &in) {
    string userName;
    unsigned long long passwordHash;
    vector<User> userDatabase;
    while (in >> userName >> passwordHash)
        userDatabase.push_back(User(userName,passwordHash));
    return userDatabase;
}

void saveUserDataBase(ofstream &out, vector<User> userDatabase) {
    for (int i = 0; i < userDatabase.size(); i++) {
        out << userDatabase[i].getUsername();
        cout << " ";
        cout << userDatabase[i].getPasswordHash() << endl;
    }
    out.close();
}

int main() {
    string fileName = "userDatabase.txt";
    ifstream inputFile(fileName.c_str());
    ofstream outputFile(fileName.c_str());
    vector<User> userDatabase = loadUserDatabase(inputFile);
    string username, oldPass, newPass;
    
    cout << "Please enter your username: " << endl;
    cin >> username;
    cout << "Please enter your old password: " << endl;
    cin >> oldPass;
    cout << "Please enter your new password: " << endl;
    cin >> newPass;
    
    bool userExists = false;
    if (!userExists) {
        cout << "User with the given name does not exist, password not changed." << endl;
    }
    
    if (userExists == false) {
        for (int i = 0; i < userDatabase.size(); i++) {
            if (userDatabase[i].getUsername() == username) {
                userExists = true;
                bool userFound = userDatabase[i].authenticate(oldPass);
                if (userFound) {
                bool check = userDatabase[i].setNewPassword(newPass);
                if (check)
                    cout << "Password has been changed for user: " << username << endl;
                else
                    cout << "New password does not meet criteria, password not changed." << endl;
            }
            else {
                cout << "Old password is incorrect, password not changed." << endl;
            }
            
                }
            }
        }
    saveUserDataBase(outputFile, userDatabase);
    }

