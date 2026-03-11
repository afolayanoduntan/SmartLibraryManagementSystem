#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include <string>

class Member : public User {
private:
    string borrowedBooks[5];
    int borrowedCount;
    string studentId;

public:
    Member(string userId, string name, string email, string password, string studentId);

    string getStudentId() const;
    int getBorrowedCount() const;

    static bool isValidStudentEmail(string email);

    void displayInfo() const override;
    void displayMenu() override;

    bool borrowBook(string bookISBN);
    bool returnBook(string bookISBN);
    bool hasBook(string bookISBN) const;
    void getBorrowedBooks(string books[]) const;
};

#endif