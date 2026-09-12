#pragma once
#include "Person.h"
#include <string>

class Receptionist : public Person {
private:
    std::string receptionistId;
    std::string shift; // "MORNING", "AFTERNOON", "NIGHT"
    std::string username;
    std::string passwordHash;

public:
    Receptionist(const std::string& receptionistId, const std::string& name, int age, const std::string& gender,
                 const std::string& contact, const std::string& address, const std::string& shift,
                 const std::string& username, const std::string& password);
    Receptionist(const std::string& receptionistId, const std::string& name, int age, const std::string& gender,
                 const std::string& contact, const std::string& address, const std::string& shift,
                 const std::string& username, const std::string& passwordHash, bool isHashed);
    Receptionist();

    std::string getReceptionistId() const;
    std::string getShift() const;
    std::string getUsername() const;
    std::string getPasswordHash() const;

    void display(std::ostream& os) const override;
    std::string getRole() const override;
    std::string serialize() const override;
    static Receptionist deserialize(const std::string& line);
};
