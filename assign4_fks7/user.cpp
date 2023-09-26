//
//  user.cpp
//

#include "user.h"
#include <iostream>
#include <string>

using namespace std;

unsigned long long User :: hash(string s) {{
        unsigned long long h = 0;
        for (int i = 0; i < s.size(); i++) {
            h = s[i] + (h << 6) + (h << 16) - h;
        }
        return h;
    }
}

bool User:: meetsCriteria(string password) {
    int const n = 0;
    if (n >=8) {
        if (all_of(password.begin(), password.end(), &::isupper)){
            if (all_of(password.begin(), password.end(), &::islower)){
                if (all_of(password.begin(), password.end(), &::isdigit)){
                }
            }
        }
    }
    return true;
}

string User:: getUsername() {
    return username;
}

unsigned long long User:: getPasswordHash() {
    return passwordHash;
}

bool User:: authenticate(string password) {
    unsigned long long beHash = hash(password);
    if (beHash == passwordHash) {
        return true;
    }
    else
        return false;
}

bool User:: setNewPassword(string password) {
    if (meetsCriteria(password) == false)
        return false;
    
    unsigned long long qHash = hash(password);
    passwordHash = qHash;
    return true;
}
