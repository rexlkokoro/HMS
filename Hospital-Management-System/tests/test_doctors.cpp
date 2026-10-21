#include "../include/Hospital.h"
#include "../include/Exceptions.h"
#include <iostream>
#include <cassert>

void testRegisterDoctor() {
    Hospital h;
    Doctor d;
    d.setName("Dr. Smith");
    d.setAge(45);
    d.setGender("Male");
    d.setSpecialization("Cardiology");
    d.setConsultationFee(500.0);
    
    auto added = h.addDoctor(d);
    assert(added->getName() == "Dr. Smith");
    assert(added->getSpecialization() == "Cardiology");
    std::cout << "testRegisterDoctor passed.\n";
}

void testInvalidFee() {
    Doctor d;
    bool caught = false;
    try {
        d.setConsultationFee(-100.0);
    } catch (const InvalidInputException&) {
        caught = true;
    }
    assert(caught);
    std::cout << "testInvalidFee passed.\n";
}

void testDoctorAvailability() {
    Doctor d;
    assert(d.isAvailable() == true);
    d.setAvailable(false);
    assert(d.isAvailable() == false);
    std::cout << "testDoctorAvailability passed.\n";
}

void testDoctorSerialization() {
    Doctor d;
    d.setId("D001");
    d.setName("Dr. Adams");
    d.setAge(50);
    d.setGender("Female");
    d.setConsultationFee(1000.0);
    d.setAvailable(false);
    
    std::string s = d.serialize();
    Doctor d2;
    d2.deserialize(s);
    
    assert(d2.getId() == "D001");
    assert(d2.getName() == "Dr. Adams");
    assert(d2.getConsultationFee() == 1000.0);
    assert(d2.isAvailable() == false);
    std::cout << "testDoctorSerialization passed.\n";
}

int main() {
    testRegisterDoctor();
    testInvalidFee();
    testDoctorAvailability();
    testDoctorSerialization();
    return 0;
}
