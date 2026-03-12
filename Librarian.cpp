#include "Librarian.h"
#include <iostream>
using namespace std;

Librarian::Librarian(string userId, string name, string email, string password, string staffId, string department)
    : User(userId, name, email, password, "Librarian") {
    this->staffId = staffId;
    this->department = department;
}

string Librarian::getStaffId() const { return staffId; }
string Librarian::getDepartment() const { return department; }

void Librarian::displayInfo() const {
    User::displayInfo();
    cout << "Staff ID: " << staffId << endl;
    cout << "Department: " << department << endl;
    cout << "------------------------" << endl;
}

void Librarian::displayMenu() {
    cout << "\n=== LIBRARIAN MENU ===\n";
    cout << "1. View My Information\n";
    cout << "2. View All Books\n";
    cout << "3. Add New Book\n";
    cout << "4. Remove Book\n";
    cout << "5. Update Book Information\n";
    cout << "6. View Overdue Books Report\n";
    cout << "7. View Borrowed Books\n";
    cout << "8. View Reserved Books\n";
    cout << "9. Logout\n";
    cout << "Enter your choice: ";
}