#pragma once
#include "Person.h"
#include <string>

class Admin : public Person {
private:
    std::string adminId;
    std::string department;
    std::string username;
    std::string passwordHash;

public:
    Admin(const std::string& adminId, const std::string& name, int age, const std::string& gender,
          const std::string& contact, const std::string& address, const std::string& department,
          const std::string& username, const std::string& password);
    Admin(const std::string& adminId, const std::string& name, int age, const std::string& gender,
          const std::string& contact, const std::string& address, const std::string& department,
          const std::string& username, const std::string& passwordHash, bool isHashed);
    Admin();

    std::string getAdminId() const;
    std::string getDepartment() const;
    std::string getUsername() const;
    std::string getPasswordHash() const;

    void display(std::ostream& os) const override;
    std::string getRole() const override;
    std::string serialize() const override;
    static Admin deserialize(const std::string& line);
};
