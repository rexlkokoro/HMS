#include "../include/Hospital.h"
#include "../include/Exceptions.h"
#include <iostream>
#include <cassert>

void testBookAppointment() {
    Hospital h;
    auto a = h.bookAppointment("P1", "D1", "2023-10-10 10:00", "Fever");
    assert(a->getPatientId() == "P1");
    assert(a->getDoctorId() == "D1");
    assert(a->getStatus() == "Scheduled");
    std::cout << "testBookAppointment passed.\n";
}

void testDoubleBooking() {
    Hospital h;
    h.bookAppointment("P1", "D1", "2023-10-10 10:00", "Fever");
    bool caught = false;
    try {
        h.bookAppointment("P2", "D1", "2023-10-10 10:00", "Cold");
    } catch (const DoubleBookingException&) {
        caught = true;
    }
    assert(caught);
    std::cout << "testDoubleBooking passed.\n";
}

void testCancelAppointment() {
    Hospital h;
    auto a = h.bookAppointment("P1", "D1", "2023-10-10 11:00", "Fever");
    h.cancelAppointment(a->getId());
    assert(a->getStatus() == "Cancelled");
    std::cout << "testCancelAppointment passed.\n";
}

void testCompleteAppointment() {
    Hospital h;
    auto a = h.bookAppointment("P1", "D1", "2023-10-10 12:00", "Checkup");
    h.completeAppointment(a->getId());
    assert(a->getStatus() == "Completed");
    std::cout << "testCompleteAppointment passed.\n";
}

void testCancelCompletedThrows() {
    Hospital h;
    auto a = h.bookAppointment("P1", "D1", "2023-10-10 13:00", "Checkup");
    h.completeAppointment(a->getId());
    bool caught = false;
    try {
        h.cancelAppointment(a->getId());
    } catch (const HospitalException&) {
        caught = true;
    }
    assert(caught);
    std::cout << "testCancelCompletedThrows passed.\n";
}

int main() {
    testBookAppointment();
    testDoubleBooking();
    testCancelAppointment();
    testCompleteAppointment();
    testCancelCompletedThrows();
    return 0;
}
