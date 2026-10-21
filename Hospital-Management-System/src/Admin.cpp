#include "../include/Admin.h"
#include "../include/User.h"
#include "../include/Exceptions.h"
#include <sstream>
#include <vector>

Admin::Admin(const std::string& adminId, const std::string& name, int age, const std::string& gender,
             const std::string& contact, const std::string& address, const std::string& department,
             const std::string& username, const std::string& password)
    : Person(name, age, gender, contact, address), adminId(adminId), department(department),
      username(username), passwordHash(User::hashPassword(password)) {
    if (adminId.empty()) throw InvalidInputException("Admin ID cannot be empty.");
}

Admin::Admin(const std::string& adminId, const std::string& name, int age, const std::string& gender,
             const std::string& contact, const std::string& address, const std::string& department,
             const std::string& username, const std::string& passwordHash, bool isHashed)
    : Person(name, age, gender, contact, address), adminId(adminId), department(department),
      username(username), passwordHash(passwordHash) {
    if (adminId.empty()) throw InvalidInputException("Admin ID cannot be empty.");
}

Admin::Admin() : Person() {}

std::string Admin::getAdminId() const { return adminId; }
std::string Admin::getDepartment() const { return department; }
std::string Admin::getUsername() const { return username; }
std::string Admin::getPasswordHash() const { return passwordHash; }

void Admin::display(std::ostream& os) const {
    os << "--- Admin Details ---\n"
       << "ID: " << adminId << "\n"
       << "Name: " << name << "\n"
       << "Department: " << department << "\n"
       << "Username: " << username << "\n";
}

std::string Admin::getRole() const { return "Admin"; }

std::string Admin::serialize() const {
    return adminId + "|" + name + "|" + std::to_string(age) + "|" + gender + "|" + contact + "|" +
           address + "|" + department + "|" + username + "|" + passwordHash;
}

Admin Admin::deserialize(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }
    while (tokens.size() < 9) {
        tokens.push_back("");
    }
    return Admin(tokens[0], tokens[1], std::stoi(tokens[2]), tokens[3], tokens[4], tokens[5],
                 tokens[6], tokens[7], tokens[8], true);
}
