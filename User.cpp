#include "User.h"
#include <iostream>

using namespace std;

User::User(string userId, string name, string email, string password, string role) {
    this->userId = userId;
    this->name = name;
    this->email = email;
    this->password = password;
    this->role = role;
}

User::~User() {
}

string User::getUserId() const { return userId; }
string User::getName() const { return name; }
string User::getEmail() const { return email; }
string User::getRole() const { return role; }
string User::getPassword() const { return password; }

bool User::login(string enteredPassword) {
    if (this->password == enteredPassword) {
        cout << "Login successful! Welcome, " << name << " (" << role << ")" << endl;
        return true;
    } else {
        cout << "Invalid password." << endl;
        return false;
    }
}

void User::logout() {
    cout << "Goodbye, " << name << "!" << endl;
}

void User::displayInfo() const {
    cout << "ID: " << userId << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Role: " << role << endl;
}
