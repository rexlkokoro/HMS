#include "../include/Patient.h"
#include <iostream>
#include <iomanip>

Patient::Patient() : Person(), address(""), bloodGroup(""), medicalHistory("None") {}

Patient::Patient(const std::string& id, const std::string& name, int age,
                 const std::string& contact, const std::string& address,
                 const std::string& bloodGroup)
    : Person(id, name, age, contact), address(address), bloodGroup(bloodGroup), medicalHistory("None") {}

void Patient::display() const {
    std::cout << "------------------------------------------\n";
    std::cout << "Role:            " << getRole() << "\n";
    std::cout << "Patient ID:      " << id << "\n";
    std::cout << "Name:            " << name << "\n";
    std::cout << "Age:             " << age << "\n";
    std::cout << "Contact:         " << contact << "\n";
    std::cout << "Address:         " << address << "\n";
    std::cout << "Blood Group:     " << bloodGroup << "\n";
    std::cout << "Medical History: " << medicalHistory << "\n";
    std::cout << "------------------------------------------\n";
}

