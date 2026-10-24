#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <vector>
#include <string>
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"

class Hospital {
private:
    std::vector<Patient> patients;
    std::vector<Doctor> doctors;
    std::vector<Appointment> appointments;

    // Helper finders
    Patient* findPatientById(const std::string& id);
    Doctor* findDoctorById(const std::string& id);

public:
    Hospital();
    ~Hospital() = default;

    // Application lifecycle
    void run();

    // Patient Operations
    void addPatient();
    void viewPatients() const;

    // Doctor Operations
    void addDoctor();
    void viewDoctors() const;

    // Appointment Operations
    void bookAppointment();
    void viewAppointments() const;

    // File Persistence
    void loadData();
    void saveData() const;
};

#endif // HOSPITAL_H

