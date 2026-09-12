#include "../include/Hospital.h"
#include "../include/Exceptions.h"
#include <iostream>
#include <cassert>
#include <cmath>

void testBillCalculation() {
    Hospital h;
    auto b = h.generateBill("P1", "A1", 100.0, 500.0, 0.0);
    // Assuming consultation fee defaults to 0 if doctor not found or not mapped
    assert(std::abs(b->getTotalAmount() - 600.0) < 0.01);
    std::cout << "testBillCalculation passed.\n";
}

void testApplyDiscount() {
    Hospital h;
    auto b = h.generateBill("P1", "A1", 100.0, 500.0, 10.0);
    // 600 - 10% = 540
    assert(std::abs(b->getTotalAmount() - 540.0) < 0.01);
    std::cout << "testApplyDiscount passed.\n";
}

void testBillOperatorPlus() {
    Bill b1; b1.setMedicineCost(100.0); b1.setRoomCharges(200.0);
    Bill b2; b2.setMedicineCost(50.0); b2.setRoomCharges(100.0);
    Bill b3 = b1 + b2;
    assert(std::abs(b3.getMedicineCost() - 150.0) < 0.01);
    assert(std::abs(b3.getRoomCharges() - 300.0) < 0.01);
    std::cout << "testBillOperatorPlus passed.\n";
}

void testMarkPaid() {
    Hospital h;
    auto b = h.generateBill("P1", "A1", 100.0, 500.0, 0.0);
    assert(b->getPaymentStatus() == "Pending");
    h.payBill(b->getId());
    assert(b->getPaymentStatus() == "Paid");
    std::cout << "testMarkPaid passed.\n";
}

void testBillSerialization() {
    Bill b;
    b.setId("B001");
    b.setPatientId("P001");
    b.setMedicineCost(150.5);
    b.setPaymentStatus("Paid");
    
    std::string s = b.serialize();
    Bill b2;
    b2.deserialize(s);
    assert(b2.getId() == "B001");
    assert(b2.getPaymentStatus() == "Paid");
    assert(std::abs(b2.getMedicineCost() - 150.5) < 0.01);
    std::cout << "testBillSerialization passed.\n";
}

int main() {
    testBillCalculation();
    testApplyDiscount();
    testBillOperatorPlus();
    testMarkPaid();
    testBillSerialization();
    return 0;
}
