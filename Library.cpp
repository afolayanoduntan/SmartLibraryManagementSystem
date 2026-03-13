#include "Library.h"
#include <cctype>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include <fstream>
using namespace std;

Library::Library() {
    bookCount = 0;
    userCount = 0;

    maxBooksPerMember = 5;
    loanPeriodDays = 14;
    reservationExpiryDays = 3;
    overdueFinePerDay = 0.50;
    loadRules();

    //Default Admin credential
    Admin *defaultAdmin = new Admin("A001", "Library Admin", "admin@bucks.ac.uk", "admin123", "ADM001", "Management");
    users[userCount++] = defaultAdmin;

    //Default Librarian credential
    Librarian *defaultLibrarian = new Librarian("L001", "Head Librarian", "librarian@bucks.ac.uk", "lib123", "LIB001",
                                                "Library");
    users[userCount++] = defaultLibrarian;

    //Default Member credential
    Member *defaultMember = new Member("M101", "Default User", "11112222@bucks.ac.uk", "password", "11112222");
    users[userCount++] = defaultMember;

    loadData();

    if (userCount <= 3) {
        saveUsers();
    }

    checkExpiredReservations();

    if (bookCount == 0) {
        if (bookCount < 100) {
            books[bookCount] = new Book("LIB-00001", "The Hobbit", "J.R.R. Tolkien");
            bookCount++;
        }
        if (bookCount < 100) {
            books[bookCount] = new Book("LIB-00002", "Harry Potter and the Sorcerer's Stone", "J.K. Rowling");
            bookCount++;
        }
        if (bookCount < 100) {
            books[bookCount] = new Book("LIB-00003", "To Kill a Mockingbird", "Harper Lee");
            bookCount++;
        }
        if (bookCount < 100) {
            books[bookCount] = new Book("LIB-00004", "Pride and Prejudice", "Jane Austen");
            bookCount++;
        }
        if (bookCount < 100) {
            books[bookCount] = new Book("LIB-00005", "1984", "George Orwell");
            bookCount++;
        }
        if (bookCount < 100) {
            books[bookCount] = new Book("LIB-00006", "The Great Gatsby", "F. Scott Fitzgerald");
            bookCount++;
        }
        if (bookCount < 100) {
            books[bookCount] = new Book("LIB-00007", "Moby Dick", "Herman Melville");
            bookCount++;
        }
        if (bookCount < 100) {
            books[bookCount] = new Book("LIB-00008", "War and Peace", "Leo Tolstoy");
            bookCount++;
        }
        if (bookCount < 100) {
            books[bookCount] = new Book("LIB-00009", "The Catcher in the Rye", "J.D. Salinger");
            bookCount++;
        }
        if (bookCount < 100) {
            books[bookCount] = new Book("LIB-00010", "The Lord of the Rings", "J.R.R. Tolkien");
            bookCount++;
        }
        if (bookCount < 100) {
            books[bookCount] = new Book("LIB-00011", "Jane Eyre", "Charlotte Bronte");
            bookCount++;
        }
        if (bookCount < 100) {
            books[bookCount] = new Book("LIB-00012", "Wuthering Heights", "Emily Bronte");
            bookCount++;
        }
        if (bookCount < 100) {
            books[bookCount] = new Book("LIB-00013", "The Odyssey", "Homer");
            bookCount++;
        }
        if (bookCount < 100) {
            books[bookCount] = new Book("LIB-00014", "Crime and Punishment", "Fyodor Dostoevsky");
            bookCount++;
        }
        if (bookCount < 100) {
            books[bookCount] = new Book("LIB-00015", "Brave New World", "Aldous Huxley");
            bookCount++;
        }
    }
}

Library::~Library() {
    for (int i = 0; i < bookCount; i++) {
        delete books[i];
    }
    for (int i = 0; i < userCount; i++) {
        delete users[i];
    }
}

string Library::generateISBN() {
    stringstream ss;
    ss << "LIB-" << setw(5) << setfill('0') << (bookCount + 1);
    return ss.str();
}

void Library::addBook(string title, string author) {
    if (bookCount < 100) {
        string isbn = generateISBN();
        books[bookCount] = new Book(isbn, title, author);
        cout << "Book added successfully! ISBN: " << isbn << endl;
        cout << "Title: " << title << " by " << author << endl;
        bookCount++;
    } else {
        cout << "Library is full! Cannot add more books." << endl;
    }
}

bool Library::removeBook(string title) {
    string lowerTitle = toLowerCase(title);

    for (int i = 0; i < bookCount; i++) {
        string bookTitle = toLowerCase(books[i]->getTitle());

        if (bookTitle == lowerTitle || bookTitle.find(lowerTitle) != string::npos) {
            if (books[i]->getStatus() == "Borrowed") {
                cout << "Cannot remove \"" << books[i]->getTitle() << "\" - it is currently borrowed." << endl;
                return false;
            }

            cout << "Found book: \"" << books[i]->getTitle() << "\" by " << books[i]->getAuthor() << endl;
            cout << "Remove this book? (y/n): ";
            char confirm;
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y') {
                delete books[i];
                for (int j = i; j < bookCount - 1; j++) {
                    books[j] = books[j + 1];
                }
                bookCount--;
                cout << "Book removed successfully!" << endl;
                return true;
            } else {
                cout << "Removal cancelled." << endl;
                return false;
            }
        }
    }

    cout << "No book found with title \"" << title << "\"." << endl;

    cout << "\nDid you mean one of these?" << endl;
    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        string bookTitle = toLowerCase(books[i]->getTitle());
        if (bookTitle.find(lowerTitle) != string::npos || lowerTitle.find(bookTitle) != string::npos) {
            cout << "- " << books[i]->getTitle() << " by " << books[i]->getAuthor() << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No similar titles found." << endl;
    }

    return false;
}

Book *Library::findBookByISBN(string isbn) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i]->getISBN() == isbn) {
            return books[i];
        }
    }
    return nullptr;
}

Book *Library::findBookByTitle(string title) {
    string lowerTitle = toLowerCase(title);
    for (int i = 0; i < bookCount; i++) {
        string bookTitle = toLowerCase(books[i]->getTitle());
        if (bookTitle == lowerTitle) {
            return books[i];
        }
    }
    return nullptr;
}

Book *Library::findBookByTitlePartial(string title) {
    string lowerTitle = toLowerCase(title);
    for (int i = 0; i < bookCount; i++) {
        string bookTitle = toLowerCase(books[i]->getTitle());
        if (bookTitle.find(lowerTitle) != string::npos) {
            return books[i];
        }
    }
    return nullptr;
}

void Library::searchBooksByTitle(string title, Book *results[], int &resultCount) {
    string lowerTitle = toLowerCase(title);
    resultCount = 0;

    for (int i = 0; i < bookCount; i++) {
        string bookTitle = toLowerCase(books[i]->getTitle());
        if (bookTitle.find(lowerTitle) != string::npos) {
            results[resultCount++] = books[i];
        }
    }
}

void Library::searchBooksByAuthor(string author, Book *results[], int &resultCount) {
    string lowerAuthor = toLowerCase(author);
    resultCount = 0;

    for (int i = 0; i < bookCount; i++) {
        string bookAuthor = toLowerCase(books[i]->getAuthor());
        if (bookAuthor.find(lowerAuthor) != string::npos) {
            results[resultCount++] = books[i];
        }
    }
}

void Library::displayAllBooks() {
    cout << "\n=== LIBRARY CATALOG (" << bookCount << " books) ===\n";
    if (bookCount == 0) {
        cout << "No books in library." << endl;
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        cout << i + 1 << ". ";
        cout << books[i]->getTitle() << " by " << books[i]->getAuthor();
        cout << " [" << books[i]->getStatus() << "]";

        if (books[i]->getStatus() == "Borrowed") {
            cout << " - Borrowed by: " << books[i]->getBorrowedBy();
        }
        else if (books[i]->getStatus() == "Reserved") {
            cout << " - Reserved by: " << books[i]->getReservedBy();
        }
        cout << endl;
    }
}

void Library::displayAvailableBooks() {
    cout << "\n=== AVAILABLE BOOKS ===\n";
    int available = 0;

    for (int i = 0; i < bookCount; i++) {
        if (books[i]->isAvailable()) {
            cout << i + 1 << ". ";
            books[i]->displayBrief();
            available++;
        }
    }

    if (available == 0) {
        cout << "No books currently available." << endl;
    } else {
        cout << "Total available: " << available << endl;
    }
}

static void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Library::displayAllMembers() {
    cout << "\n=== MEMBER LIST (" << (userCount - 1) << " members) ===\n";

    if (userCount <= 1) {
        cout << "No members registered yet." << endl;
        return;
    }

    cout << left;
    cout << setw(15) << "Member ID"
            << setw(25) << "Name"
            << setw(30) << "Email"
            << setw(15) << "Student ID"
            << setw(10) << "Books" << endl;
    cout << string(95, '-') << endl;

    for (int i = 0; i < userCount; i++) {
        if (users[i]->getRole() == "Member") {
            Member *member = dynamic_cast<Member *>(users[i]);
            if (member != nullptr) {
                cout << setw(15) << member->getUserId()
                        << setw(25) << member->getName()
                        << setw(30) << member->getEmail()
                        << setw(15) << member->getStudentId()
                        << setw(10) << member->getBorrowedCount() << "/5" << endl;
            }
        }
    }
}

void Library::displayBorrowingReports() {
    cout << "\n=== BORROWING REPORTS ===\n";

    int totalBooks = bookCount;
    int borrowedCount = 0;
    int availableCount = 0;
    int reservedCount = 0;
    int overdueCount = 0;

    cout << "\n--- CURRENT BOOK STATUS ---" << endl;
    cout << left;
    cout << setw(5) << "No."
            << setw(40) << "Title"
            << setw(25) << "Author"
            << setw(15) << "Status"
            << setw(30) << "Details" << endl;
    cout << string(115, '-') << endl;

    for (int i = 0; i < bookCount; i++) {
        Book *book = books[i];
        string status = book->getStatus();
        string details = "";

        if (status == "Borrowed") {
            borrowedCount++;
            details = "Borrowed by: " + book->getBorrowedBy();

            if (book->isOverdue()) {
                int days = book->getDaysOverdue();
                overdueCount++;
                details += " - " + to_string(days) + " day" + (days > 1 ? "s" : "") + " OVERDUE!";
            } else {
                details += " - Due: " + book->getDueDateString();
            }
        } else if (status == "Available") {
            availableCount++;
            details = "Available";
        } else if (status == "Reserved") {
            reservedCount++;
            details = "Reserved for: " + book->getReservedBy();
        }

        string title = book->getTitle();
        string author = book->getAuthor();

        cout << setw(5) << (i + 1)
                << setw(40) << (title.length() > 37 ? title.substr(0, 37) + "..." : title)
                << setw(25) << (author.length() > 22 ? author.substr(0, 22) + "..." : author)
                << setw(15) << status
                << setw(30) << (details.length() > 27 ? details.substr(0, 27) + "..." : details)
                << endl;
    }

    cout << "\n--- SUMMARY STATISTICS ---" << endl;
    cout << "Total Books in Library: " << totalBooks << endl;
    cout << "Available: " << availableCount << endl;
    cout << "Borrowed: " << borrowedCount << endl;
    cout << "Reserved: " << reservedCount << endl;
    cout << "Overdue: " << overdueCount << endl;

    if (overdueCount > 0) {
        cout << "\n--- OVERDUE BOOKS DETAIL ---" << endl;
        for (int i = 0; i < bookCount; i++) {
            Book *book = books[i];
            if (book->getStatus() == "Borrowed" && book->isOverdue()) {
                cout << "- " << book->getTitle() << " by " << book->getAuthor() << endl;
                cout << "  Borrowed by: " << book->getBorrowedBy() << endl;
                cout << "  Due date was: " << book->getDueDateString() << endl;
                cout << "  Days overdue: " << book->getDaysOverdue() << endl;
            }
        }
    }

    cout << "\n--- MEMBERS WITH BORROWED BOOKS ---" << endl;
    bool found = false;
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getRole() == "Member") {
            Member *member = dynamic_cast<Member *>(users[i]);
            if (member != nullptr && member->getBorrowedCount() > 0) {
                cout << member->getName() << " (" << member->getEmail() << "): ";
                cout << member->getBorrowedCount() << " books";

                string borrowedISBNs[5];
                member->getBorrowedBooks(borrowedISBNs);
                bool hasOverdue = false;
                for (int j = 0; j < 5; j++) {
                    if (borrowedISBNs[j] != "") {
                        Book *book = findBookByISBN(borrowedISBNs[j]);
                        if (book != nullptr && book->isOverdue()) {
                            hasOverdue = true;
                            break;
                        }
                    }
                }
                if (hasOverdue) {
                    cout << " (HAS OVERDUE BOOKS)";
                }
                cout << endl;
                found = true;
            }
        }
    }
    if (!found) {
        cout << "No members currently have books borrowed." << endl;
    }
}

bool Library::updateBookInformation() {
    cout << "\n=== UPDATE BOOK INFORMATION ===\n";

    if (bookCount == 0) {
        cout << "No books in library to update." << endl;
        return false;
    }

    displayAllBooks();

    cout << "\nEnter the TITLE of the book to update (or 0 to cancel): ";
    clearInputBuffer();
    string title;
    getline(cin, title);

    if (title == "0") {
        cout << "Update cancelled." << endl;
        return false;
    }

    Book *book = findBookByTitle(title);
    if (book == nullptr) {
        book = findBookByTitlePartial(title);
        if (book != nullptr) {
            cout << "Did you mean \"" << book->getTitle() << "\"?" << endl;
            cout << "Update this book? (y/n): ";
            char confirm;
            cin >> confirm;
            if (confirm != 'y' && confirm != 'Y') {
                cout << "Update cancelled." << endl;
                return false;
            }
        }
    }

    if (book == nullptr) {
        cout << "No book found with title \"" << title << "\"." << endl;
        return false;
    }

    cout << "\nCurrent Book Information:" << endl;
    book->displayInfo();

    cout << "\nEnter new information (leave blank to keep current):" << endl;

    string newTitle, newAuthor;

    cout << "New Title [" << book->getTitle() << "]: ";
    clearInputBuffer();
    getline(cin, newTitle);

    cout << "New Author [" << book->getAuthor() << "]: ";
    getline(cin, newAuthor);

    bool updated = false;
    if (!newTitle.empty()) {
        book->setTitle(newTitle);
        updated = true;
    }
    if (!newAuthor.empty()) {
        book->setAuthor(newAuthor);
        updated = true;
    }

    if (updated) {
        cout << "\nBook information updated successfully!" << endl;
        book->displayInfo();
    } else {
        cout << "No changes made." << endl;
    }

    return true;
}

void Library::displayBorrowedBooks() {
    cout << "\n=== BORROWED BOOKS ===\n";

    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        Book *book = books[i];
        if (book->getStatus() == "Borrowed") {
            if (!found) {
                cout << "The following books are currently borrowed:" << endl;
                found = true;
            }
            cout << "- " << book->getTitle() << " by " << book->getAuthor() << endl;
            cout << "  Borrowed by: " << book->getBorrowedBy() << endl;
            cout << "  Due date: " << book->getDueDateString() << endl;
            if (book->isOverdue()) {
                cout << "  ** OVERDUE - " << book->getDaysOverdue() << " days **" << endl;
            }
            cout << endl;
        }
    }

    if (!found) {
        cout << "No books are currently borrowed." << endl;
    }
}

void Library::displayReservedBooks() {
    cout << "\n=== RESERVED BOOKS ===\n";

    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        Book* book = books[i];
        if (book->getReservedBy() != "") {
            if (!found) {
                found = true;
            }
            cout << "- " << book->getTitle() << " by " << book->getAuthor();
            cout << " [Reserved] - Reserved by: " << book->getReservedBy() << endl;

            if (book->getStatus() == "Borrowed") {
                cout << "  (Currently borrowed by: " << book->getBorrowedBy() << ")" << endl;
            }

            time_t now = time(0);
            double secondsSinceReserved = difftime(now, book->getReservationDate());
            int daysSinceReserved = secondsSinceReserved / (24 * 60 * 60);
            int daysLeft = 3 - daysSinceReserved;

            if (daysLeft > 0) {
                cout << "  Expires in: " << daysLeft << " day(s)" << endl;
            }
        }
    }

    if (!found) {
        cout << "No books are currently reserved." << endl;
    }
}


string trim(string str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start != string::npos) {
        str = str.substr(start);
    }

    size_t end = str.find_last_not_of(" \t\n\r");
    if (end != string::npos) {
        str = str.substr(0, end + 1);
    }

    return str;
}

bool Library::registerMember(string name, string email, string password, string studentId) {
    name = trim(name);

    for (int i = 0; i < userCount; i++) {
        if (users[i]->getEmail() == email) {
            cout << "Email already registered!" << endl;
            return false;
        }
    }

    if (!Member::isValidStudentEmail(email)) {
        cout << "Please use your student email (StudentID@bucks.ac.uk)" << endl;
        return false;
    }

    string userId = "M" + to_string(userCount + 99);

    Member *newMember = new Member(userId, name, email, password, studentId);
    users[userCount] = newMember;
    userCount++;

    cout << "Registration successful! Your Member ID: " << userId << endl;
    return true;
}

User *Library::login(string email, string password) {
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getEmail() == email) {
            if (users[i]->login(password)) {
                return users[i];
            }
            return nullptr;
        }
    }

    cout << "Email not found. Please register first." << endl;
    return nullptr;
}

int Library::getBookCount() const { return bookCount; }

Book *Library::getBook(int index) const {
    if (index >= 0 && index < bookCount) {
        return books[index];
    }
    return nullptr;
}

string Library::toLowerCase(string str) {
    for (char &c: str) {
        c = tolower(c);
    }
    return str;
}

bool Library::saveData() {
    saveBooks();
    saveUsers();
    cout << "Data saved successfully!" << endl;
    return true;
}

bool Library::loadData() {
    loadBooks();
    loadUsers();
    cout << "Data loaded successfully!" << endl;
    return true;
}

void Library::saveBooks() {
    ofstream file("books.txt");
    if (!file.is_open()) return;

    for (int i = 0; i < bookCount; i++) {
        Book *book = books[i];
        file << book->getISBN() << "|"
                << book->getTitle() << "|"
                << book->getAuthor() << "|"
                << book->getStatus() << "|"
                << book->getBorrowedBy() << "|"
                << book->getReservedBy() << "|"
                << book->getDueDate() << endl;
    }
    file.close();
}

void Library::loadBooks() {
    ifstream file("books.txt");
    if (!file.is_open()) return;

    for (int i = 0; i < bookCount; i++) {
        delete books[i];
    }
    bookCount = 0;

    string line;
    while (getline(file, line) && bookCount < 100) {
        stringstream ss(line);
        string isbn, title, author, status, borrowedBy, reservedBy, dueDateStr;

        getline(ss, isbn, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, status, '|');
        getline(ss, borrowedBy, '|');
        getline(ss, reservedBy, '|');
        getline(ss, dueDateStr, '|');

        time_t dueDate = stol(dueDateStr);

        Book *book = new Book(isbn, title, author);

        book->setStatus(status);
        book->setBorrowedBy(borrowedBy);
        book->setReservedBy(reservedBy);
        book->setDueDate(dueDate);

        books[bookCount++] = book;
    }
    file.close();
}

void Library::saveUsers() {
    ofstream file("users.txt");
    if (!file.is_open()) return;

    for (int i = 0; i < userCount; i++) {
        User *user = users[i];
        file << user->getRole() << "|"
                << user->getUserId() << "|"
                << user->getName() << "|"
                << user->getEmail() << "|"
                << user->getPassword() << "|";

        if (user->getRole() == "Member") {
            Member *member = dynamic_cast<Member *>(user);
            file << member->getStudentId() << "|"
                    << member->getBorrowedCount();

            string borrowedISBNs[5];
            member->getBorrowedBooks(borrowedISBNs);
            for (int j = 0; j < 5; j++) {
                file << "|" << borrowedISBNs[j];
            }
        } else if (user->getRole() == "Librarian") {
            Librarian *librarian = dynamic_cast<Librarian *>(user);
            file << librarian->getStaffId() << "|"
                    << librarian->getDepartment();
        } else if (user->getRole() == "Admin") {
            Admin *admin = dynamic_cast<Admin *>(user);
            file << admin->getStaffId() << "|"
                    << admin->getDepartment();
        }
        file << endl;
    }
    file.close();
}

void Library::loadUsers() {
    ifstream file("users.txt");
    if (!file.is_open()) return;

    for (int i = 0; i < userCount; i++) {
        delete users[i];
    }
    userCount = 0;

    string line;
    while (getline(file, line) && userCount < 50) {
        stringstream ss(line);
        string role, userId, name, email, password;

        getline(ss, role, '|');
        getline(ss, userId, '|');
        getline(ss, name, '|');
        getline(ss, email, '|');
        getline(ss, password, '|');

        if (role == "Member") {
            string studentId, borrowedCountStr;
            string borrowedISBNs[5];

            getline(ss, studentId, '|');
            getline(ss, borrowedCountStr, '|');

            int borrowedCount = stoi(borrowedCountStr);

            for (int j = 0; j < 5; j++) {
                getline(ss, borrowedISBNs[j], '|');
            }

            Member *member = new Member(userId, name, email, password, studentId);

            for (int j = 0; j < borrowedCount; j++) {
                if (borrowedISBNs[j] != "") {
                    member->borrowBook(borrowedISBNs[j]);
                }
            }

            users[userCount++] = member;
        } else if (role == "Librarian") {
            string staffId, department;
            getline(ss, staffId, '|');
            getline(ss, department, '|');

            Librarian *librarian = new Librarian(userId, name, email, password, staffId, department);
            users[userCount++] = librarian;
        } else if (role == "Admin") {
            string staffId, department;
            getline(ss, staffId, '|');
            getline(ss, department, '|');

            Admin *admin = new Admin(userId, name, email, password, staffId, department);
            users[userCount++] = admin;
        }
    }
    file.close();
}

void Library::displayOverdueBooks() {
    cout << "\n=== OVERDUE BOOKS REPORT ==f=\n";

    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        Book *book = books[i];
        if (book->getStatus() == "Borrowed" && book->isOverdue()) {
            if (!found) {
                cout << "The following books are overdue:" << endl;
                found = true;
            }
            cout << "- " << book->getTitle() << " by " << book->getAuthor() << endl;
            cout << "  Borrowed by: " << book->getBorrowedBy() << endl;
            cout << "  Days overdue: " << book->getDaysOverdue() << endl;
        }
    }

    if (!found) {
        cout << "No overdue books found." << endl;
    }
}

void Library::displayAllLibrarians() {
    cout << "\n=== LIBRARIAN LIST ===\n";

    bool found = false;
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getRole() == "Librarian") {
            users[i]->displayInfo();
            found = true;
        }
    }

    if (!found) {
        cout << "No librarians registered." << endl;
    }
}

bool Library::registerLibrarian(string name, string email, string password, string staffId, string department) {
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getEmail() == email) {
            cout << "Email already registered!" << endl;
            return false;
        }
    }

    string userId = "L" + to_string(userCount + 100);
    Librarian *newLibrarian = new Librarian(userId, name, email, password, staffId, department);
    users[userCount++] = newLibrarian;

    cout << "Librarian registered successfully! ID: " << userId << endl;
    saveUsers();
    return true;
}

void Library::checkExpiredReservations() {
    bool expiredFound = false;

    for (int i = 0; i < bookCount; i++) {
        Book *book = books[i];
        if (book->getStatus() == "Reserved" && book->isReservationExpired()) {
            cout << "Reservation for '" << book->getTitle() << "' by "
                    << book->getReservedBy() << " has expired." << endl;

            book->setStatus("Available");
            book->setReservedBy("");
            book->setReservationDate(0);

            expiredFound = true;
        }
    }

    if (expiredFound) {
        cout << "Expired reservations have been removed." << endl;
        saveBooks();
    }
}

void Library::displayRules() {
    cout << "\n=== CURRENT LIBRARY RULES ===\n";
    cout << "1. Max Books Per Member: " << maxBooksPerMember << " (Fixed)" << endl;
    cout << "2. Reservation Expiry (days): " << reservationExpiryDays << " (Fixed)" << endl;
    cout << "3. Loan Period (days): " << loanPeriodDays << endl;
    cout << "4. Overdue Fine Per Day: GBP " << overdueFinePerDay << endl;

    cout << "==============================\n";
}

void Library::updateRules() {
    displayRules();

    cout << "\nSelect rule to update (3 or 4, 0 to cancel): ";
    int choice;
    cin >> choice;

    if (choice == 0) return;

    switch(choice) {
        case 3:
            cout << "Enter new loan period (days): ";
            cin >> loanPeriodDays;
            break;
        case 4:
            cout << "Enter new overdue fine per day (£): ";
            cin >> overdueFinePerDay;
            break;
        default:
            cout << "Invalid choice. Only rules 3 and 4 can be modified.\n";
            return;
    }

    cout << "Rule updated successfully!\n";
    saveRules();
    displayRules();
}

void Library::saveRules() {
    ofstream file("rules.txt");
    if (!file.is_open()) return;

    file << loanPeriodDays << endl;
    file << overdueFinePerDay << endl;

    file.close();
}

void Library::loadRules() {
    ifstream file("rules.txt");
    if (!file.is_open()) return;

    file >> loanPeriodDays;
    file >> overdueFinePerDay;

    file.close();
}

int Library::getNextLibrarianId() {
    int maxId = 0;
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getRole() == "Librarian") {
            Librarian* lib = dynamic_cast<Librarian*>(users[i]);
            string id = lib->getStaffId();
            if (id.substr(0, 3) == "LIB") {
                int num = stoi(id.substr(3));
                if (num > maxId) maxId = num;
            }
        }
    }
    return maxId + 1;
}

void Library::addLibrarian(Librarian* librarian) {
    users[userCount++] = librarian;
    saveUsers();
    cout << "Librarian added successfully! User ID: " << librarian->getUserId()
         << ", Staff ID: " << librarian->getStaffId() << endl;
}

int Library::getUserCount() const {
    return userCount;
}

User* Library::getUser(int index) const {
    if (index >= 0 && index < userCount) {
        return users[index];
    }
    return nullptr;
}

void Library::removeMember(int index) {
    if (index < 0 || index >= userCount) return;

    delete users[index];

    for (int i = index; i < userCount - 1; i++) {
        users[i] = users[i + 1];
    }

    userCount--;
    saveUsers();
}