#include "Admin.h"
#include <iostream>
using namespace std;

Admin::Admin(string userId, string name, string email, string password, string staffId, string department)
    : User(userId, name, email, password, "Admin") {
    this->staffId = staffId;
    this->department = department;
}

string Admin::getStaffId() const { return staffId; }
string Admin::getDepartment() const { return department; }

void Admin::displayInfo() const {
    User::displayInfo();
    cout << "Staff ID: " << staffId << endl;
    cout << "Department: " << department << endl;
    cout << "------------------------" << endl;
}

void Admin::displayMenu() {
    cout << "\n=== ADMIN MENU ===\n";
    cout << "1. View My Information\n";
    cout << "2. Manage Member Accounts\n";
    cout << "3. Manage Librarian Accounts\n";
    cout << "4. Set Library Rules\n";
    cout << "5. Logout\n";
    cout << "Enter your choice: ";
}