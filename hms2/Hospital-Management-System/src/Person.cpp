#include "../include/Person.h"

Person::Person() : id(""), name(""), age(0), contact("") {}

Person::Person(const std::string& id, const std::string& name, int age, const std::string& contact)
    : id(id), name(name), age(age), contact(contact) {}

