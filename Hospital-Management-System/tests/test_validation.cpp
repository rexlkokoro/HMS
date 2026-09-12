#include "../include/Hospital.h"
#include "../include/Exceptions.h"
#include <iostream>
#include <cassert>

void testEmptyName() {
    Patient p;
    bool caught = false;
    try { p.setName(""); } catch(const InvalidInputException&) { caught = true; }
    assert(caught);
    std::cout << "testEmptyName passed.\n";
}

void testAgeRange() {
    Patient p;
    p.setAge(0);
    p.setAge(120);
    
    bool caught1 = false;
    try { p.setAge(121); } catch(const InvalidInputException&) { caught1 = true; }
    assert(caught1);
    
    bool caught2 = false;
    try { p.setAge(-1); } catch(const InvalidInputException&) { caught2 = true; }
    assert(caught2);
    
    std::cout << "testAgeRange passed.\n";
}

void testBloodGroupValues() {
    Patient p;
    p.setBloodGroup("A+");
    p.setBloodGroup("O-");
    
    bool caught = false;
    try { p.setBloodGroup("Z+"); } catch(const InvalidInputException&) { caught = true; }
    assert(caught);
    
    std::cout << "testBloodGroupValues passed.\n";
}

void testNegativeFee() {
    Doctor d;
    bool caught = false;
    try { d.setConsultationFee(-50.0); } catch(const InvalidInputException&) { caught = true; }
    assert(caught);
    std::cout << "testNegativeFee passed.\n";
}

void testDiscountRange() {
    Hospital h;
    bool caught = false;
    try {
        h.generateBill("P1", "A1", 100, 100, 101.0);
    } catch(const InvalidInputException&) {
        caught = true;
    }
    assert(caught);
    std::cout << "testDiscountRange passed.\n";
}

int main() {
    testEmptyName();
    testAgeRange();
    testBloodGroupValues();
    testNegativeFee();
    testDiscountRange();
    return 0;
}
