#include "../include/Person.h"

Person::Person(const std::string& name, int age, const std::string& gender, const std::string& contact, const std::string& address) {
    setName(name);
    setAge(age);
    setGender(gender);
    setContact(contact);
    setAddress(address);
}

Person::Person() : age(0) {}

std::string Person::getName() const { return name; }
int Person::getAge() const { return age; }
std::string Person::getGender() const { return gender; }
std::string Person::getContact() const { return contact; }
std::string Person::getAddress() const { return address; }

void Person::setName(const std::string& name) {
    if (name.empty()) {
        throw InvalidInputException("Name cannot be empty.");
    }
    this->name = name;
}

void Person::setAge(int age) {
    if (age < 0 || age > 120) {
        throw InvalidInputException("Age must be between 0 and 120.");
    }
    this->age = age;
}

void Person::setGender(const std::string& gender) {
    if (gender.empty()) {
        throw InvalidInputException("Gender cannot be empty.");
    }
    this->gender = gender;
}

void Person::setContact(const std::string& contact) {
    if (contact.empty()) {
        throw InvalidInputException("Contact cannot be empty.");
    }
    this->contact = contact;
}

void Person::setAddress(const std::string& address) {
    if (address.empty()) {
        throw InvalidInputException("Address cannot be empty.");
    }
    this->address = address;
}

std::ostream& operator<<(std::ostream& os, const Person& person) {
    person.display(os);
    return os;
}
