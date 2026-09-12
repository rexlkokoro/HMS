#include "../include/Hospital.h"
#include "../include/Exceptions.h"
#include <iostream>
#include <cassert>

void testRegisterPatient() {
    Hospital h;
    Patient p;
    p.setName("John Doe");
    p.setAge(30);
    p.setGender("Male");
    p.setContact("1234567890");
    p.setAddress("123 Main St");
    p.setBloodGroup("O+");
    
    auto added = h.addPatient(p);
    assert(added->getName() == "John Doe");
    assert(added->getAge() == 30);
    std::cout << "testRegisterPatient passed.\n";
}

void testDuplicatePatientId() {
    Hospital h;
    Patient p1; p1.setName("Alice"); p1.setAge(25); p1.setGender("Female");
    Patient p2; p2.setName("Bob"); p2.setAge(35); p2.setGender("Male");
    auto a1 = h.addPatient(p1);
    auto a2 = h.addPatient(p2);
    assert(a1->getId() != a2->getId());
    std::cout << "testDuplicatePatientId passed.\n";
}

void testInvalidAge() {
    Patient p;
    bool caught1 = false;
    try { p.setAge(-5); } catch (const InvalidInputException&) { caught1 = true; }
    assert(caught1);

    bool caught2 = false;
    try { p.setAge(200); } catch (const InvalidInputException&) { caught2 = true; }
    assert(caught2);
    
    std::cout << "testInvalidAge passed.\n";
}

void testSearchPatient() {
    Hospital h;
    Patient p1; p1.setName("Alice Smith"); p1.setAge(25); p1.setGender("Female");
    Patient p2; p2.setName("Bob Smith"); p2.setAge(35); p2.setGender("Male");
    Patient p3; p3.setName("Charlie Brown"); p3.setAge(40); p3.setGender("Male");
    h.addPatient(p1);
    h.addPatient(p2);
    h.addPatient(p3);

    auto res = h.searchPatients("Smith");
    assert(res.size() == 2);
    std::cout << "testSearchPatient passed.\n";
}

void testPatientSerialization() {
    Patient p;
    p.setId("P100");
    p.setName("Jane Doe");
    p.setAge(28);
    p.setGender("Female");
    p.setContact("0987654321");
    p.setAddress("456 Elm St");
    p.setBloodGroup("AB-");
    p.setAdmissionDate("2023-01-01");

    std::string data = p.serialize();
    Patient p2;
    p2.deserialize(data);
    assert(p2.getId() == "P100");
    assert(p2.getName() == "Jane Doe");
    assert(p2.getAge() == 28);
    assert(p2.getBloodGroup() == "AB-");
    std::cout << "testPatientSerialization passed.\n";
}

int main() {
    testRegisterPatient();
    testDuplicatePatientId();
    testInvalidAge();
    testSearchPatient();
    testPatientSerialization();
    return 0;
}
