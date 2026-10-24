#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <string>

class Patient : public Person {
private:
    std::string address;
    std::string bloodGroup;
    std::string medicalHistory;

public:
    Patient();
    Patient(const std::string& id, const std::string& name, int age,
            const std::string& contact, const std::string& address,
            const std::string& bloodGroup);
    ~Patient() override = default;

    std::string getRole() const override { return "Patient"; }
    void display() const override;

    // Patient-specific accessors
    std::string getAddress() const { return address; }
    void setAddress(const std::string& address) { this->address = address; }

    std::string getBloodGroup() const { return bloodGroup; }
    void setBloodGroup(const std::string& bg) { this->bloodGroup = bg; }

    std::string getMedicalHistory() const { return medicalHistory; }
    void setMedicalHistory(const std::string& history) { this->medicalHistory = history; }
};

#endif
