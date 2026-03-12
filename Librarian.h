#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "User.h"

class Librarian : public User {
private:
    string staffId;
    string department;

public:
    Librarian(string userId, string name, string email, string password, string staffId, string department);

    string getStaffId() const;

    string getDepartment() const;

    void displayInfo() const override;

    void displayMenu() override;
};

#endif
