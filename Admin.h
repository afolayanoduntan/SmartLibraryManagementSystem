#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <string>
using namespace std;

#include "User.h"

class Admin : public User {
private:
    string staffId;
    string department;

public:
    Admin(string userId, string name, string email, string password, string staffId, string department);
    
    string getStaffId() const;
    string getDepartment() const;
    
    void displayInfo() const override;
    void displayMenu() override;
};

#endif