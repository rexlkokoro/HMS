#include "Bill.h"
#include "Exceptions.h"
#include <sstream>
#include <iomanip>

Bill::Bill() : consultationFee(0), medicineCost(0), roomCharges(0), discount(0), tax(5), totalAmount(0), paymentStatus("UNPAID") {}

Bill::Bill(const std::string& billId, const std::string& patientId, const std::string& appointmentId, double consultationFee, double medicineCost, double roomCharges, const std::string& date)
    : billId(billId), patientId(patientId), appointmentId(appointmentId), consultationFee(consultationFee), medicineCost(medicineCost), roomCharges(roomCharges), discount(0), tax(5), paymentStatus("UNPAID"), date(date) {
    calculate();
}

void Bill::calculate() {
    double subtotal = consultationFee + medicineCost + roomCharges;
    double discountAmt = subtotal * (discount / 100.0);
    double taxAmt = (subtotal - discountAmt) * (tax / 100.0);
    totalAmount = subtotal - discountAmt + taxAmt;
}

void Bill::applyDiscount(double percent) {
    if (percent < 0 || percent > 100) throw InvalidInputException("Discount must be between 0 and 100.");
    discount = percent;
    calculate();
}

void Bill::setTax(double percent) {
    if (percent < 0 || percent > 100) throw InvalidInputException("Tax must be between 0 and 100.");
    tax = percent;
    calculate();
}

void Bill::markPaid() {
    paymentStatus = "PAID";
}

void Bill::markPartial() {
    paymentStatus = "PARTIAL";
}

std::string Bill::getBillId() const { return billId; }
std::string Bill::getPatientId() const { return patientId; }
std::string Bill::getAppointmentId() const { return appointmentId; }
double Bill::getConsultationFee() const { return consultationFee; }
double Bill::getMedicineCost() const { return medicineCost; }
double Bill::getRoomCharges() const { return roomCharges; }
double Bill::getDiscount() const { return discount; }
double Bill::getTax() const { return tax; }
double Bill::getTotalAmount() const { return totalAmount; }
std::string Bill::getPaymentStatus() const { return paymentStatus; }
std::string Bill::getDate() const { return date; }

std::string Bill::serialize() const {
    std::stringstream ss;
    ss << billId << "|" << patientId << "|" << appointmentId << "|" << consultationFee << "|" << medicineCost << "|" << roomCharges << "|" << discount << "|" << tax << "|" << totalAmount << "|" << paymentStatus << "|" << date;
    return ss.str();
}

Bill Bill::deserialize(const std::string& line) {
    std::stringstream ss(line);
    Bill b;
    std::string val;
    
    std::getline(ss, b.billId, '|');
    std::getline(ss, b.patientId, '|');
    std::getline(ss, b.appointmentId, '|');
    
    std::getline(ss, val, '|'); b.consultationFee = std::stod(val);
    std::getline(ss, val, '|'); b.medicineCost = std::stod(val);
    std::getline(ss, val, '|'); b.roomCharges = std::stod(val);
    std::getline(ss, val, '|'); b.discount = std::stod(val);
    std::getline(ss, val, '|'); b.tax = std::stod(val);
    std::getline(ss, val, '|'); b.totalAmount = std::stod(val);
    
    std::getline(ss, b.paymentStatus, '|');
    std::getline(ss, b.date, '|');
    return b;
}

Bill Bill::operator+(const Bill& other) const {
    Bill newBill;
    newBill.consultationFee = this->consultationFee + other.consultationFee;
    newBill.medicineCost = this->medicineCost + other.medicineCost;
    newBill.roomCharges = this->roomCharges + other.roomCharges;
    newBill.discount = this->discount; // Keep current discount
    newBill.tax = this->tax; // Keep current tax
    newBill.calculate();
    return newBill;
}

std::ostream& operator<<(std::ostream& os, const Bill& b) {
    os << "Bill ID: " << b.billId << " | Patient: " << b.patientId << " | Total: $" << b.totalAmount << " | Status: " << b.paymentStatus;
    return os;
}

std::string Bill::printInvoice() const {
    std::stringstream ss;
    ss << "====================================\n";
    ss << "          HOSPITAL INVOICE          \n";
    ss << "====================================\n";
    ss << "Bill ID: " << billId << "\n";
    ss << "Date: " << date << "\n";
    ss << "Patient ID: " << patientId << "\n";
    ss << "Appointment ID: " << appointmentId << "\n";
    ss << "------------------------------------\n";
    ss << std::fixed << std::setprecision(2);
    ss << "Consultation Fee: $" << consultationFee << "\n";
    ss << "Medicine Cost:    $" << medicineCost << "\n";
    ss << "Room Charges:     $" << roomCharges << "\n";
    ss << "------------------------------------\n";
    double subtotal = consultationFee + medicineCost + roomCharges;
    ss << "Subtotal:         $" << subtotal << "\n";
    ss << "Discount (" << discount << "%):   -$" << (subtotal * discount / 100.0) << "\n";
    double afterDiscount = subtotal - (subtotal * discount / 100.0);
    ss << "Tax (" << tax << "%):        +$" << (afterDiscount * tax / 100.0) << "\n";
    ss << "------------------------------------\n";
    ss << "TOTAL AMOUNT:     $" << totalAmount << "\n";
    ss << "STATUS:           " << paymentStatus << "\n";
    ss << "====================================\n";
    return ss.str();
}
