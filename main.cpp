#include <iostream>
#include <string>
#include <limits>
#include "Library.h"

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Library library;

    User *currentUser = nullptr;
    int choice;
    bool running = true;

    cout << "\n========================================\n";
    cout << "   SMART LIBRARY MANAGEMENT SYSTEM     \n";
    cout << "========================================\n";

    while (running) {
        if (currentUser == nullptr) {
            cout << "\n=== WELCOME ===\n";
            cout << "1. Member Login\n";
            cout << "2. Member Registration\n";
            cout << "3. Librarian Login\n";
            cout << "4. Admin Login\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";

            cin >> choice;

            switch (choice) {
                case 1: {
                    string email, password;
                    cout << "Enter your student email (StudentID@bucks.ac.uk): ";
                    cin >> email;
                    cout << "Enter password: ";
                    cin >> password;

                    currentUser = library.login(email, password);

                    if (currentUser != nullptr && currentUser->getRole() != "Member") {
                        cout << "This is a member login. Please use the correct login." << endl;
                        currentUser = nullptr;
                    }
                    break;
                }

                case 2: {
                    string name, email, password, studentId;

                    cout << "\n=== MEMBER REGISTRATION ===\n";
                    cout << "Enter your full name: ";
                    clearInputBuffer();
                    getline(cin, name);

                    cout << "Enter your student email (StudentID@bucks.ac.uk): ";
                    getline(cin, email);

                    cout << "Enter your student ID: ";
                    getline(cin, studentId);

                    cout << "Create a password: ";
                    getline(cin, password);

                    library.registerMember(name, email, password, studentId);
                    break;
                }

                case 3: {
                    string email, password;
                    cout << "Enter librarian email (@bucks.ac.uk): ";
                    cin >> email;
                    cout << "Enter password: ";
                    cin >> password;

                    currentUser = library.login(email, password);

                    if (currentUser != nullptr && currentUser->getRole() != "Librarian") {
                        cout << "This is a librarian login. Please use the correct login." << endl;
                        currentUser = nullptr;
                    }
                    break;
                }

                case 4: {
                    string email, password;
                    cout << "Enter admin email (@bucks.ac.uk): ";
                    cin >> email;
                    cout << "Enter password: ";
                    cin >> password;

                    currentUser = library.login(email, password);

                    if (currentUser != nullptr && currentUser->getRole() != "Admin") {
                        cout << "This is an admin login. Please use the correct login." << endl;
                        currentUser = nullptr;
                    }
                    break;
                }

                case 5:
                    library.saveData();
                    cout << "Thank you for using the Smart Library Management System." << endl;
                    running = false;
                    break;

                default:
                    cout << "Invalid choice. Please try again." << endl;
                    clearInputBuffer();
            }
        } else if (currentUser->getRole() == "Member") {
            Member *member = dynamic_cast<Member *>(currentUser);
            member->displayMenu();
            cin >> choice;

            switch (choice) {
                case 1:
                    member->displayInfo();
                    break;

                case 2:
                    library.displayAllBooks();
                    break;

                case 3: {
                    string title;
                    cout << "Enter title to search: ";
                    clearInputBuffer();
                    getline(cin, title);

                    Book *results[100];
                    int resultCount;
                    library.searchBooksByTitle(title, results, resultCount);

                    cout << "\n=== Search Results (" << resultCount << " found) ===\n";
                    if (resultCount == 0) {
                        cout << "No books found with that title." << endl;
                    } else {
                        for (int i = 0; i < resultCount; i++) {
                            results[i]->displayInfo();
                        }
                    }
                    break;
                }

                case 4: {
                    string author;
                    cout << "Enter author to search: ";
                    clearInputBuffer();
                    getline(cin, author);

                    Book *results[100];
                    int resultCount;
                    library.searchBooksByAuthor(author, results, resultCount);

                    cout << "\n=== Search Results (" << resultCount << " found) ===\n";
                    if (resultCount == 0) {
                        cout << "No books found by that author." << endl;
                    } else {
                        for (int i = 0; i < resultCount; i++) {
                            results[i]->displayInfo();
                        }
                    }
                    break;
                }

                case 5: {
                    cout << "\n=== BORROW A BOOK ===\n";

                    for (int i = 0; i < library.getBookCount(); i++) {
                        Book *book = library.getBook(i);
                        cout << i + 1 << ". " << book->getTitle() << " by " << book->getAuthor();
                        cout << " [" << book->getStatus() << "]";

                        if (book->getStatus() == "Reserved") {
                            if (book->getReservedBy() == member->getEmail()) {
                                cout << " (You reserved this)";
                            } else {
                                cout << " (Reserved)";
                            }
                        }
                        cout << endl;
                    }

                    cout << "\nEnter the TITLE of the book to borrow (or 0 to cancel): ";
                    clearInputBuffer();
                    string title;
                    getline(cin, title);

                    if (title == "0") {
                        cout << "Borrowing cancelled." << endl;
                        break;
                    }

                    Book *book = library.findBookByTitle(title);

                    if (book == nullptr) {
                        book = library.findBookByTitlePartial(title);
                        if (book != nullptr) {
                            cout << "Did you mean \"" << book->getTitle() << "\"? (y/n): ";
                            char confirm;
                            cin >> confirm;
                            if (confirm != 'y' && confirm != 'Y') {
                                cout << "Borrowing cancelled." << endl;
                                break;
                            }
                        }
                    }

                    if (book != nullptr) {
                        if (member->getBorrowedCount() >= 5) {
                            cout << "You have already borrowed the maximum of 5 books. Please return a book first." <<
                                    endl;
                        } else if (book->isAvailable()) {
                            if (book->borrow(member->getEmail())) {
                                member->borrowBook(book->getISBN());
                                library.saveBooks();
                                library.saveUsers();
                            }
                        } else if (book->getStatus() == "Reserved" && book->getReservedBy() == member->getEmail()) {
                            if (book->borrow(member->getEmail())) {
                                member->borrowBook(book->getISBN());
                                library.saveBooks();
                                library.saveUsers();
                            }
                        } else if (book->getStatus() == "Reserved") {
                            cout << "This book is reserved for another member." << endl;
                        } else if (book->getStatus() == "Borrowed") {
                            cout << "This book is currently borrowed. You can reserve it instead." << endl;
                        }
                    } else {
                        cout << "No book found with title \"" << title << "\"." << endl;
                    }
                    break;
                }

                case 6: {
                    if (member->getBorrowedCount() == 0) {
                        cout << "You have no books to return." << endl;
                        break;
                    }

                    cout << "\n=== RETURN A BOOK ===\n";
                    cout << "Your borrowed books:" << endl;

                    string borrowedISBNs[5];
                    member->getBorrowedBooks(borrowedISBNs);

                    int displayNumber = 1;
                    for (int i = 0; i < 5; i++) {
                        if (borrowedISBNs[i] != "") {
                            Book *book = library.findBookByISBN(borrowedISBNs[i]);
                            if (book != nullptr) {
                                cout << displayNumber << ". " << book->getTitle() << " by " << book->getAuthor() <<
                                        endl;
                                displayNumber++;
                            }
                        }
                    }

                    cout << "\nEnter the TITLE of the book to return (or 0 to cancel): ";
                    clearInputBuffer();
                    string title;
                    getline(cin, title);

                    if (title == "0") {
                        cout << "Return cancelled." << endl;
                        break;
                    }

                    Book *bookToReturn = nullptr;
                    string lowerTitle = library.toLowerCase(title);

                    for (int i = 0; i < 5; i++) {
                        if (borrowedISBNs[i] != "") {
                            Book *book = library.findBookByISBN(borrowedISBNs[i]);
                            if (book != nullptr) {
                                string bookTitle = library.toLowerCase(book->getTitle());
                                if (bookTitle == lowerTitle || bookTitle.find(lowerTitle) != string::npos) {
                                    bookToReturn = book;
                                    break;
                                }
                            }
                        }
                    }

                    if (bookToReturn != nullptr) {
                        if (bookToReturn->returnBook()) {
                            member->returnBook(bookToReturn->getISBN());
                            library.saveBooks();
                            library.saveUsers();
                        }
                    } else {
                        cout << "No book with title \"" << title << "\" found in your borrowed list." << endl;
                    }
                    break;
                }

                case 7: {
                    cout << "\n=== RESERVE A BOOK ===\n";
                    library.displayAllBooks();

                    cout << "Enter the TITLE of the book to reserve (or 0 to cancel): ";
                    clearInputBuffer();
                    string title;
                    getline(cin, title);

                    if (title == "0") {
                        cout << "Reservation cancelled." << endl;
                        break;
                    }

                    Book *book = library.findBookByTitle(title);

                    if (book == nullptr) {
                        book = library.findBookByTitlePartial(title);
                        if (book != nullptr) {
                            cout << "Did you mean \"" << book->getTitle() << "\"? (y/n): ";
                            char confirm;
                            cin >> confirm;
                            if (confirm != 'y' && confirm != 'Y') {
                                cout << "Reservation cancelled." << endl;
                                break;
                            }
                        }
                    }

                    if (book != nullptr) {
                        book->reserve(member->getEmail());
                        library.saveBooks();
                    } else {
                        cout << "No book found with title \"" << title << "\"." << endl;
                    }
                    break;
                }

                case 8: {
                    cout << "\n=== YOUR BORROWED BOOKS ===\n";
                    string borrowedISBNs[5];
                    member->getBorrowedBooks(borrowedISBNs);

                    bool hasBooks = false;
                    for (int i = 0; i < 5; i++) {
                        if (borrowedISBNs[i] != "") {
                            Book *book = library.findBookByISBN(borrowedISBNs[i]);
                            if (book != nullptr) {
                                book->displayInfo();
                                hasBooks = true;
                            }
                        }
                    }

                    if (!hasBooks) {
                        cout << "You have no books borrowed." << endl;
                    }
                    break;
                }

                case 9:
                    currentUser->logout();
                    currentUser = nullptr;
                    break;

                default:
                    cout << "Invalid choice. Please try again." << endl;
                    clearInputBuffer();
            }
        } else if (currentUser->getRole() == "Librarian") {
            currentUser->displayMenu();
            cin >> choice;

            switch (choice) {
                case 1:
                    currentUser->displayInfo();
                    break;

                case 2:
                    library.displayAllBooks();
                    break;

                case 3: {
                    cout << "\n=== ADD NEW BOOK ===\n";
                    string title, author;

                    cout << "Enter Title: ";
                    clearInputBuffer();
                    getline(cin, title);
                    cout << "Enter Author: ";
                    getline(cin, author);

                    library.addBook(title, author);
                    library.saveBooks();
                    break;
                }

                case 4: {
                    cout << "\n=== REMOVE BOOK ===\n";
                    library.displayAllBooks();

                    cout << "\nEnter the TITLE of the book to remove (or 0 to cancel): ";
                    clearInputBuffer();
                    string title;
                    getline(cin, title);

                    if (title == "0") {
                        cout << "Removal cancelled." << endl;
                        break;
                    }

                    if (library.removeBook(title)) {
                        library.saveBooks();
                    }
                    break;
                }

                case 5: {
                    if (library.updateBookInformation()) {
                        library.saveBooks();
                    }
                    break;
                }

                case 6: {
                    library.displayOverdueBooks();
                    break;
                }

                case 7: {
                    library.displayBorrowedBooks();
                    break;
                }

                case 8: {
                    library.displayReservedBooks();
                    break;
                }

                case 9:
                    currentUser->logout();
                    currentUser = nullptr;
                    break;

                default:
                    cout << "Invalid choice. Please try again." << endl;
                    clearInputBuffer();
            }
        } else if (currentUser->getRole() == "Admin") {
            currentUser->displayMenu();
            cin >> choice;

            switch (choice) {
                case 1:
                    currentUser->displayInfo();
                    break;

                case 2: {
                    cout << "\n=== MANAGE MEMBER ACCOUNTS ===\n";
                    cout << "1. View All Members\n";
                    cout << "2. Add Member\n";
                    cout << "3. Remove Member\n";
                    cout << "Enter choice: ";
                    int subChoice;
                    cin >> subChoice;

                    if (subChoice == 1) {
                        library.displayAllMembers();
                    } else if (subChoice == 2) {
                        string name, email, password, studentId;
                        cout << "Enter name: ";
                        clearInputBuffer();
                        getline(cin, name);
                        cout << "Enter email (@bucks.ac.uk): ";
                        getline(cin, email);
                        cout << "Enter student ID: ";
                        getline(cin, studentId);
                        cout << "Enter password: ";
                        getline(cin, password);
                        library.registerMember(name, email, password, studentId);
                    } else if (subChoice == 3) {
                        cout << "\n=== REMOVE MEMBER ===\n";
                        library.displayAllMembers();

                        cout << "Enter the email of the member to remove (or 0 to cancel): ";
                        string email;
                        cin >> email;

                        if (email == "0") {
                            cout << "Removal cancelled." << endl;
                            break;
                        }

                        bool found = false;
                        for (int i = 0; i < library.getUserCount(); i++) {
                            User *user = library.getUser(i);
                            if (user->getRole() == "Member" && user->getEmail() == email) {
                                found = true;
                                Member *member = dynamic_cast<Member *>(user);

                                if (member->getBorrowedCount() > 0) {
                                    cout << "Cannot remove member. They have " << member->getBorrowedCount()
                                            << " book(s) currently borrowed." << endl;
                                    break;
                                }

                                cout << "Found member: " << user->getName() << " (" << user->getEmail() << ")" << endl;
                                cout << "Remove this member? (y/n): ";
                                char confirm;
                                cin >> confirm;

                                if (confirm == 'y' || confirm == 'Y') {
                                    library.removeMember(i);
                                    cout << "Member removed successfully!" << endl;
                                } else {
                                    cout << "Removal cancelled." << endl;
                                }
                                break;
                            }
                        }

                        if (!found) {
                            cout << "No member found with email: " << email << endl;
                        }
                    }
                    break;
                }

                case 3: {
                    cout << "\n=== MANAGE LIBRARIAN ACCOUNTS ===\n";
                    cout << "1. View All Librarians\n";
                    cout << "2. Add Librarian\n";
                    cout << "Enter choice: ";
                    int subChoice;
                    cin >> subChoice;

                    if (subChoice == 1) {
                        library.displayAllLibrarians();
                    } else if (subChoice == 2) {
                        string name, email, password;
                        cout << "Enter name: ";
                        clearInputBuffer();
                        getline(cin, name);
                        cout << "Enter email (@bucks.ac.uk): ";
                        getline(cin, email);
                        cout << "Enter password: ";
                        getline(cin, password);

                        int nextId = library.getNextLibrarianId();

                        string staffId;
                        if (nextId < 10) {
                            staffId = "LIB00" + to_string(nextId);
                        } else if (nextId < 100) {
                            staffId = "LIB0" + to_string(nextId);
                        } else {
                            staffId = "LIB" + to_string(nextId);
                        }

                        string userId = "L" + to_string(100 + nextId);
                        string department = "Library";

                        Librarian *newLibrarian = new Librarian(userId, name, email, password, staffId, department);
                        library.addLibrarian(newLibrarian);
                    }
                    break;
                }
                case 4:
                    library.updateRules();
                    break;

                case 5:
                    currentUser->logout();
                    currentUser = nullptr;
                    break;

                default:
                    cout << "Invalid choice. Please try again." << endl;
                    clearInputBuffer();
            }
        }
    }

    return 0;
}
