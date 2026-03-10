#include "Book.h"
#include <ctime>
#include <iostream>
using namespace std;

Book::Book(string isbn, string title, string author) {
    this->isbn = isbn;
    this->title = title;
    this->author = author;
    this->status = "Available";
    this->dueDate = 0;
    this->borrowedBy = "";
    this->reservedBy = "";
    this->reservationDate = 0;
}

string Book::getISBN() const { return isbn; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getStatus() const { return status; }
string Book::getBorrowedBy() const { return borrowedBy; }
string Book::getReservedBy() const { return reservedBy; }

void Book::setTitle(string newTitle) { title = newTitle; }
void Book::setAuthor(string newAuthor) { author = std::move(newAuthor); }

// Borrow method
bool Book::borrow(string memberEmail) {
    if (status == "Available") {
        status = "Borrowed";
        borrowedBy = memberEmail;

        time_t now = time(0);
        dueDate = now + (14 * 24 * 60 * 60);

        cout << "Book '" << title << "' borrowed successfully!" << endl;
        return true;
    } else if (status == "Reserved" && reservedBy == memberEmail) {
        status = "Borrowed";
        borrowedBy = memberEmail;
        reservedBy = "";

        time_t now = time(0);
        dueDate = now + (14 * 24 * 60 * 60);

        cout << "Reserved book '" << title << "' borrowed successfully!" << endl;
        return true;
    } else if (status == "Reserved") {
        cout << "Book '" << title << "' is reserved for another member." << endl;
        return false;
    } else if (status == "Borrowed") {
        cout << "Book '" << title << "' is already borrowed." << endl;
        return false;
    } else {
        cout << "Book '" << title << "' is not available for borrowing." << endl;
        return false;
    }
}

// Return method
bool Book::returnBook() {
    if (status == "Borrowed") {
        borrowedBy = "";
        dueDate = 0;

        if (reservedBy != "") {
            status = "Reserved";
            cout << "Book '" << title << "' is now reserved for " << reservedBy << endl;
        } else {
            status = "Available";
        }

        cout << "Book '" << title << "' returned successfully!" << endl;
        return true;
    } else {
        cout << "Book '" << title << "' was not borrowed." << endl;
        return false;
    }
}

// Reserve method
bool Book::reserve(string memberEmail) {
    if (status == "Available") {
        status = "Reserved";
        reservedBy = memberEmail;
        reservationDate = time(0);
        cout << "Book '" << title << "' reserved successfully! It will expire in 3 days." << endl;
        return true;
    }
    else if (status == "Borrowed" && reservedBy == "") {
        reservedBy = memberEmail;
        reservationDate = time(0);
        cout << "Book '" << title << "' reserved. You'll be notified when available." << endl;
        return true;
    }
    else if (status == "Reserved") {
        cout << "Book '" << title << "' is already reserved." << endl;
        return false;
    }
    else {
        cout << "Book '" << title << "' cannot be reserved." << endl;
        return false;
    }
}

void Book::displayInfo() const {
    cout << "ISBN: " << isbn << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Status: " << status << endl;
    if (status == "Borrowed") {
        cout << "Borrowed by: " << borrowedBy << endl;
    }
    if (status == "Reserved" && reservedBy != "") {
        cout << "Reserved for: " << reservedBy << endl;
    }
    cout << "------------------------" << endl;
}

void Book::displayBrief() const {
    cout << title << " by " << author << " [" << status << "]";
    if (status == "Borrowed") {
        cout << " - Borrowed by: " << borrowedBy;
    }
    cout << endl;
}

bool Book::isAvailable() const {
    return status == "Available";
}

bool Book::isBorrowedBy(string memberEmail) const {
    return status == "Borrowed" && borrowedBy == memberEmail;
}

string Book::getDueDateString() const {
    if (dueDate == 0) {
        return "No due date";
    }

    tm* timeinfo = localtime(&dueDate);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", timeinfo);
    return string(buffer);
}

bool Book::isOverdue() const {
    return getDaysOverdue() > 0;
}

time_t Book::getReservationDate() const {
    return reservationDate;
}

int Book::getDaysOverdue() const {
    if (status != "Borrowed" || dueDate == 0) {
        return 0;
    }

    time_t now = time(0);
    if (now <= dueDate) {
        return 0;
    }

    double secondsOverdue = difftime(now, dueDate);
    return static_cast<int>(secondsOverdue / (24 * 60 * 60));
}

time_t Book::getDueDate() const {
    return dueDate;
}

void Book::setStatus(string newStatus) {
    status = newStatus;
}

void Book::setBorrowedBy(string email) {
    borrowedBy = email;
}

void Book::setReservedBy(string email) {
    reservedBy = email;
}

void Book::setDueDate(time_t date) {
    dueDate = date;
}

void Book::setReservationDate(time_t date) {
    reservationDate = date;
}

bool Book::isReservationExpired() const {
    if (status != "Reserved" || reservationDate == 0) {
        return false;
    }

    time_t now = time(0);
    double secondsSinceReserved = difftime(now, reservationDate);
    int daysSinceReserved = secondsSinceReserved / (24 * 60 * 60);

    return daysSinceReserved >= 3;
}

