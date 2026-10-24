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

Hospital::Hospital() : isLoggedIn(false) {
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

Appointment* Hospital::findAppointmentById(const std::string& id) {
    for (auto& appointment : appointments) {
        if (appointment.getAppointmentId() == id) {
            return &appointment;
        }
    }
    return nullptr;
}

Bill* Hospital::findBillById(const std::string& id) {
    for (auto& bill : bills) {
        if (bill.getBillId() == id) {
            return &bill;
        }
    }
    return nullptr;
}

void Hospital::loadData() {
    // 1. Users
    std::ifstream userFile("data/users.txt");
    if (userFile.is_open()) {
        std::string line;
        while (std::getline(userFile, line)) {
            if (!line.empty()) {
                users.push_back(User::fromFileString(line));
            }
        }
        userFile.close();
    }
    // Seed default admin if user file is empty
    if (users.empty()) {
        users.emplace_back("admin", "admin123", "Admin");
        users.emplace_back("doctor", "doc123", "Doctor");
        users.emplace_back("reception", "rec123", "Receptionist");
    }

    // 2. Patients
    std::ifstream pFile("data/patients.txt");
    if (pFile.is_open()) {
        std::string line;
        while (std::getline(pFile, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string id, name, ageStr, contact, addr, bg, history;
            std::getline(ss, id, '|');
            std::getline(ss, name, '|');
            std::getline(ss, ageStr, '|');
            std::getline(ss, contact, '|');
            std::getline(ss, addr, '|');
            std::getline(ss, bg, '|');
            std::getline(ss, history, '|');

            int age = 0;
            try { if (!ageStr.empty()) age = std::stoi(ageStr); } catch (...) {}

            Patient p(id, name, age, contact, addr, bg);
            if (!history.empty()) p.setMedicalHistory(history);
            patients.push_back(p);
        }
        pFile.close();
    }

    // 3. Doctors
    std::ifstream dFile("data/doctors.txt");
    if (dFile.is_open()) {
        std::string line;
        while (std::getline(dFile, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string id, name, ageStr, contact, spec, feeStr, availStr;
            std::getline(ss, id, '|');
            std::getline(ss, name, '|');
            std::getline(ss, ageStr, '|');
            std::getline(ss, contact, '|');
            std::getline(ss, spec, '|');
            std::getline(ss, feeStr, '|');
            std::getline(ss, availStr, '|');

            int age = 0;
            double fee = 0.0;
            try { if (!ageStr.empty()) age = std::stoi(ageStr); } catch (...) {}
            try { if (!feeStr.empty()) fee = std::stod(feeStr); } catch (...) {}

            Doctor d(id, name, age, contact, spec, fee);
            d.setAvailable(availStr != "0");
            doctors.push_back(d);
        }
        dFile.close();
    }

    // 4. Appointments
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

    // 5. Prescriptions
    std::ifstream rxFile("data/prescriptions.txt");
    if (rxFile.is_open()) {
        std::string line;
        while (std::getline(rxFile, line)) {
            if (!line.empty()) {
                prescriptions.push_back(Prescription::fromFileString(line));
            }
        }
        rxFile.close();
    }

    // 6. Bills
    std::ifstream bFile("data/bills.txt");
    if (bFile.is_open()) {
        std::string line;
        while (std::getline(bFile, line)) {
            if (!line.empty()) {
                bills.push_back(Bill::fromFileString(line));
            }
        }
        bFile.close();
    }
}

void Hospital::saveData() const {
    // 1. Users
    std::ofstream userFile("data/users.txt");
    for (const auto& u : users) {
        userFile << u.toFileString() << "\n";
    }

    // 2. Patients
    std::ofstream pFile("data/patients.txt");
    for (const auto& p : patients) {
        pFile << p.getId() << "|" << p.getName() << "|" << p.getAge() << "|"
              << p.getContact() << "|" << p.getAddress() << "|"
              << p.getBloodGroup() << "|" << p.getMedicalHistory() << "\n";
    }

    // 3. Doctors
    std::ofstream dFile("data/doctors.txt");
    for (const auto& d : doctors) {
        dFile << d.getId() << "|" << d.getName() << "|" << d.getAge() << "|"
              << d.getContact() << "|" << d.getSpecialization() << "|"
              << d.getConsultationFee() << "|" << (d.isAvailable() ? "1" : "0") << "\n";
    }

    // 4. Appointments
    std::ofstream aFile("data/appointments.txt");
    for (const auto& a : appointments) {
        aFile << a.toFileString() << "\n";
    }

    // 5. Prescriptions
    std::ofstream rxFile("data/prescriptions.txt");
    for (const auto& rx : prescriptions) {
        rxFile << rx.toFileString() << "\n";
    }

    // 6. Bills
    std::ofstream bFile("data/bills.txt");
    for (const auto& b : bills) {
        bFile << b.toFileString() << "\n";
    }
}

bool Hospital::login() {
    std::cout << "\n==========================================\n";
    std::cout << "         HOSPITAL MANAGEMENT LOGIN        \n";
    std::cout << "==========================================\n";
    std::cout << "[Hint] Default credentials:\n";
    std::cout << "  - admin     / admin123  (Full Access)\n";
    std::cout << "  - doctor    / doc123    (Doctor Access)\n";
    std::cout << "  - reception / rec123    (Receptionist Access)\n";
    std::cout << "------------------------------------------\n";
    std::string uname = readLine("Enter Username: ");
    std::string pwd = readLine("Enter Password: ");

    for (const auto& user : users) {
        if (user.getUsername() == uname && user.authenticate(pwd)) {
            currentUser = user;
            isLoggedIn = true;
            std::cout << "\n[+] Login successful! Welcome, " << currentUser.getUsername()
                      << " (Role: " << currentUser.getRole() << ")\n";
            return true;
        }
    }

    std::cout << "\n[-] Invalid username or password.\n";
    return false;
}

void Hospital::logout() {
    isLoggedIn = false;
    currentUser = User();
    std::cout << "\n[+] Successfully logged out.\n";
}

void Hospital::run() {
    while (true) {
        if (!isLoggedIn) {
            std::cout << "\n==========================================\n";
            std::cout << "   WELCOME TO HOSPITAL MANAGEMENT SYSTEM  \n";
            std::cout << "==========================================\n";
            std::cout << "1. Login\n";
            std::cout << "2. Exit\n";
            std::cout << "Choice: ";
            int opt = 0;
            if (!(std::cin >> opt)) {
                clearInputBuffer();
                continue;
            }
            clearInputBuffer();

            if (opt == 1) {
                login();
            } else if (opt == 2) {
                saveData();
                std::cout << "Goodbye!\n";
                break;
            } else {
                std::cout << "Invalid choice. Please retry.\n";
            }
            continue;
        }

        std::cout << "\n==========================================\n";
        std::cout << "               MAIN MENU                  \n";
        std::cout << " Logged in as: " << currentUser.getUsername()
                  << " (" << currentUser.getRole() << ")\n";
        std::cout << "==========================================\n";
        std::cout << "1. Patient Management\n";
        std::cout << "2. Doctor Management\n";
        std::cout << "3. Appointment Management\n";
        std::cout << "4. Prescription Management\n";
        std::cout << "5. Billing Management\n";
        std::cout << "6. Save All Data\n";
        std::cout << "7. Logout\n";
        std::cout << "Choice: ";

        int choice = 0;
        if (!(std::cin >> choice)) {
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: showPatientMenu(); break;
            case 2: showDoctorMenu(); break;
            case 3: showAppointmentMenu(); break;
            case 4: showPrescriptionMenu(); break;
            case 5: showBillingMenu(); break;
            case 6:
                saveData();
                std::cout << "[+] Data saved successfully.\n";
                break;
            case 7:
                saveData();
                logout();
                break;
            default:
                std::cout << "Invalid selection.\n";
                break;
        }
    }
}

// ---------------- Patient Methods ----------------
void Hospital::showPatientMenu() {
    while (true) {
        std::cout << "\n--- Patient Management ---\n";
        std::cout << "1. Add Patient\n";
        std::cout << "2. View All Patients\n";
        std::cout << "3. Search Patient\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Choice: ";
        int c;
        if (!(std::cin >> c)) { clearInputBuffer(); continue; }
        clearInputBuffer();

        if (c == 1) addPatient();
        else if (c == 2) viewPatients();
        else if (c == 3) searchPatient();
        else if (c == 4) break;
    }
}

void Hospital::addPatient() {
    if (!currentUser.hasPermission("add_patient")) {
        std::cout << "[-] Error: Permission denied.\n";
        return;
    }
    std::cout << "\n--- Add New Patient ---\n";
    std::string id = readLine("Enter Patient ID: ");
    if (findPatientById(id) != nullptr) {
        std::cout << "[-] Error: Patient ID already exists.\n";
        return;
    }
    std::string name = readLine("Enter Name: ");
    int age;
    std::cout << "Enter Age: ";
    while (!(std::cin >> age) || age <= 0) {
        clearInputBuffer();
        std::cout << "Invalid age. Please enter a positive integer: ";
    }
    clearInputBuffer();
    std::string contact = readLine("Enter Contact: ");
    std::string addr = readLine("Enter Address: ");
    std::string bg = readLine("Enter Blood Group: ");

    patients.emplace_back(id, name, age, contact, addr, bg);
    std::cout << "[+] Patient added successfully!\n";
    saveData();
}

void Hospital::viewPatients() const {
    if (!currentUser.hasPermission("view_patient")) {
        std::cout << "[-] Error: Permission denied.\n";
        return;
    }
    if (patients.empty()) {
        std::cout << "No patients registered yet.\n";
        return;
    }
    for (const auto& p : patients) {
        p.display();
    }
}

void Hospital::searchPatient() const {
    if (!currentUser.hasPermission("search_patient") && !currentUser.hasPermission("view_patient")) {
        std::cout << "[-] Error: Permission denied.\n";
        return;
    }
    std::string id = readLine("Enter Patient ID to search: ");
    for (const auto& p : patients) {
        if (p.getId() == id) {
            p.display();
            return;
        }
    }
    std::cout << "[-] Patient not found.\n";
}

// ---------------- Doctor Methods ----------------
void Hospital::showDoctorMenu() {
    while (true) {
        std::cout << "\n--- Doctor Management ---\n";
        std::cout << "1. Add Doctor\n";
        std::cout << "2. View All Doctors\n";
        std::cout << "3. Search Doctor\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Choice: ";
        int c;
        if (!(std::cin >> c)) { clearInputBuffer(); continue; }
        clearInputBuffer();

        if (c == 1) addDoctor();
        else if (c == 2) viewDoctors();
        else if (c == 3) searchDoctor();
        else if (c == 4) break;
    }
}

void Hospital::addDoctor() {
    if (!currentUser.hasPermission("admin") && currentUser.getRole() != "Admin") {
        std::cout << "[-] Error: Only Admin can add doctors.\n";
        return;
    }
    std::cout << "\n--- Add New Doctor ---\n";
    std::string id = readLine("Enter Doctor ID: ");
    if (findDoctorById(id) != nullptr) {
        std::cout << "[-] Error: Doctor ID already exists.\n";
        return;
    }
    std::string name = readLine("Enter Doctor Name: ");
    int age;
    std::cout << "Enter Age: ";
    while (!(std::cin >> age) || age <= 0) {
        clearInputBuffer();
        std::cout << "Invalid age. Enter a positive integer: ";
    }
    clearInputBuffer();
    std::string contact = readLine("Enter Contact: ");
    std::string spec = readLine("Enter Specialization: ");
    double fee;
    std::cout << "Enter Consultation Fee: ";
    while (!(std::cin >> fee) || fee < 0) {
        clearInputBuffer();
        std::cout << "Invalid fee. Enter a non-negative number: ";
    }
    clearInputBuffer();

    doctors.emplace_back(id, name, age, contact, spec, fee);
    std::cout << "[+] Doctor registered successfully!\n";
    saveData();
}

void Hospital::viewDoctors() const {
    if (!currentUser.hasPermission("view_doctor")) {
        std::cout << "[-] Error: Permission denied.\n";
        return;
    }
    if (doctors.empty()) {
        std::cout << "No doctors registered yet.\n";
        return;
    }
    for (const auto& d : doctors) {
        d.display();
    }
}

void Hospital::searchDoctor() const {
    if (!currentUser.hasPermission("search_doctor") && !currentUser.hasPermission("view_doctor")) {
        std::cout << "[-] Error: Permission denied.\n";
        return;
    }
    std::string id = readLine("Enter Doctor ID to search: ");
    for (const auto& d : doctors) {
        if (d.getId() == id) {
            d.display();
            return;
        }
    }
    std::cout << "[-] Doctor not found.\n";
}

// ---------------- Appointment Methods ----------------
void Hospital::showAppointmentMenu() {
    while (true) {
        std::cout << "\n--- Appointment Management ---\n";
        std::cout << "1. Book Appointment\n";
        std::cout << "2. View All Appointments\n";
        std::cout << "3. Cancel Appointment\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Choice: ";
        int c;
        if (!(std::cin >> c)) { clearInputBuffer(); continue; }
        clearInputBuffer();

        if (c == 1) bookAppointment();
        else if (c == 2) viewAppointments();
        else if (c == 3) cancelAppointment();
        else if (c == 4) break;
    }
}

void Hospital::bookAppointment() {
    if (!currentUser.hasPermission("book_appointment")) {
        std::cout << "[-] Error: Permission denied.\n";
        return;
    }
    std::cout << "\n--- Book Appointment ---\n";
    std::string apptId = readLine("Enter Appointment ID: ");
    if (findAppointmentById(apptId) != nullptr) {
        std::cout << "[-] Error: Appointment ID already exists.\n";
        return;
    }
    std::string pId = readLine("Enter Patient ID: ");
    if (findPatientById(pId) == nullptr) {
        std::cout << "[-] Error: Patient ID not found. Register patient first.\n";
        return;
    }
    std::string dId = readLine("Enter Doctor ID: ");
    Doctor* doc = findDoctorById(dId);
    if (doc == nullptr) {
        std::cout << "[-] Error: Doctor ID not found.\n";
        return;
    }
    if (!doc->isAvailable()) {
        std::cout << "[-] Notice: Selected doctor is currently unavailable.\n";
    }

    std::string date = readLine("Enter Date (YYYY-MM-DD): ");
    std::string time = readLine("Enter Time (HH:MM): ");

    appointments.emplace_back(apptId, pId, dId, date, time, "Scheduled");
    std::cout << "[+] Appointment booked successfully!\n";
    saveData();
}

void Hospital::viewAppointments() const {
    if (!currentUser.hasPermission("view_appointment")) {
        std::cout << "[-] Error: Permission denied.\n";
        return;
    }
    if (appointments.empty()) {
        std::cout << "No appointments on record.\n";
        return;
    }
    for (const auto& a : appointments) {
        a.display();
    }
}

void Hospital::cancelAppointment() {
    if (!currentUser.hasPermission("cancel_appointment")) {
        std::cout << "[-] Error: Permission denied.\n";
        return;
    }
    std::string id = readLine("Enter Appointment ID to cancel: ");
    Appointment* appt = findAppointmentById(id);
    if (appt == nullptr) {
        std::cout << "[-] Error: Appointment not found.\n";
        return;
    }
    appt->setStatus("Cancelled");
    std::cout << "[+] Appointment marked as Cancelled.\n";
    saveData();
}

// ---------------- Prescription Methods ----------------
void Hospital::showPrescriptionMenu() {
    while (true) {
        std::cout << "\n--- Prescription Management ---\n";
        std::cout << "1. Add Prescription\n";
        std::cout << "2. View All Prescriptions\n";
        std::cout << "3. Back to Main Menu\n";
        std::cout << "Choice: ";
        int c;
        if (!(std::cin >> c)) { clearInputBuffer(); continue; }
        clearInputBuffer();

        if (c == 1) addPrescription();
        else if (c == 2) viewPrescriptions();
        else if (c == 3) break;
    }
}

void Hospital::addPrescription() {
    if (!currentUser.hasPermission("add_prescription")) {
        std::cout << "[-] Error: Only Doctors or authorized staff can add prescriptions.\n";
        return;
    }
    std::cout << "\n--- Add Prescription ---\n";
    std::string rxId = readLine("Enter Prescription ID: ");
    std::string pId = readLine("Enter Patient ID: ");
    if (findPatientById(pId) == nullptr) {
        std::cout << "[-] Error: Patient ID not found.\n";
        return;
    }
    std::string dId = readLine("Enter Doctor ID: ");
    if (findDoctorById(dId) == nullptr) {
        std::cout << "[-] Error: Doctor ID not found.\n";
        return;
    }
    std::string medicine = readLine("Enter Medicine Name: ");
    std::string dosage = readLine("Enter Dosage (e.g., 500mg twice a day): ");
    std::string duration = readLine("Enter Duration (e.g., 5 days): ");

    prescriptions.emplace_back(rxId, pId, dId, medicine, dosage, duration);
    std::cout << "[+] Prescription added successfully!\n";
    saveData();
}

void Hospital::viewPrescriptions() const {
    if (!currentUser.hasPermission("view_prescription")) {
        std::cout << "[-] Error: Permission denied.\n";
        return;
    }
    if (prescriptions.empty()) {
        std::cout << "No prescriptions recorded.\n";
        return;
    }
    for (const auto& rx : prescriptions) {
        rx.display();
    }
}

// ---------------- Billing Methods ----------------
void Hospital::showBillingMenu() {
    while (true) {
        std::cout << "\n--- Billing Management ---\n";
        std::cout << "1. Generate Bill\n";
        std::cout << "2. View All Bills\n";
        std::cout << "3. Pay Bill\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Choice: ";
        int c;
        if (!(std::cin >> c)) { clearInputBuffer(); continue; }
        clearInputBuffer();

        if (c == 1) generateBill();
        else if (c == 2) viewBills();
        else if (c == 3) payBill();
        else if (c == 4) break;
    }
}

void Hospital::generateBill() {
    if (!currentUser.hasPermission("generate_bill")) {
        std::cout << "[-] Error: Permission denied.\n";
        return;
    }
    std::cout << "\n--- Generate Bill ---\n";
    std::string bId = readLine("Enter Bill ID: ");
    if (findBillById(bId) != nullptr) {
        std::cout << "[-] Error: Bill ID already exists.\n";
        return;
    }
    std::string pId = readLine("Enter Patient ID: ");
    if (findPatientById(pId) == nullptr) {
        std::cout << "[-] Error: Patient ID not found.\n";
        return;
    }
    double amt;
    std::cout << "Enter Amount: ";
    while (!(std::cin >> amt) || amt < 0) {
        clearInputBuffer();
        std::cout << "Invalid amount. Enter a positive number: ";
    }
    clearInputBuffer();
    std::string desc = readLine("Enter Description: ");

    bills.emplace_back(bId, pId, amt, desc.empty() ? "Consultation/Treatment" : desc, "Pending");
    std::cout << "[+] Bill generated successfully!\n";
    saveData();
}

void Hospital::viewBills() const {
    if (!currentUser.hasPermission("view_bill")) {
        std::cout << "[-] Error: Permission denied.\n";
        return;
    }
    if (bills.empty()) {
        std::cout << "No bills recorded.\n";
        return;
    }
    for (const auto& b : bills) {
        b.display();
    }
}

void Hospital::payBill() {
    if (!currentUser.hasPermission("pay_bill")) {
        std::cout << "[-] Error: Permission denied.\n";
        return;
    }
    std::string id = readLine("Enter Bill ID to mark as Paid: ");
    Bill* bill = findBillById(id);
    if (bill == nullptr) {
        std::cout << "[-] Error: Bill not found.\n";
        return;
    }
    bill->markPaid();
    std::cout << "[+] Bill marked as Paid successfully!\n";
    saveData();
}

