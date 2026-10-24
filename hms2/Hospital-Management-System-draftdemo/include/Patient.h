#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <string>

class Patient : public Person {
private:
    std::string disease;

public:
    Patient();
    Patient(const std::string& id, const std::string& name, int age,
            const std::string& contact, const std::string& disease);
    ~Patient() override = default;

    std::string getRole() const override { return "Patient"; }
    void display() const override;

    std::string getDisease() const { return disease; }
    void setDisease(const std::string& d) { disease = d; }

    std::string toFileString() const;
    static Patient fromFileString(const std::string& line);
};

#endif // PATIENT_H

