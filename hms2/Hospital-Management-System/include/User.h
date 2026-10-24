#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;
    std::string role; // e.g. "Admin", "Doctor", "Receptionist"

public:
    User();
    User(const std::string& username, const std::string& password, const std::string& role);

    // Getters
    std::string getUsername() const { return username; }
    std::string getRole() const { return role; }

    // Authentication & Access control
    bool authenticate(const std::string& enteredPassword) const;
    bool hasPermission(const std::string& action) const;

    std::string toFileString() const;
    static User fromFileString(const std::string& line);
};

#endif // USER_H

