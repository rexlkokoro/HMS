#include "../include/Hospital.h"
#include <iostream>
#include <cassert>
#include <vector>

void testAdminRole() {
    Admin a;
    assert(a.getRole() == "Admin");
    std::cout << "testAdminRole passed.\n";
}

void testDoctorRole() {
    Doctor d;
    assert(d.getRole() == "Doctor");
    std::cout << "testDoctorRole passed.\n";
}

void testReceptionistRole() {
    Receptionist r;
    assert(r.getRole() == "Receptionist");
    std::cout << "testReceptionistRole passed.\n";
}

void testPatientRole() {
    Patient p;
    assert(p.getRole() == "Patient");
    std::cout << "testPatientRole passed.\n";
}

void testPolymorphism() {
    std::vector<Person*> people;
    Patient p;
    Doctor d;
    Admin a;
    Receptionist r;
    
    people.push_back(&p);
    people.push_back(&d);
    people.push_back(&a);
    people.push_back(&r);
    
    assert(people[0]->getRole() == "Patient");
    assert(people[1]->getRole() == "Doctor");
    assert(people[2]->getRole() == "Admin");
    assert(people[3]->getRole() == "Receptionist");
    
    std::cout << "testPolymorphism passed.\n";
}

int main() {
    testAdminRole();
    testDoctorRole();
    testReceptionistRole();
    testPatientRole();
    testPolymorphism();
    return 0;
}
