#include "../include/Hospital.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

namespace {
    void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string readLine(const std::string& prompt) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        return line;
    }
}

Hospital::Hospital() {
    loadData();
}

Patient* Hospital::findPatientById(const std::string& id) {
    for (auto& patient : patients) {
        if (patient.getId() == id) {
            return &patient;
        }
    }
    return nullptr;
}

Doctor* Hospital::findDoctorById(const std::string& id) {
    for (auto& doctor : doctors) {
        if (doctor.getId() == id) {
            return &doctor;
        }
    }
    return nullptr;
}

void Hospital::loadData() {
    // 1. Patients
    std::ifstream pFile("data/patients.txt");
    if (pFile.is_open()) {
        std::string line;
        while (std::getline(pFile, line)) {
            if (!line.empty()) {
                patients.push_back(Patient::fromFileString(line));
            }
        }
        pFile.close();
    }

    // 2. Doctors
    std::ifstream dFile("data/doctors.txt");
    if (dFile.is_open()) {
        std::string line;
        while (std::getline(dFile, line)) {
            if (!line.empty()) {
                doctors.push_back(Doctor::fromFileString(line));
            }
        }
        dFile.close();
    }

    // 3. Appointments
    std::ifstream aFile("data/appointments.txt");
    if (aFile.is_open()) {
        std::string line;
        while (std::getline(aFile, line)) {
            if (!line.empty()) {
                appointments.push_back(Appointment::fromFileString(line));
            }
        }
        aFile.close();
    }
}

void Hospital::saveData() const {
    // 1. Patients
    std::ofstream pFile("data/patients.txt");
    if (pFile.is_open()) {
        for (const auto& patient : patients) {
            pFile << patient.toFileString() << "\n";
        }
        pFile.close();
    }

    // 2. Doctors
    std::ofstream dFile("data/doctors.txt");
    if (dFile.is_open()) {
        for (const auto& doctor : doctors) {
            dFile << doctor.toFileString() << "\n";
        }
        dFile.close();
    }

    // 3. Appointments
    std::ofstream aFile("data/appointments.txt");
    if (aFile.is_open()) {
        for (const auto& appointment : appointments) {
            aFile << appointment.toFileString() << "\n";
        }
        aFile.close();
    }
}

void Hospital::addPatient() {
    std::cout << "\n=== Register New Patient ===\n";
    std::string id = readLine("Enter Patient ID: ");
    if (findPatientById(id) != nullptr) {
        std::cout << "Error: Patient ID already exists.\n";
        return;
    }

    std::string name = readLine("Enter Name: ");
    std::string ageStr = readLine("Enter Age: ");
    int age = 0;
    try {
        age = std::stoi(ageStr);
    } catch (...) {
        std::cout << "Invalid age entered. Defaulting to 0.\n";
    }

    std::string contact = readLine("Enter Contact Number: ");
    std::string disease = readLine("Enter Disease/Reason for Visit: ");

    patients.emplace_back(id, name, age, contact, disease);
    saveData();
    std::cout << "Patient registered successfully!\n";
}

void Hospital::viewPatients() const {
    std::cout << "\n=== Registered Patients (" << patients.size() << ") ===\n";
    if (patients.empty()) {
        std::cout << "No patients found.\n";
        return;
    }
    for (const auto& patient : patients) {
        patient.display();
    }
}

void Hospital::addDoctor() {
    std::cout << "\n=== Add New Doctor ===\n";
    std::string id = readLine("Enter Doctor ID: ");
    if (findDoctorById(id) != nullptr) {
        std::cout << "Error: Doctor ID already exists.\n";
        return;
    }

    std::string name = readLine("Enter Doctor Name: ");
    std::string ageStr = readLine("Enter Age: ");
    int age = 0;
    try {
        age = std::stoi(ageStr);
    } catch (...) {
        std::cout << "Invalid age entered. Defaulting to 0.\n";
    }

    std::string contact = readLine("Enter Contact Number: ");
    std::string spec = readLine("Enter Specialization (e.g. Cardiology, General): ");

    doctors.emplace_back(id, name, age, contact, spec);
    saveData();
    std::cout << "Doctor added successfully!\n";
}

void Hospital::viewDoctors() const {
    std::cout << "\n=== Doctor Directory (" << doctors.size() << ") ===\n";
    if (doctors.empty()) {
        std::cout << "No doctors registered yet.\n";
        return;
    }
    for (const auto& doctor : doctors) {
        doctor.display();
    }
}

void Hospital::bookAppointment() {
    std::cout << "\n=== Book Appointment ===\n";
    std::string apptId = readLine("Enter Appointment ID: ");
    std::string patientId = readLine("Enter Patient ID: ");
    if (findPatientById(patientId) == nullptr) {
        std::cout << "Error: Patient not found. Please register patient first.\n";
        return;
    }

    std::string doctorId = readLine("Enter Doctor ID: ");
    if (findDoctorById(doctorId) == nullptr) {
        std::cout << "Error: Doctor not found.\n";
        return;
    }

    std::string date = readLine("Enter Date (e.g. DD-MM-YYYY): ");

    appointments.emplace_back(apptId, patientId, doctorId, date);
    saveData();
    std::cout << "Appointment booked successfully!\n";
}

void Hospital::viewAppointments() const {
    std::cout << "\n=== Appointments (" << appointments.size() << ") ===\n";
    if (appointments.empty()) {
        std::cout << "No appointments booked yet.\n";
        return;
    }
    for (const auto& appt : appointments) {
        appt.display();
    }
}

void Hospital::run() {
    int choice = 0;
    while (true) {
        std::cout << "\n==========================================\n";
        std::cout << "     HOSPITAL MANAGEMENT SYSTEM (DEMO)    \n";
        std::cout << "==========================================\n";
        std::cout << "1. Register Patient\n";
        std::cout << "2. View All Patients\n";
        std::cout << "3. Add Doctor\n";
        std::cout << "4. View All Doctors\n";
        std::cout << "5. Book Appointment\n";
        std::cout << "6. View All Appointments\n";
        std::cout << "0. Exit\n";
        std::cout << "------------------------------------------\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            clearInputBuffer();
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                viewPatients();
                break;
            case 3:
                addDoctor();
                break;
            case 4:
                viewDoctors();
                break;
            case 5:
                bookAppointment();
                break;
            case 6:
                viewAppointments();
                break;
            case 0:
                std::cout << "Thank you for using the Hospital Management Demo. Goodbye!\n";
                return;
            default:
                std::cout << "Invalid choice. Please choose from 0 to 6.\n";
                break;
        }
    }
}

