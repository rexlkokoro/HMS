#include "Hospital.h"
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
        patients[p.getPatientId()] = p;
        int idNum = std::stoi(p.getPatientId().substr(1));
        if (idNum > patientCounter) patientCounter = idNum;
    }
}

void Hospital::savePatients() {
    std::ofstream file(dataDir + "/patients.txt");
    for (const auto& pair : patients) {
        file << pair.second.serialize() << "\n";
    }
}

void Hospital::loadDoctors() {
    std::ifstream file(dataDir + "/doctors.txt");
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        Doctor d = Doctor::deserialize(line);
        doctors[d.getDoctorId()] = d;
        int idNum = std::stoi(d.getDoctorId().substr(1));
        if (idNum > doctorCounter) doctorCounter = idNum;
    }
}

void Hospital::saveDoctors() {
    std::ofstream file(dataDir + "/doctors.txt");
    for (const auto& pair : doctors) {
        file << pair.second.serialize() << "\n";
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
        file << a.serialize() << "\n";
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
        file << p.serialize() << "\n";
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
        file << b.serialize() << "\n";
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
        std::string idLower = pair.second.getPatientId();
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
