#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "Member.h"
#include "Librarian.h"
#include "Admin.h"

class Library {
private:
    Book* books[100];
    int bookCount;

    User* users[50];
    int userCount;

    int maxBooksPerMember;
    int loanPeriodDays;
    int reservationExpiryDays;
    double overdueFinePerDay;

public:
    Library();
    ~Library();

    void addBook(string title, string author);
    bool removeBook(string title);
    Book* findBookByISBN(string isbn);
    Book* findBookByTitle(string title);
    Book* findBookByTitlePartial(string title);
    void searchBooksByTitle(string title, Book* results[], int& resultCount);
    void searchBooksByAuthor(string author, Book* results[], int& resultCount);
    void displayAllBooks();
    void displayAvailableBooks();
    void displayOverdueBooks();

    bool registerMember(string name, string email, string password, string studentId);
    bool registerLibrarian(string name, string email, string password, string staffId, string department);
    User* login(string email, string password);

    void displayAllMembers();
    void displayAllLibrarians();
    void displayBorrowingReports();
    bool updateBookInformation();
    void displayBorrowedBooks();
    void displayReservedBooks();

    void checkExpiredReservations();

    int getBookCount() const;
    Book* getBook(int index) const;

    bool saveData();
    bool loadData();
    void saveBooks();
    void loadBooks();
    void saveUsers();
    void loadUsers();

    string toLowerCase(string str);
    string generateISBN();

    void displayRules();
    void updateRules();
    int getMaxBooksPerMember() const { return maxBooksPerMember; }
    int getLoanPeriodDays() const { return loanPeriodDays; }
    int getReservationExpiryDays() const { return reservationExpiryDays; }
    double getOverdueFinePerDay() const { return overdueFinePerDay; }
    void saveRules();
    void loadRules();
    int getNextLibrarianId();
    void addLibrarian(Librarian* librarian);
    int getUserCount() const;
    User* getUser(int index) const;
    void removeMember(int index);
};

#endif