#pragma once
#include <string>
#include <iostream>

class Bill {
private:
    std::string billId;
    std::string patientId;
    std::string appointmentId;
    double consultationFee;
    double medicineCost;
    double roomCharges;
    double discount;
    double tax;
    double totalAmount;
    std::string paymentStatus;
    std::string date;

public:
    Bill();
    Bill(const std::string& billId, const std::string& patientId, const std::string& appointmentId, double consultationFee, double medicineCost, double roomCharges, const std::string& date);

    void calculate();
    void applyDiscount(double percent);
    void setTax(double percent);
    void markPaid();
    void markPartial();

    std::string getBillId() const;
    std::string getPatientId() const;
    std::string getAppointmentId() const;
    double getConsultationFee() const;
    double getMedicineCost() const;
    double getRoomCharges() const;
    double getDiscount() const;
    double getTax() const;
    double getTotalAmount() const;
    std::string getPaymentStatus() const;
    std::string getDate() const;

    std::string serialize() const;
    static Bill deserialize(const std::string& line);

    Bill operator+(const Bill& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Bill& b);
    
    std::string printInvoice() const;
};
