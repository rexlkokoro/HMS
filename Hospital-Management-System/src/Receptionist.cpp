#include "../include/Receptionist.h"
#include "../include/User.h"
#include "../include/Exceptions.h"
#include <sstream>
#include <vector>

Receptionist::Receptionist(const std::string& receptionistId, const std::string& name, int age, const std::string& gender,
                           const std::string& contact, const std::string& address, const std::string& shift,
                           const std::string& username, const std::string& password)
    : Person(name, age, gender, contact, address), receptionistId(receptionistId), shift(shift),
      username(username), passwordHash(User::hashPassword(password)) {
    if (receptionistId.empty()) throw InvalidInputException("Receptionist ID cannot be empty.");
    if (shift != "MORNING" && shift != "AFTERNOON" && shift != "NIGHT") {
        throw InvalidInputException("Shift must be MORNING, AFTERNOON, or NIGHT.");
    }
}

Receptionist::Receptionist(const std::string& receptionistId, const std::string& name, int age, const std::string& gender,
                           const std::string& contact, const std::string& address, const std::string& shift,
                           const std::string& username, const std::string& passwordHash, bool isHashed)
    : Person(name, age, gender, contact, address), receptionistId(receptionistId), shift(shift),
      username(username), passwordHash(passwordHash) {
    if (receptionistId.empty()) throw InvalidInputException("Receptionist ID cannot be empty.");
    if (shift != "MORNING" && shift != "AFTERNOON" && shift != "NIGHT") {
        throw InvalidInputException("Shift must be MORNING, AFTERNOON, or NIGHT.");
    }
}

Receptionist::Receptionist() : Person() {}

std::string Receptionist::getReceptionistId() const { return receptionistId; }
std::string Receptionist::getShift() const { return shift; }
std::string Receptionist::getUsername() const { return username; }
std::string Receptionist::getPasswordHash() const { return passwordHash; }

void Receptionist::display(std::ostream& os) const {
    os << "--- Receptionist Details ---\n"
       << "ID: " << receptionistId << "\n"
       << "Name: " << name << "\n"
       << "Shift: " << shift << "\n"
       << "Username: " << username << "\n";
}

std::string Receptionist::getRole() const { return "Receptionist"; }

std::string Receptionist::serialize() const {
    return receptionistId + "|" + name + "|" + std::to_string(age) + "|" + gender + "|" + contact + "|" +
           address + "|" + shift + "|" + username + "|" + passwordHash;
}

Receptionist Receptionist::deserialize(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }
    while (tokens.size() < 9) {
        tokens.push_back("");
    }
    return Receptionist(tokens[0], tokens[1], std::stoi(tokens[2]), tokens[3], tokens[4], tokens[5],
                        tokens[6], tokens[7], tokens[8], true);
}
