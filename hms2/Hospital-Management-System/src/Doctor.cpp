#include "../include/Doctor.h"
#include <iostream>
#include <iomanip>

Doctor::Doctor() : Person(), specialization(""), consultationFee(0.0), available(true) {}

Doctor::Doctor(const std::string& id, const std::string& name, int age,
               const std::string& contact, const std::string& specialization,
               double consultationFee)
    : Person(id, name, age, contact), specialization(specialization),
      consultationFee(consultationFee), available(true) {}

void Doctor::display() const {
    std::cout << "------------------------------------------\n";
    std::cout << "Role:            " << getRole() << "\n";
    std::cout << "Doctor ID:       " << id << "\n";
    std::cout << "Name:            Dr. " << name << "\n";
    std::cout << "Age:             " << age << "\n";
    std::cout << "Contact:         " << contact << "\n";
    std::cout << "Specialization:  " << specialization << "\n";
    std::cout << "Consultation Fee: $" << std::fixed << std::setprecision(2) << consultationFee << "\n";
    std::cout << "Status:          " << (available ? "Available" : "Unavailable") << "\n";
    std::cout << "------------------------------------------\n";
}

