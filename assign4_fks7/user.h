//
//  user.h
//

#ifndef user_h
#define user_h
#include <string>

using namespace std;

class User {
public:
    User(string pUsername, unsigned long long pPasswordHash):username(pUsername), passwordHash(pPasswordHash){}
    string getUsername();
    bool authenticate (string password);
    bool setNewPassword (string password);
    unsigned long long getPasswordHash();
    
    
private:
    string username;
    unsigned long long passwordHash;
    unsigned long long hash(string s);
    bool meetsCriteria(string s);
    
};


#endif 
