#pragma once
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
