import os

project_dir = "/Users/vedant/.gemini/antigravity/scratch/Hospital-Management-System"
os.makedirs(os.path.join(project_dir, "include"), exist_ok=True)
os.makedirs(os.path.join(project_dir, "src"), exist_ok=True)

# FILE 1
with open(os.path.join(project_dir, "include/Appointment.h"), "w") as f:
    f.write("""#pragma once
#include <string>
#include <iostream>

class Appointment {
private:
    std::string appointmentId;
    std::string patientId;
    std::string doctorId;
    std::string dateTime;
    std::string status;
    std::string reason;
    std::string notes;

public:
    Appointment();
    Appointment(const std::string& appointmentId, const std::string& patientId, const std::string& doctorId, const std::string& dateTime, const std::string& reason);

    std::string getAppointmentId() const;
    std::string getPatientId() const;
    std::string getDoctorId() const;
    std::string getDateTime() const;
    std::string getStatus() const;
    std::string getReason() const;
    std::string getNotes() const;
    void setNotes(const std::string& notes);

    void complete();
    void cancel();
    void reschedule(const std::string& newDateTime);

    std::string serialize() const;
    static Appointment deserialize(const std::string& line);

    bool operator<(const Appointment& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Appointment& appt);
};
""")

# FILE 2
with open(os.path.join(project_dir, "src/Appointment.cpp"), "w") as f:
    f.write("""#include "Appointment.h"
#include "Exceptions.h"
#include <sstream>

Appointment::Appointment() : status("SCHEDULED") {}

Appointment::Appointment(const std::string& appointmentId, const std::string& patientId, const std::string& doctorId, const std::string& dateTime, const std::string& reason)
    : appointmentId(appointmentId), patientId(patientId), doctorId(doctorId), dateTime(dateTime), status("SCHEDULED"), reason(reason) {}

std::string Appointment::getAppointmentId() const { return appointmentId; }
std::string Appointment::getPatientId() const { return patientId; }
std::string Appointment::getDoctorId() const { return doctorId; }
std::string Appointment::getDateTime() const { return dateTime; }
std::string Appointment::getStatus() const { return status; }
std::string Appointment::getReason() const { return reason; }
std::string Appointment::getNotes() const { return notes; }
void Appointment::setNotes(const std::string& notes) { this->notes = notes; }

void Appointment::complete() {
    if (status == "CANCELLED") throw InvalidInputException("Cannot complete a cancelled appointment.");
    status = "COMPLETED";
}

void Appointment::cancel() {
    if (status == "COMPLETED") throw InvalidInputException("Cannot cancel a completed appointment.");
    status = "CANCELLED";
}

void Appointment::reschedule(const std::string& newDateTime) {
    if (status != "SCHEDULED") throw InvalidInputException("Can only reschedule scheduled appointments.");
    dateTime = newDateTime;
}

std::string Appointment::serialize() const {
    return appointmentId + "|" + patientId + "|" + doctorId + "|" + dateTime + "|" + status + "|" + reason + "|" + notes;
}

Appointment Appointment::deserialize(const std::string& line) {
    std::stringstream ss(line);
    Appointment appt;
    std::getline(ss, appt.appointmentId, '|');
    std::getline(ss, appt.patientId, '|');
    std::getline(ss, appt.doctorId, '|');
    std::getline(ss, appt.dateTime, '|');
    std::getline(ss, appt.status, '|');
    std::getline(ss, appt.reason, '|');
    std::getline(ss, appt.notes, '|');
    return appt;
}

bool Appointment::operator<(const Appointment& other) const {
    return dateTime < other.dateTime;
}

std::ostream& operator<<(std::ostream& os, const Appointment& appt) {
    os << "Appointment: " << appt.appointmentId << " | Patient: " << appt.patientId << " | Doctor: " << appt.doctorId 
       << " | Date: " << appt.dateTime << " | Status: " << appt.status << " | Reason: " << appt.reason;
    return os;
}
""")

# FILE 3
with open(os.path.join(project_dir, "include/Prescription.h"), "w") as f:
    f.write("""#pragma once
#include <string>
#include <vector>
#include <iostream>

struct Medicine {
    std::string name, dosage, frequency, duration, notes;
    std::string serialize() const;
    static Medicine deserialize(const std::string& data);
};

class Prescription {
private:
    std::string prescriptionId;
    std::string appointmentId;
    std::string patientId;
    std::string doctorId;
    std::vector<Medicine> medicines;
    std::string date;
    std::string notes;

public:
    Prescription();
    Prescription(const std::string& prescriptionId, const std::string& appointmentId, const std::string& patientId, const std::string& doctorId, const std::string& date);

    void addMedicine(const Medicine& m);
    void removeMedicine(int index);
    const std::vector<Medicine>& getMedicines() const;

    std::string getPrescriptionId() const;
    std::string getAppointmentId() const;
    std::string getPatientId() const;
    std::string getDoctorId() const;
    std::string getDate() const;
    std::string getNotes() const;
    void setNotes(const std::string& notes);

    std::string serialize() const;
    static Prescription deserialize(const std::string& line);
    friend std::ostream& operator<<(std::ostream& os, const Prescription& p);
};
""")

# FILE 4
with open(os.path.join(project_dir, "src/Prescription.cpp"), "w") as f:
    f.write("""#include "Prescription.h"
#include "Exceptions.h"
#include <sstream>

std::string Medicine::serialize() const {
    return name + ":" + dosage + ":" + frequency + ":" + duration + ":" + notes;
}

Medicine Medicine::deserialize(const std::string& data) {
    std::stringstream ss(data);
    Medicine m;
    std::getline(ss, m.name, ':');
    std::getline(ss, m.dosage, ':');
    std::getline(ss, m.frequency, ':');
    std::getline(ss, m.duration, ':');
    std::getline(ss, m.notes, ':');
    return m;
}

Prescription::Prescription() {}

Prescription::Prescription(const std::string& prescriptionId, const std::string& appointmentId, const std::string& patientId, const std::string& doctorId, const std::string& date)
    : prescriptionId(prescriptionId), appointmentId(appointmentId), patientId(patientId), doctorId(doctorId), date(date) {}

void Prescription::addMedicine(const Medicine& m) {
    medicines.push_back(m);
}

void Prescription::removeMedicine(int index) {
    if (index >= 0 && index < static_cast<int>(medicines.size())) {
        medicines.erase(medicines.begin() + index);
    } else {
        throw InvalidInputException("Invalid medicine index.");
    }
}

const std::vector<Medicine>& Prescription::getMedicines() const {
    return medicines;
}

std::string Prescription::getPrescriptionId() const { return prescriptionId; }
std::string Prescription::getAppointmentId() const { return appointmentId; }
std::string Prescription::getPatientId() const { return patientId; }
std::string Prescription::getDoctorId() const { return doctorId; }
std::string Prescription::getDate() const { return date; }
std::string Prescription::getNotes() const { return notes; }
void Prescription::setNotes(const std::string& n) { notes = n; }

std::string Prescription::serialize() const {
    std::string res = prescriptionId + "|" + appointmentId + "|" + patientId + "|" + doctorId + "|" + date + "|" + notes + "|";
    for (size_t i = 0; i < medicines.size(); ++i) {
        res += medicines[i].serialize();
        if (i < medicines.size() - 1) res += ";";
    }
    return res;
}

Prescription Prescription::deserialize(const std::string& line) {
    std::stringstream ss(line);
    Prescription p;
    std::getline(ss, p.prescriptionId, '|');
    std::getline(ss, p.appointmentId, '|');
    std::getline(ss, p.patientId, '|');
    std::getline(ss, p.doctorId, '|');
    std::getline(ss, p.date, '|');
    std::getline(ss, p.notes, '|');
    
    std::string meds;
    if (std::getline(ss, meds, '|')) {
        std::stringstream mss(meds);
        std::string medStr;
        while (std::getline(mss, medStr, ';')) {
            if(!medStr.empty()) p.addMedicine(Medicine::deserialize(medStr));
        }
    }
    return p;
}

std::ostream& operator<<(std::ostream& os, const Prescription& p) {
    os << "Prescription: " << p.prescriptionId << " | Appt: " << p.appointmentId << " | Medicines: " << p.medicines.size();
    return os;
}
""")

# FILE 5
with open(os.path.join(project_dir, "include/Bill.h"), "w") as f:
    f.write("""#pragma once
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
""")

# FILE 6
with open(os.path.join(project_dir, "src/Bill.cpp"), "w") as f:
    f.write("""#include "Bill.h"
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
""")

# FILE 7
with open(os.path.join(project_dir, "include/Hospital.h"), "w") as f:
    f.write("""#pragma once
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <mutex>
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "Receptionist.h"
#include "Appointment.h"
#include "Prescription.h"
#include "Bill.h"
#include "Exceptions.h"

struct HospitalStats {
    int totalPatients;
    int totalDoctors;
    int todayAppointments;
    double totalRevenue;
};

struct ActivityLogEntry {
    std::string timestamp;
    std::string action;
    std::string details;
};

class Hospital {
private:
    std::string name;
    std::map<std::string, Patient> patients;
    std::map<std::string, Doctor> doctors;
    std::map<std::string, Admin> admins;
    std::map<std::string, Receptionist> receptionists;
    std::vector<Appointment> appointments;
    std::vector<Prescription> prescriptions;
    std::vector<Bill> bills;
    std::vector<ActivityLogEntry> activityLog;
    
    int patientCounter;
    int doctorCounter;
    int adminCounter;
    int receptionistCounter;
    int appointmentCounter;
    int prescriptionCounter;
    int billCounter;
    
    std::string dataDir;
    
    std::string generateId(const std::string& prefix, int& counter);
    void logActivity(const std::string& action, const std::string& details);
    std::string getCurrentTimestamp() const;
    std::string getCurrentDate() const;
    
public:
    Hospital(const std::string& name = "Smart Hospital", const std::string& dataDir = "data");
    
    // Data persistence
    void loadAllData();
    void saveAllData();
    void loadPatients();
    void savePatients();
    void loadDoctors();
    void saveDoctors();
    void loadAppointments();
    void saveAppointments();
    void loadPrescriptions();
    void savePrescriptions();
    void loadBills();
    void saveBills();
    
    // Patient operations
    Patient& addPatient(const std::string& name, int age, const std::string& gender,
                        const std::string& contact, const std::string& address,
                        const std::string& bloodGroup, const std::string& admissionDate);
    Patient& getPatient(const std::string& id);
    const std::map<std::string, Patient>& getAllPatients() const;
    std::vector<Patient> searchPatients(const std::string& query) const;
    
    // Doctor operations
    Doctor& addDoctor(const std::string& name, int age, const std::string& gender,
                      const std::string& contact, const std::string& address,
                      const std::string& department, const std::string& specialization,
                      const std::string& qualifications, double consultationFee);
    Doctor& getDoctor(const std::string& id);
    const std::map<std::string, Doctor>& getAllDoctors() const;
    
    // Appointment operations
    Appointment& bookAppointment(const std::string& patientId, const std::string& doctorId,
                                  const std::string& dateTime, const std::string& reason);
    void cancelAppointment(const std::string& appointmentId);
    void completeAppointment(const std::string& appointmentId);
    const std::vector<Appointment>& getAllAppointments() const;
    std::vector<Appointment> getAppointmentsByDate(const std::string& date) const;
    Appointment* findAppointment(const std::string& id);
    
    // Prescription operations
    Prescription& addPrescription(const std::string& appointmentId, const std::string& patientId,
                                   const std::string& doctorId, const std::vector<Medicine>& medicines,
                                   const std::string& notes);
    std::vector<Prescription> getPrescriptionsByAppointment(const std::string& appointmentId) const;
    std::vector<Prescription> getPrescriptionsByPatient(const std::string& patientId) const;
    const std::vector<Prescription>& getAllPrescriptions() const;
    
    // Billing operations
    Bill& generateBill(const std::string& patientId, const std::string& appointmentId,
                       double medicineCost, double roomCharges, double discountPercent);
    void payBill(const std::string& billId);
    const std::vector<Bill>& getAllBills() const;
    std::vector<Bill> getBillsByPatient(const std::string& patientId) const;
    Bill* findBill(const std::string& id);
    
    // Dashboard
    HospitalStats getStats() const;
    const std::vector<ActivityLogEntry>& getActivityLog() const;
    
    // Polymorphism demo
    void displayAllPersonnel(std::ostream& os) const;
};
""")

# FILE 8
with open(os.path.join(project_dir, "src/Hospital.cpp"), "w") as f:
    f.write("""#include "Hospital.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <iostream>

Hospital::Hospital(const std::string& name, const std::string& dataDir)
    : name(name), dataDir(dataDir), patientCounter(0), doctorCounter(0), adminCounter(0), receptionistCounter(0), appointmentCounter(0), prescriptionCounter(0), billCounter(0) {
    std::filesystem::create_directories(dataDir);
}

std::string Hospital::generateId(const std::string& prefix, int& counter) {
    counter++;
    std::stringstream ss;
    ss << prefix << std::setw(3) << std::setfill('0') << counter;
    return ss.str();
}

void Hospital::logActivity(const std::string& action, const std::string& details) {
    activityLog.push_back({getCurrentTimestamp(), action, details});
}

std::string Hospital::getCurrentTimestamp() const {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_c);
    std::stringstream ss;
    ss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string Hospital::getCurrentDate() const {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_c);
    std::stringstream ss;
    ss << std::put_time(now_tm, "%Y-%m-%d");
    return ss.str();
}

void Hospital::loadAllData() {
    loadPatients();
    loadDoctors();
    loadAppointments();
    loadPrescriptions();
    loadBills();
}

void Hospital::saveAllData() {
    savePatients();
    saveDoctors();
    saveAppointments();
    savePrescriptions();
    saveBills();
}

void Hospital::loadPatients() {
    std::ifstream file(dataDir + "/patients.txt");
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        Patient p = Patient::deserialize(line);
        patients[p.getId()] = p;
        int idNum = std::stoi(p.getId().substr(1));
        if (idNum > patientCounter) patientCounter = idNum;
    }
}

void Hospital::savePatients() {
    std::ofstream file(dataDir + "/patients.txt");
    for (const auto& pair : patients) {
        file << pair.second.serialize() << "\\n";
    }
}

void Hospital::loadDoctors() {
    std::ifstream file(dataDir + "/doctors.txt");
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        Doctor d = Doctor::deserialize(line);
        doctors[d.getId()] = d;
        int idNum = std::stoi(d.getId().substr(1));
        if (idNum > doctorCounter) doctorCounter = idNum;
    }
}

void Hospital::saveDoctors() {
    std::ofstream file(dataDir + "/doctors.txt");
    for (const auto& pair : doctors) {
        file << pair.second.serialize() << "\\n";
    }
}

void Hospital::loadAppointments() {
    std::ifstream file(dataDir + "/appointments.txt");
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        Appointment a = Appointment::deserialize(line);
        appointments.push_back(a);
        int idNum = std::stoi(a.getAppointmentId().substr(1));
        if (idNum > appointmentCounter) appointmentCounter = idNum;
    }
}

void Hospital::saveAppointments() {
    std::ofstream file(dataDir + "/appointments.txt");
    for (const auto& a : appointments) {
        file << a.serialize() << "\\n";
    }
}

void Hospital::loadPrescriptions() {
    std::ifstream file(dataDir + "/prescriptions.txt");
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        Prescription p = Prescription::deserialize(line);
        prescriptions.push_back(p);
        int idNum = std::stoi(p.getPrescriptionId().substr(2)); // Assuming PR001
        if (idNum > prescriptionCounter) prescriptionCounter = idNum;
    }
}

void Hospital::savePrescriptions() {
    std::ofstream file(dataDir + "/prescriptions.txt");
    for (const auto& p : prescriptions) {
        file << p.serialize() << "\\n";
    }
}

void Hospital::loadBills() {
    std::ifstream file(dataDir + "/bills.txt");
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        Bill b = Bill::deserialize(line);
        bills.push_back(b);
        int idNum = std::stoi(b.getBillId().substr(1));
        if (idNum > billCounter) billCounter = idNum;
    }
}

void Hospital::saveBills() {
    std::ofstream file(dataDir + "/bills.txt");
    for (const auto& b : bills) {
        file << b.serialize() << "\\n";
    }
}

Patient& Hospital::addPatient(const std::string& name, int age, const std::string& gender,
                              const std::string& contact, const std::string& address,
                              const std::string& bloodGroup, const std::string& admissionDate) {
    std::string id = generateId("P", patientCounter);
    Patient p(id, name, age, gender, contact, address, bloodGroup, admissionDate);
    patients[id] = p;
    savePatients();
    logActivity("ADD_PATIENT", "Added patient: " + name + " (" + id + ")");
    return patients[id];
}

Patient& Hospital::getPatient(const std::string& id) {
    if (patients.find(id) == patients.end()) throw InvalidIdException("Patient ID not found.");
    return patients[id];
}

const std::map<std::string, Patient>& Hospital::getAllPatients() const {
    return patients;
}

std::vector<Patient> Hospital::searchPatients(const std::string& query) const {
    std::vector<Patient> results;
    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);
    
    for (const auto& pair : patients) {
        std::string nameLower = pair.second.getName();
        std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);
        std::string idLower = pair.second.getId();
        std::transform(idLower.begin(), idLower.end(), idLower.begin(), ::tolower);
        
        if (nameLower.find(lowerQuery) != std::string::npos || 
            idLower.find(lowerQuery) != std::string::npos || 
            pair.second.getContact().find(query) != std::string::npos) {
            results.push_back(pair.second);
        }
    }
    return results;
}

Doctor& Hospital::addDoctor(const std::string& name, int age, const std::string& gender,
                            const std::string& contact, const std::string& address,
                            const std::string& department, const std::string& specialization,
                            const std::string& qualifications, double consultationFee) {
    std::string id = generateId("D", doctorCounter);
    Doctor d(id, name, age, gender, contact, address, department, specialization, qualifications, consultationFee);
    doctors[id] = d;
    saveDoctors();
    logActivity("ADD_DOCTOR", "Added doctor: " + name + " (" + id + ")");
    return doctors[id];
}

Doctor& Hospital::getDoctor(const std::string& id) {
    if (doctors.find(id) == doctors.end()) throw InvalidIdException("Doctor ID not found.");
    return doctors[id];
}

const std::map<std::string, Doctor>& Hospital::getAllDoctors() const {
    return doctors;
}

Appointment& Hospital::bookAppointment(const std::string& patientId, const std::string& doctorId,
                                       const std::string& dateTime, const std::string& reason) {
    if (patients.find(patientId) == patients.end()) throw InvalidIdException("Patient ID not found.");
    if (doctors.find(doctorId) == doctors.end()) throw InvalidIdException("Doctor ID not found.");
    
    for (const auto& a : appointments) {
        if (a.getDoctorId() == doctorId && a.getDateTime() == dateTime && a.getStatus() == "SCHEDULED") {
            throw DoubleBookingException("Doctor is already booked at this time.");
        }
    }
    
    std::string id = generateId("A", appointmentCounter);
    Appointment a(id, patientId, doctorId, dateTime, reason);
    appointments.push_back(a);
    saveAppointments();
    logActivity("BOOK_APPT", "Booked appointment " + id + " for patient " + patientId);
    return appointments.back();
}

void Hospital::cancelAppointment(const std::string& appointmentId) {
    Appointment* a = findAppointment(appointmentId);
    if (!a) throw InvalidIdException("Appointment ID not found.");
    a->cancel();
    saveAppointments();
    logActivity("CANCEL_APPT", "Cancelled appointment " + appointmentId);
}

void Hospital::completeAppointment(const std::string& appointmentId) {
    Appointment* a = findAppointment(appointmentId);
    if (!a) throw InvalidIdException("Appointment ID not found.");
    a->complete();
    saveAppointments();
    logActivity("COMPL_APPT", "Completed appointment " + appointmentId);
}

const std::vector<Appointment>& Hospital::getAllAppointments() const {
    return appointments;
}

std::vector<Appointment> Hospital::getAppointmentsByDate(const std::string& date) const {
    std::vector<Appointment> results;
    for (const auto& a : appointments) {
        if (a.getDateTime().substr(0, 10) == date) {
            results.push_back(a);
        }
    }
    return results;
}

Appointment* Hospital::findAppointment(const std::string& id) {
    for (auto& a : appointments) {
        if (a.getAppointmentId() == id) return &a;
    }
    return nullptr;
}

Prescription& Hospital::addPrescription(const std::string& appointmentId, const std::string& patientId,
                                        const std::string& doctorId, const std::vector<Medicine>& medicines,
                                        const std::string& notes) {
    std::string id = generateId("PR", prescriptionCounter);
    Prescription p(id, appointmentId, patientId, doctorId, getCurrentDate());
    p.setNotes(notes);
    for (const auto& m : medicines) {
        p.addMedicine(m);
    }
    prescriptions.push_back(p);
    savePrescriptions();
    logActivity("ADD_PRESCR", "Added prescription " + id + " for appointment " + appointmentId);
    return prescriptions.back();
}

std::vector<Prescription> Hospital::getPrescriptionsByAppointment(const std::string& appointmentId) const {
    std::vector<Prescription> results;
    for (const auto& p : prescriptions) {
        if (p.getAppointmentId() == appointmentId) {
            results.push_back(p);
        }
    }
    return results;
}

std::vector<Prescription> Hospital::getPrescriptionsByPatient(const std::string& patientId) const {
    std::vector<Prescription> results;
    for (const auto& p : prescriptions) {
        if (p.getPatientId() == patientId) {
            results.push_back(p);
        }
    }
    return results;
}

const std::vector<Prescription>& Hospital::getAllPrescriptions() const {
    return prescriptions;
}

Bill& Hospital::generateBill(const std::string& patientId, const std::string& appointmentId,
                             double medicineCost, double roomCharges, double discountPercent) {
    if (patients.find(patientId) == patients.end()) throw InvalidIdException("Patient ID not found.");
    
    double consultationFee = 0;
    Appointment* appt = findAppointment(appointmentId);
    if (appt) {
        auto docIt = doctors.find(appt->getDoctorId());
        if (docIt != doctors.end()) {
            consultationFee = docIt->second.getConsultationFee();
        }
    }
    
    std::string id = generateId("B", billCounter);
    Bill b(id, patientId, appointmentId, consultationFee, medicineCost, roomCharges, getCurrentDate());
    b.applyDiscount(discountPercent);
    bills.push_back(b);
    saveBills();
    logActivity("GEN_BILL", "Generated bill " + id + " for patient " + patientId);
    return bills.back();
}

void Hospital::payBill(const std::string& billId) {
    Bill* b = findBill(billId);
    if (!b) throw InvalidIdException("Bill ID not found.");
    b->markPaid();
    saveBills();
    logActivity("PAY_BILL", "Paid bill " + billId);
}

const std::vector<Bill>& Hospital::getAllBills() const {
    return bills;
}

std::vector<Bill> Hospital::getBillsByPatient(const std::string& patientId) const {
    std::vector<Bill> results;
    for (const auto& b : bills) {
        if (b.getPatientId() == patientId) {
            results.push_back(b);
        }
    }
    return results;
}

Bill* Hospital::findBill(const std::string& id) {
    for (auto& b : bills) {
        if (b.getBillId() == id) return &b;
    }
    return nullptr;
}

HospitalStats Hospital::getStats() const {
    HospitalStats stats;
    stats.totalPatients = patients.size();
    stats.totalDoctors = doctors.size();
    
    std::string today = getCurrentDate();
    int apptCount = 0;
    for (const auto& a : appointments) {
        if (a.getDateTime().substr(0, 10) == today) apptCount++;
    }
    stats.todayAppointments = apptCount;
    
    double revenue = 0;
    for (const auto& b : bills) {
        if (b.getPaymentStatus() == "PAID") revenue += b.getTotalAmount();
    }
    stats.totalRevenue = revenue;
    
    return stats;
}

const std::vector<ActivityLogEntry>& Hospital::getActivityLog() const {
    return activityLog;
}

void Hospital::displayAllPersonnel(std::ostream& os) const {
    std::vector<const Person*> personnel;
    for (const auto& p : patients) {
        personnel.push_back(&p.second);
    }
    for (const auto& d : doctors) {
        personnel.push_back(&d.second);
    }
    // Polymorphic display
    for (const Person* p : personnel) {
        p->display(os);
    }
}
""")

print("All files successfully generated.")
