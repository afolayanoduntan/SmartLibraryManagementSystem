#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class User {
protected:
    string userId;
    string name;
    string email;
    string password;
    string role;

public:
    User(string userId, string name, string email, string password, string role);
    virtual ~User();

    string getUserId() const;
    string getName() const;
    string getEmail() const;
    string getRole() const;
    string getPassword() const;

    virtual bool login(string enteredPassword);
    virtual void logout();
    virtual void displayMenu() = 0;
    virtual void displayInfo() const;
};

#endif