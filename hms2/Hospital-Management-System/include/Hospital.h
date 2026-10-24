#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <vector>
#include <string>
#include <memory>
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "Prescription.h"
#include "Bill.h"
#include "User.h"
#include "Exceptions.h"

class Hospital {
private:
    std::vector<Patient> patients;
    std::vector<Doctor> doctors;
    std::vector<Appointment> appointments;
    std::vector<Prescription> prescriptions;
    std::vector<Bill> bills;
    std::vector<User> users;
    User currentUser;
    bool isLoggedIn;

    // Helper finders
    Patient* findPatientById(const std::string& id);
    Doctor* findDoctorById(const std::string& id);
    Appointment* findAppointmentById(const std::string& id);
    Bill* findBillById(const std::string& id);

    // Internal submenus
    void showPatientMenu();
    void showDoctorMenu();
    void showAppointmentMenu();
    void showPrescriptionMenu();
    void showBillingMenu();

public:
    Hospital();
    ~Hospital() = default;

    // Core Lifecycle
    void run();
    bool login();
    void logout();

    // Patient Operations
    void addPatient();
    void viewPatients() const;
    void searchPatient() const;

    // Doctor Operations
    void addDoctor();
    void viewDoctors() const;
    void searchDoctor() const;

    // Appointment Operations
    void bookAppointment();
    void viewAppointments() const;
    void cancelAppointment();

    // Prescription Operations
    void addPrescription();
    void viewPrescriptions() const;

    // Billing Operations
    void generateBill();
    void viewBills() const;
    void payBill();

    // File Persistence
    void loadData();
    void saveData() const;
};

#endif // HOSPITAL_H

