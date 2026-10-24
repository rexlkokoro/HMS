#include "../include/User.h"
#include <sstream>

User::User() : username(""), password(""), role("Guest") {}

User::User(const std::string& username, const std::string& password, const std::string& role)
    : username(username), password(password), role(role) {}

bool User::authenticate(const std::string& enteredPassword) const {
    return password == enteredPassword;
}

bool User::hasPermission(const std::string& action) const {
    if (role == "Admin") {
        return true; // Admin has full access
    }

    if (role == "Doctor") {
        return (action == "view_patient" || action == "add_prescription" ||
                action == "view_prescription" || action == "view_appointment" ||
                action == "view_doctor");
    }

    if (role == "Receptionist") {
        return (action == "add_patient" || action == "view_patient" ||
                action == "search_patient" || action == "view_doctor" ||
                action == "search_doctor" || action == "book_appointment" ||
                action == "view_appointment" || action == "cancel_appointment" ||
                action == "generate_bill" || action == "view_bill" ||
                action == "pay_bill");
    }

    return false;
}

std::string User::toFileString() const {
    return username + "|" + password + "|" + role;
}

User User::fromFileString(const std::string& line) {
    std::stringstream ss(line);
    std::string u, p, r;
    std::getline(ss, u, '|');
    std::getline(ss, p, '|');
    std::getline(ss, r, '|');
    return User(u, p, r.empty() ? "Receptionist" : r);
}

