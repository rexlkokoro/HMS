#include "../include/Bill.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Bill::Bill()
    : billId(""), patientId(""), amount(0.0), description("Consultation/Treatment"), paymentStatus("Pending") {}

Bill::Bill(const std::string& billId, const std::string& patientId,
           double amount, const std::string& description,
           const std::string& paymentStatus)
    : billId(billId), patientId(patientId), amount(amount),
      description(description), paymentStatus(paymentStatus) {}

void Bill::markPaid() {
    paymentStatus = "Paid";
}

void Bill::display() const {
    std::cout << "------------------------------------------\n";
    std::cout << "Bill ID:        " << billId << "\n";
    std::cout << "Patient ID:     " << patientId << "\n";
    std::cout << "Description:    " << description << "\n";
    std::cout << "Amount:         $" << std::fixed << std::setprecision(2) << amount << "\n";
    std::cout << "Payment Status: " << paymentStatus << "\n";
    std::cout << "------------------------------------------\n";
}

std::string Bill::toFileString() const {
    return billId + "|" + patientId + "|" + std::to_string(amount) + "|" + description + "|" + paymentStatus;
}

Bill Bill::fromFileString(const std::string& line) {
    std::stringstream ss(line);
    std::string bId, pId, amtStr, desc, status;

    std::getline(ss, bId, '|');
    std::getline(ss, pId, '|');
    std::getline(ss, amtStr, '|');
    std::getline(ss, desc, '|');
    std::getline(ss, status, '|');

    double amt = 0.0;
    try {
        if (!amtStr.empty()) {
            amt = std::stod(amtStr);
        }
    } catch (...) {
        amt = 0.0;
    }

    return Bill(bId, pId, amt, desc, status.empty() ? "Pending" : status);
}

