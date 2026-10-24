#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"
#include <string>

class Doctor : public Person {
private:
    std::string specialization;
    double consultationFee;
    bool available;

public:
    Doctor();
    Doctor(const std::string& id, const std::string& name, int age,
           const std::string& contact, const std::string& specialization,
           double consultationFee);
    ~Doctor() override = default;

    std::string getRole() const override { return "Doctor"; }
    void display() const override;

    // Doctor-specific accessors
    std::string getSpecialization() const { return specialization; }
    void setSpecialization(const std::string& spec) { this->specialization = spec; }

    double getConsultationFee() const { return consultationFee; }
    void setConsultationFee(double fee) { this->consultationFee = fee; }

    bool isAvailable() const { return available; }
    void setAvailable(bool available) { this->available = available; }
};

#endif
