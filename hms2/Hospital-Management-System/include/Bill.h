#ifndef BILL_H
#define BILL_H

#include <string>

class Bill {
private:
    std::string billId;
    std::string patientId;
    double amount;
    std::string description;
    std::string paymentStatus; // e.g. "Pending", "Paid"

public:
    Bill();
    Bill(const std::string& billId, const std::string& patientId,
         double amount, const std::string& description = "Consultation/Treatment",
         const std::string& paymentStatus = "Pending");

    // Getters
    std::string getBillId() const { return billId; }
    std::string getPatientId() const { return patientId; }
    double getAmount() const { return amount; }
    std::string getDescription() const { return description; }
    std::string getPaymentStatus() const { return paymentStatus; }

    // Setters
    void setBillId(const std::string& id) { billId = id; }
    void setPatientId(const std::string& id) { patientId = id; }
    void setAmount(double amt) { amount = amt; }
    void setDescription(const std::string& desc) { description = desc; }
    void setPaymentStatus(const std::string& status) { paymentStatus = status; }

    void markPaid();
    void display() const;
    std::string toFileString() const;
    static Bill fromFileString(const std::string& line);
};

#endif // BILL_H

