#include "../include/Doctor.h"
#include <iostream>
#include <sstream>

Doctor::Doctor() : Person(), specialization("") {}

Doctor::Doctor(const std::string& id, const std::string& name, int age,
               const std::string& contact, const std::string& specialization)
    : Person(id, name, age, contact), specialization(specialization) {}

void Doctor::display() const {
    std::cout << "------------------------------------------\n";
    std::cout << "Doctor ID:      " << id << "\n";
    std::cout << "Name:           Dr. " << name << "\n";
    std::cout << "Age:            " << age << "\n";
    std::cout << "Contact:        " << contact << "\n";
    std::cout << "Specialization: " << specialization << "\n";
    std::cout << "------------------------------------------\n";
}

std::string Doctor::toFileString() const {
    return id + "|" + name + "|" + std::to_string(age) + "|" + contact + "|" + specialization;
}

Doctor Doctor::fromFileString(const std::string& line) {
    std::stringstream ss(line);
    std::string id, name, ageStr, contact, spec;
    std::getline(ss, id, '|');
    std::getline(ss, name, '|');
    std::getline(ss, ageStr, '|');
    std::getline(ss, contact, '|');
    std::getline(ss, spec, '|');

    int age = 0;
    try {
        if (!ageStr.empty()) age = std::stoi(ageStr);
    } catch (...) {}

    return Doctor(id, name, age, contact, spec);
}

