#include "../include/Patient.h"
#include <iostream>
#include <sstream>

Patient::Patient() : Person(), disease("") {}

Patient::Patient(const std::string& id, const std::string& name, int age,
                 const std::string& contact, const std::string& disease)
    : Person(id, name, age, contact), disease(disease) {}

void Patient::display() const {
    std::cout << "------------------------------------------\n";
    std::cout << "Patient ID: " << id << "\n";
    std::cout << "Name:       " << name << "\n";
    std::cout << "Age:        " << age << "\n";
    std::cout << "Contact:    " << contact << "\n";
    std::cout << "Disease:    " << disease << "\n";
    std::cout << "------------------------------------------\n";
}

std::string Patient::toFileString() const {
    return id + "|" + name + "|" + std::to_string(age) + "|" + contact + "|" + disease;
}

Patient Patient::fromFileString(const std::string& line) {
    std::stringstream ss(line);
    std::string id, name, ageStr, contact, disease;
    std::getline(ss, id, '|');
    std::getline(ss, name, '|');
    std::getline(ss, ageStr, '|');
    std::getline(ss, contact, '|');
    std::getline(ss, disease, '|');

    int age = 0;
    try {
        if (!ageStr.empty()) age = std::stoi(ageStr);
    } catch (...) {}

    return Patient(id, name, age, contact, disease);
}

