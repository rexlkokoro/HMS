#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"
#include <string>

class Doctor : public Person {
private:
    std::string specialization;

public:
    Doctor();
    Doctor(const std::string& id, const std::string& name, int age,
           const std::string& contact, const std::string& specialization);
    ~Doctor() override = default;

    std::string getRole() const override { return "Doctor"; }
    void display() const override;

    std::string getSpecialization() const { return specialization; }
    void setSpecialization(const std::string& spec) { specialization = spec; }

    std::string toFileString() const;
    static Doctor fromFileString(const std::string& line);
};

#endif // DOCTOR_H

