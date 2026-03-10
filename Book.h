#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
    string isbn;
    string title;
    string author;
    string status;
    time_t dueDate;
    string borrowedBy;
    string reservedBy;
    time_t reservationDate;

public:
    Book(string isbn, string title, string author);
    
    string getISBN() const;
    string getTitle() const;
    string getAuthor() const;
    string getStatus() const;
    string getBorrowedBy() const;
    string getReservedBy() const;
    time_t getDueDate() const;
    time_t getReservationDate() const;

    void setTitle(string newTitle);
    void setAuthor(string newAuthor);
    
    bool borrow(string memberEmail);
    bool returnBook();
    bool reserve(string memberEmail);
    
    void displayInfo() const;
    void displayBrief() const;
    
    bool isAvailable() const;
    bool isBorrowedBy(string memberEmail) const;

    bool isOverdue() const;
    int getDaysOverdue() const;
    string getDueDateString() const;

    void setStatus(string newStatus);
    void setBorrowedBy(string email);
    void setReservedBy(string email);
    void setDueDate(time_t date);
    void setReservationDate(time_t date);
    bool isReservationExpired() const;

    string getPassword() const;
};

#endif