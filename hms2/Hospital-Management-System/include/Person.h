#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

class Person {
protected:
    std::string id;
    std::string name;
    int age;
    std::string contact;

public:
    Person();
    Person(const std::string& id, const std::string& name, int age, const std::string& contact);
    virtual ~Person() = default;

    virtual std::string getRole() const = 0;
    virtual void display() const = 0;

    // Getters
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getContact() const { return contact; }

    // Setters
    void setId(const std::string& id) { this->id = id; }
    void setName(const std::string& name) { this->name = name; }
    void setAge(int age) { this->age = age; }
    void setContact(const std::string& contact) { this->contact = contact; }
};

#endif
