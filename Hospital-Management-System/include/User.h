#pragma once
#include <string>

class User {
protected:
    std::string userId;
    std::string username;
    std::string passwordHash;
    std::string role;

public:
    User(const std::string& userId, const std::string& username, const std::string& password, const std::string& role);
    User(const std::string& userId, const std::string& username, const std::string& passwordHash, const std::string& role, bool isHashed);

    bool authenticate(const std::string& password) const;
    static std::string hashPassword(const std::string& password);

    std::string getUserId() const;
    std::string getUsername() const;
    std::string getPasswordHash() const;
    std::string getRole() const;

    std::string serialize() const;
    static User deserialize(const std::string& line);
};
