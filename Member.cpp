#include "Member.h"
#include <iostream>
using namespace std;

Member::Member(string userId, string name, string email, string password, string studentId)
    : User(userId, name, email, password, "Member") {
    this->studentId = studentId;
    this->borrowedCount = 0;

    for (int i = 0; i < 5; i++) {
        borrowedBooks[i] = "";
    }
}

string Member::getStudentId() const { return studentId; }
int Member::getBorrowedCount() const { return borrowedCount; }

bool Member::isValidStudentEmail(string email) {
    return email.find("@bucks.ac.uk") != string::npos;
}

void Member::displayInfo() const {
    User::displayInfo();
    cout << "Student ID: " << studentId << endl;
    cout << "Books Borrowed: " << borrowedCount << "/5" << endl;
    cout << "------------------------" << endl;
}

void Member::displayMenu() {
    cout << "\n=== MEMBER MENU ===\n";
    cout << "1. View My Information\n";
    cout << "2. Browse All Books\n";
    cout << "3. Search Books by Title\n";
    cout << "4. Search Books by Author\n";
    cout << "5. Borrow a Book\n";
    cout << "6. Return a Book\n";
    cout << "7. Reserve a Book\n";
    cout << "8. View My Borrowed Books\n";
    cout << "9. Logout\n";
    cout << "Enter your choice: ";
}

bool Member::borrowBook(string bookISBN) {
    if (borrowedCount >= 5) {
        cout << "You have already borrowed the maximum of 5 books." << endl;
        return false;
    }

    for (int i = 0; i < 5; i++) {
        if (borrowedBooks[i] == "") {
            borrowedBooks[i] = bookISBN;
            borrowedCount++;
            return true;
        }
    }

    return false;
}

bool Member::returnBook(string bookISBN) {
    for (int i = 0; i < 5; i++) {
        if (borrowedBooks[i] == bookISBN) {
            borrowedBooks[i] = "";
            borrowedCount--;
            return true;
        }
    }
    cout << "This book is not borrowed by you." << endl;
    return false;
}

bool Member::hasBook(string bookISBN) const {
    for (int i = 0; i < 5; i++) {
        if (borrowedBooks[i] == bookISBN) {
            return true;
        }
    }
    return false;
}

void Member::getBorrowedBooks(string books[]) const {
    for (int i = 0; i < 5; i++) {
        books[i] = borrowedBooks[i];
    }
}