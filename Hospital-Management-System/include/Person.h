#pragma once
#include <string>
#include <iostream>
#include "Exceptions.h"

class Person {
protected:
    std::string name;
    int age;
    std::string gender;
    std::string contact;
    std::string address;

public:
    Person(const std::string& name, int age, const std::string& gender, const std::string& contact, const std::string& address);
    Person();
    virtual ~Person() = default;

    virtual void display(std::ostream& os) const = 0;
    virtual std::string getRole() const = 0;
    virtual std::string serialize() const = 0;

    std::string getName() const;
    int getAge() const;
    std::string getGender() const;
    std::string getContact() const;
    std::string getAddress() const;

    void setName(const std::string& name);
    void setAge(int age);
    void setGender(const std::string& gender);
    void setContact(const std::string& contact);
    void setAddress(const std::string& address);

    friend std::ostream& operator<<(std::ostream& os, const Person& person);
};
