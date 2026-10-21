#include "../include/User.h"
#include "../include/Exceptions.h"
#include <sstream>
#include <iomanip>
#include <vector>

User::User(const std::string& userId, const std::string& username, const std::string& password, const std::string& role)
    : userId(userId), username(username), passwordHash(hashPassword(password)), role(role) {}

User::User(const std::string& userId, const std::string& username, const std::string& passwordHash, const std::string& role, bool isHashed)
    : userId(userId), username(username), passwordHash(passwordHash), role(role) {}

bool User::authenticate(const std::string& password) const {
    return hashPassword(password) == passwordHash;
}

std::string User::hashPassword(const std::string& password) {
    long long sum = 0;
    for (char c : password) {
        sum += c;
    }
    std::stringstream stream;
    stream << std::hex << sum;
    return stream.str();
}

std::string User::getUserId() const { return userId; }
std::string User::getUsername() const { return username; }
std::string User::getPasswordHash() const { return passwordHash; }
std::string User::getRole() const { return role; }

std::string User::serialize() const {
    return userId + "|" + username + "|" + passwordHash + "|" + role;
}

User User::deserialize(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }
    if (tokens.size() != 4) {
        throw FileIOException("Invalid serialization format for User");
    }
    return User(tokens[0], tokens[1], tokens[2], tokens[3], true);
}
