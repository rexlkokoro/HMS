// =============================================================================
// Smart Hospital Management System — Console Application
// main.cpp — Interactive menu-driven CLI using OOP backend
// =============================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include "include/Hospital.h"
#include "include/Exceptions.h"

using namespace std;

// ========================= UTILITY FUNCTIONS =================================

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pressEnterToContinue() {
    cout << "\n  Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void printLine(int width = 70) {
    cout << "  " << string(width, '-') << endl;
}

void printDoubleLine(int width = 70) {
    cout << "  " << string(width, '=') << endl;
}

void printHeader(const string& title) {
    clearScreen();
    printDoubleLine();
    cout << "  " << setw(35 + title.length()/2) << title << endl;
    printDoubleLine();
    cout << endl;
}

void printSuccess(const string& msg) {
    cout << "\n  [SUCCESS] " << msg << endl;
}

void printError(const string& msg) {
    cout << "\n  [ERROR] " << msg << endl;
}

void printWarning(const string& msg) {
    cout << "\n  [WARNING] " << msg << endl;
}

string readString(const string& prompt) {
    string value;
    cout << "  " << prompt << ": ";
    getline(cin, value);
    return value;
}

int readInt(const string& prompt) {
    string line;
    cout << "  " << prompt << ": ";
    getline(cin, line);
    try {
        return stoi(line);
    } catch (...) {
        throw InvalidInputException("Please enter a valid number.");
    }
}

double readDouble(const string& prompt) {
    string line;
    cout << "  " << prompt << ": ";
    getline(cin, line);
    try {
        return stod(line);
    } catch (...) {
        throw InvalidInputException("Please enter a valid number.");
    }
}

int readChoice(const string& prompt, int minVal, int maxVal) {
    string line;
    cout << "  " << prompt << ": ";
    getline(cin, line);
    try {
        int val = stoi(line);
        if (val < minVal || val > maxVal) {
            throw InvalidInputException("Choice out of range.");
        }
        return val;
    } catch (const InvalidInputException& e) {
        throw;
    } catch (...) {
        throw InvalidInputException("Please enter a valid number.");
    }
}

// ========================= DISPLAY DASHBOARD =================================

void displayDashboard(Hospital& hospital) {
    printHeader("SMART HOSPITAL MANAGEMENT SYSTEM — DASHBOARD");
    
    HospitalStats stats = hospital.getStats();
    
    cout << "  +-------------------+-------------------+-------------------+-------------------+" << endl;
    cout << "  | " << left << setw(18) << "Total Patients"
         << "| " << setw(18) << "Active Doctors"
         << "| " << setw(18) << "Today Appts"
         << "| " << setw(18) << "Total Revenue" << "|" << endl;
    cout << "  +-------------------+-------------------+-------------------+-------------------+" << endl;
    cout << "  | " << left << setw(18) << stats.totalPatients
         << "| " << setw(18) << stats.totalDoctors
         << "| " << setw(18) << stats.todayAppointments
         << "| $" << setw(17) << fixed << setprecision(2) << stats.totalRevenue << "|" << endl;
    cout << "  +-------------------+-------------------+-------------------+-------------------+" << endl;
    
    // Recent Activity
    const auto& log = hospital.getActivityLog();
    if (!log.empty()) {
        cout << "\n  RECENT ACTIVITY:" << endl;
        printLine();
        int count = 0;
        for (int i = (int)log.size() - 1; i >= 0 && count < 5; --i, ++count) {
            cout << "  [" << log[i].timestamp << "] " << log[i].action << " - " << log[i].details << endl;
        }
        printLine();
    }
}

// ========================= PATIENT MANAGEMENT ================================

void registerPatient(Hospital& hospital) {
    printHeader("REGISTER NEW PATIENT");
    
    try {
        string name = readString("Patient Name");
        int age = readInt("Age (0-120)");
        string gender = readString("Gender (Male/Female/Other)");
        string contact = readString("Contact Number");
        string address = readString("Address");
        
        cout << "\n  Blood Group Options: A+, A-, B+, B-, O+, O-, AB+, AB-" << endl;
        string bloodGroup = readString("Blood Group");
        string admissionDate = readString("Admission Date (YYYY-MM-DD)");
        
        Patient& p = hospital.addPatient(name, age, gender, contact, address, bloodGroup, admissionDate);
        
        printSuccess("Patient registered successfully!");
        cout << "\n  Patient ID: " << p.getPatientId() << endl;
        cout << "  Name:       " << p.getName() << endl;
        cout << "  Age:        " << p.getAge() << endl;
        cout << "  Gender:     " << p.getGender() << endl;
        cout << "  Blood Grp:  " << p.getBloodGroup() << endl;
        cout << "  Contact:    " << p.getContact() << endl;
        cout << "  Status:     " << p.getStatus() << endl;
        
    } catch (const HospitalException& e) {
        printError(e.what());
    }
}

void viewAllPatients(Hospital& hospital) {
    printHeader("PATIENT DIRECTORY");
    
    const auto& patients = hospital.getAllPatients();
    if (patients.empty()) {
        printWarning("No patients registered yet.");
        return;
    }
    
    cout << "  " << left << setw(8) << "ID"
         << setw(22) << "Name"
         << setw(6) << "Age"
         << setw(10) << "Gender"
         << setw(8) << "Blood"
         << setw(15) << "Contact"
         << setw(12) << "Status" << endl;
    printLine();
    
    for (const auto& [id, patient] : patients) {
        cout << "  " << left << setw(8) << patient.getPatientId()
             << setw(22) << patient.getName()
             << setw(6) << patient.getAge()
             << setw(10) << patient.getGender()
             << setw(8) << patient.getBloodGroup()
             << setw(15) << patient.getContact()
             << setw(12) << patient.getStatus() << endl;
    }
    
    printLine();
    cout << "  Total: " << patients.size() << " patient(s)" << endl;
}

void searchPatient(Hospital& hospital) {
    printHeader("SEARCH PATIENTS");
    
    string query = readString("Search by Name, ID, or Contact");
    
    vector<Patient> results = hospital.searchPatients(query);
    
    if (results.empty()) {
        printWarning("No patients found matching '" + query + "'");
        return;
    }
    
    cout << "\n  Found " << results.size() << " result(s):\n" << endl;
    
    cout << "  " << left << setw(8) << "ID"
         << setw(22) << "Name"
         << setw(6) << "Age"
         << setw(10) << "Gender"
         << setw(8) << "Blood"
         << setw(15) << "Contact" << endl;
    printLine();
    
    for (const auto& p : results) {
        cout << "  " << left << setw(8) << p.getPatientId()
             << setw(22) << p.getName()
             << setw(6) << p.getAge()
             << setw(10) << p.getGender()
             << setw(8) << p.getBloodGroup()
             << setw(15) << p.getContact() << endl;
    }
}

void viewPatientDetails(Hospital& hospital) {
    printHeader("PATIENT DETAILS");
    
    string id = readString("Enter Patient ID");
    
    try {
        Patient& p = hospital.getPatient(id);
        
        cout << "\n  === PATIENT PROFILE ===" << endl;
        p.display(cout);
        
        const auto& history = p.getMedicalHistory();
        if (!history.empty()) {
            cout << "\n  === MEDICAL HISTORY ===" << endl;
            printLine();
            for (const auto& record : history) {
                record.display(cout);
                printLine(40);
            }
        } else {
            cout << "\n  No medical history records." << endl;
        }
        
    } catch (const InvalidIdException& e) {
        printError(e.what());
    }
}

void addMedicalRecord(Hospital& hospital) {
    printHeader("ADD MEDICAL RECORD");
    
    string patientId = readString("Patient ID");
    
    try {
        Patient& p = hospital.getPatient(patientId);
        
        string recordId = "MR" + to_string(p.getMedicalHistory().size() + 1);
        string doctorId = readString("Doctor ID");
        string diagnosis = readString("Diagnosis");
        string treatment = readString("Treatment");
        string date = readString("Date (YYYY-MM-DD)");
        string notes = readString("Notes");
        
        MedicalRecord record(recordId, patientId, doctorId, diagnosis, treatment, date, notes);
        p.addMedicalRecord(record);
        hospital.savePatients();
        
        printSuccess("Medical record added for patient " + p.getName());
        
    } catch (const HospitalException& e) {
        printError(e.what());
    }
}

void patientMenu(Hospital& hospital) {
    while (true) {
        printHeader("PATIENT MANAGEMENT");
        
        cout << "  1. Register New Patient" << endl;
        cout << "  2. View All Patients" << endl;
        cout << "  3. Search Patient" << endl;
        cout << "  4. View Patient Details" << endl;
        cout << "  5. Add Medical Record" << endl;
        cout << "  0. Back to Main Menu" << endl;
        cout << endl;
        
        try {
            int choice = readChoice("Enter choice", 0, 5);
            
            switch (choice) {
                case 1: registerPatient(hospital); break;
                case 2: viewAllPatients(hospital); break;
                case 3: searchPatient(hospital); break;
                case 4: viewPatientDetails(hospital); break;
                case 5: addMedicalRecord(hospital); break;
                case 0: return;
            }
            
            pressEnterToContinue();
        } catch (const HospitalException& e) {
            printError(e.what());
            pressEnterToContinue();
        }
    }
}

// ========================= DOCTOR MANAGEMENT =================================

void registerDoctor(Hospital& hospital) {
    printHeader("REGISTER NEW DOCTOR");
    
    try {
        string name = readString("Doctor Name");
        int age = readInt("Age (0-120)");
        string gender = readString("Gender (Male/Female/Other)");
        string contact = readString("Contact Number");
        string address = readString("Address");
        string department = readString("Department (e.g. Cardiology, Neurology)");
        string specialization = readString("Specialization");
        string qualifications = readString("Qualifications (e.g. MBBS, MD)");
        double fee = readDouble("Consultation Fee");
        
        Doctor& d = hospital.addDoctor(name, age, gender, contact, address,
                                        department, specialization, qualifications, fee);
        
        printSuccess("Doctor registered successfully!");
        cout << "\n  Doctor ID:       " << d.getDoctorId() << endl;
        cout << "  Name:            " << d.getName() << endl;
        cout << "  Department:      " << d.getDepartment() << endl;
        cout << "  Specialization:  " << d.getSpecialization() << endl;
        cout << "  Consultation Fee: $" << fixed << setprecision(2) << d.getConsultationFee() << endl;
        
    } catch (const HospitalException& e) {
        printError(e.what());
    }
}

void viewAllDoctors(Hospital& hospital) {
    printHeader("DOCTOR DIRECTORY");
    
    const auto& doctors = hospital.getAllDoctors();
    if (doctors.empty()) {
        printWarning("No doctors registered yet.");
        return;
    }
    
    cout << "  " << left << setw(8) << "ID"
         << setw(22) << "Name"
         << setw(16) << "Department"
         << setw(18) << "Specialization"
         << setw(10) << "Fee"
         << setw(10) << "Available" << endl;
    printLine();
    
    for (const auto& [id, doc] : doctors) {
        cout << "  " << left << setw(8) << doc.getDoctorId()
             << setw(22) << doc.getName()
             << setw(16) << doc.getDepartment()
             << setw(18) << doc.getSpecialization()
             << "$" << setw(9) << fixed << setprecision(2) << doc.getConsultationFee()
             << setw(10) << (doc.getIsAvailable() ? "Yes" : "No") << endl;
    }
    
    printLine();
    cout << "  Total: " << doctors.size() << " doctor(s)" << endl;
}

void doctorMenu(Hospital& hospital) {
    while (true) {
        printHeader("DOCTOR MANAGEMENT");
        
        cout << "  1. Register New Doctor" << endl;
        cout << "  2. View All Doctors" << endl;
        cout << "  0. Back to Main Menu" << endl;
        cout << endl;
        
        try {
            int choice = readChoice("Enter choice", 0, 2);
            
            switch (choice) {
                case 1: registerDoctor(hospital); break;
                case 2: viewAllDoctors(hospital); break;
                case 0: return;
            }
            
            pressEnterToContinue();
        } catch (const HospitalException& e) {
            printError(e.what());
            pressEnterToContinue();
        }
    }
}

// ========================= APPOINTMENT MANAGEMENT ============================

void bookAppointment(Hospital& hospital) {
    printHeader("BOOK NEW APPOINTMENT");
    
    // Show available patients and doctors
    const auto& patients = hospital.getAllPatients();
    const auto& doctors = hospital.getAllDoctors();
    
    if (patients.empty()) {
        printWarning("No patients registered. Register a patient first.");
        return;
    }
    if (doctors.empty()) {
        printWarning("No doctors registered. Register a doctor first.");
        return;
    }
    
    cout << "  Available Patients:" << endl;
    for (const auto& [id, p] : patients) {
        cout << "    " << id << " - " << p.getName() << endl;
    }
    
    cout << "\n  Available Doctors:" << endl;
    for (const auto& [id, d] : doctors) {
        cout << "    " << id << " - " << d.getName() << " (" << d.getDepartment() 
             << ") - Fee: $" << fixed << setprecision(2) << d.getConsultationFee() << endl;
    }
    cout << endl;
    
    try {
        string patientId = readString("Patient ID");
        string doctorId = readString("Doctor ID");
        string dateTime = readString("Date & Time (YYYY-MM-DD HH:MM)");
        string reason = readString("Reason for visit");
        
        Appointment& apt = hospital.bookAppointment(patientId, doctorId, dateTime, reason);
        
        printSuccess("Appointment booked successfully!");
        cout << "\n  Appointment ID: " << apt.getAppointmentId() << endl;
        cout << "  Patient:        " << hospital.getPatient(patientId).getName() << endl;
        cout << "  Doctor:         " << hospital.getDoctor(doctorId).getName() << endl;
        cout << "  Date/Time:      " << apt.getDateTime() << endl;
        cout << "  Status:         " << apt.getStatus() << endl;
        
    } catch (const DoubleBookingException& e) {
        printError(string("DOUBLE BOOKING DETECTED! ") + e.what());
    } catch (const HospitalException& e) {
        printError(e.what());
    }
}

void viewAllAppointments(Hospital& hospital) {
    printHeader("APPOINTMENT SCHEDULE");
    
    const auto& appointments = hospital.getAllAppointments();
    if (appointments.empty()) {
        printWarning("No appointments scheduled.");
        return;
    }
    
    cout << "  " << left << setw(10) << "Appt ID"
         << setw(10) << "Patient"
         << setw(10) << "Doctor"
         << setw(20) << "Date/Time"
         << setw(12) << "Status"
         << setw(20) << "Reason" << endl;
    printLine(80);
    
    for (const auto& apt : appointments) {
        cout << "  " << left << setw(10) << apt.getAppointmentId()
             << setw(10) << apt.getPatientId()
             << setw(10) << apt.getDoctorId()
             << setw(20) << apt.getDateTime()
             << setw(12) << apt.getStatus()
             << setw(20) << apt.getReason() << endl;
    }
    
    printLine(80);
    cout << "  Total: " << appointments.size() << " appointment(s)" << endl;
}

void completeAppointment(Hospital& hospital) {
    printHeader("COMPLETE APPOINTMENT");
    
    string id = readString("Enter Appointment ID to mark as COMPLETED");
    
    try {
        hospital.completeAppointment(id);
        printSuccess("Appointment " + id + " marked as COMPLETED.");
    } catch (const HospitalException& e) {
        printError(e.what());
    }
}

void cancelAppointment(Hospital& hospital) {
    printHeader("CANCEL APPOINTMENT");
    
    string id = readString("Enter Appointment ID to CANCEL");
    
    try {
        hospital.cancelAppointment(id);
        printSuccess("Appointment " + id + " has been CANCELLED.");
    } catch (const HospitalException& e) {
        printError(e.what());
    }
}

void appointmentMenu(Hospital& hospital) {
    while (true) {
        printHeader("APPOINTMENT MANAGEMENT");
        
        cout << "  1. Book New Appointment" << endl;
        cout << "  2. View All Appointments" << endl;
        cout << "  3. Complete Appointment" << endl;
        cout << "  4. Cancel Appointment" << endl;
        cout << "  0. Back to Main Menu" << endl;
        cout << endl;
        
        try {
            int choice = readChoice("Enter choice", 0, 4);
            
            switch (choice) {
                case 1: bookAppointment(hospital); break;
                case 2: viewAllAppointments(hospital); break;
                case 3: completeAppointment(hospital); break;
                case 4: cancelAppointment(hospital); break;
                case 0: return;
            }
            
            pressEnterToContinue();
        } catch (const HospitalException& e) {
            printError(e.what());
            pressEnterToContinue();
        }
    }
}

// ========================= PRESCRIPTION MANAGEMENT ===========================

void createPrescription(Hospital& hospital) {
    printHeader("CREATE NEW PRESCRIPTION");
    
    // Show completed/scheduled appointments
    const auto& appointments = hospital.getAllAppointments();
    
    cout << "  Available Appointments:" << endl;
    for (const auto& apt : appointments) {
        if (apt.getStatus() == "SCHEDULED" || apt.getStatus() == "COMPLETED") {
            try {
                string patientName = hospital.getPatient(apt.getPatientId()).getName();
                string doctorName = hospital.getDoctor(apt.getDoctorId()).getName();
                cout << "    " << apt.getAppointmentId() << " - " << patientName 
                     << " with " << doctorName << " [" << apt.getStatus() << "]" << endl;
            } catch (...) {
                cout << "    " << apt.getAppointmentId() << " - " << apt.getPatientId() 
                     << " with " << apt.getDoctorId() << " [" << apt.getStatus() << "]" << endl;
            }
        }
    }
    cout << endl;
    
    try {
        string appointmentId = readString("Appointment ID");
        
        // Resolve patient and doctor from the appointment
        Appointment* apt = hospital.findAppointment(appointmentId);
        if (!apt) {
            throw InvalidIdException("Appointment '" + appointmentId + "' not found.");
        }
        
        string patientId = apt->getPatientId();
        string doctorId = apt->getDoctorId();
        
        cout << "\n  Patient: " << hospital.getPatient(patientId).getName() << endl;
        cout << "  Doctor:  " << hospital.getDoctor(doctorId).getName() << endl;
        
        // Add medicines
        vector<Medicine> medicines;
        cout << "\n  --- Add Medicines (enter 'done' for name to finish) ---" << endl;
        
        int medCount = 1;
        while (true) {
            cout << "\n  Medicine #" << medCount << ":" << endl;
            string medName = readString("  Medicine Name (or 'done')");
            if (medName == "done" || medName == "Done" || medName == "DONE") break;
            
            string dosage = readString("  Dosage (e.g. 500mg)");
            string frequency = readString("  Frequency (e.g. 2x/day)");
            string duration = readString("  Duration (e.g. 7 days)");
            string notes = readString("  Notes (optional)");
            
            Medicine med;
            med.name = medName;
            med.dosage = dosage;
            med.frequency = frequency;
            med.duration = duration;
            med.notes = notes;
            medicines.push_back(med);
            medCount++;
        }
        
        if (medicines.empty()) {
            printWarning("No medicines added. Prescription not created.");
            return;
        }
        
        string rxNotes = readString("Clinical Notes (optional)");
        
        Prescription& rx = hospital.addPrescription(appointmentId, patientId, doctorId, medicines, rxNotes);
        
        printSuccess("Prescription created successfully!");
        cout << "\n  Prescription ID: " << rx.getPrescriptionId() << endl;
        cout << "  Medicines:       " << rx.getMedicines().size() << " item(s)" << endl;
        
        cout << "\n  --- Prescribed Medicines ---" << endl;
        for (size_t i = 0; i < rx.getMedicines().size(); i++) {
            const auto& m = rx.getMedicines()[i];
            cout << "  " << (i+1) << ". " << m.name << " | " << m.dosage 
                 << " | " << m.frequency << " | " << m.duration;
            if (!m.notes.empty()) cout << " | " << m.notes;
            cout << endl;
        }
        
    } catch (const HospitalException& e) {
        printError(e.what());
    }
}

void viewAllPrescriptions(Hospital& hospital) {
    printHeader("PRESCRIPTION RECORDS");
    
    const auto& prescriptions = hospital.getAllPrescriptions();
    if (prescriptions.empty()) {
        printWarning("No prescriptions on record.");
        return;
    }
    
    for (const auto& rx : prescriptions) {
        printLine();
        cout << "  Prescription ID: " << rx.getPrescriptionId() << endl;
        cout << "  Appointment:     " << rx.getAppointmentId() << endl;
        cout << "  Patient:         " << rx.getPatientId() << endl;
        cout << "  Doctor:          " << rx.getDoctorId() << endl;
        cout << "  Date:            " << rx.getDate() << endl;
        
        if (!rx.getNotes().empty())
            cout << "  Notes:           " << rx.getNotes() << endl;
        
        cout << "  Medicines:" << endl;
        for (size_t i = 0; i < rx.getMedicines().size(); i++) {
            const auto& m = rx.getMedicines()[i];
            cout << "    " << (i+1) << ". " << m.name << " - " << m.dosage 
                 << " - " << m.frequency << " for " << m.duration;
            if (!m.notes.empty()) cout << " (" << m.notes << ")";
            cout << endl;
        }
    }
    
    printLine();
    cout << "  Total: " << prescriptions.size() << " prescription(s)" << endl;
}

void viewPrescriptionByAppointment(Hospital& hospital) {
    printHeader("VIEW PRESCRIPTION BY APPOINTMENT");
    
    string aptId = readString("Enter Appointment ID");
    
    vector<Prescription> results = hospital.getPrescriptionsByAppointment(aptId);
    
    if (results.empty()) {
        printWarning("No prescriptions found for appointment " + aptId);
        return;
    }
    
    for (const auto& rx : results) {
        printLine();
        cout << rx << endl;
    }
}

void prescriptionMenu(Hospital& hospital) {
    while (true) {
        printHeader("PRESCRIPTION MANAGEMENT");
        
        cout << "  1. Create New Prescription" << endl;
        cout << "  2. View All Prescriptions" << endl;
        cout << "  3. View Prescription by Appointment" << endl;
        cout << "  0. Back to Main Menu" << endl;
        cout << endl;
        
        try {
            int choice = readChoice("Enter choice", 0, 3);
            
            switch (choice) {
                case 1: createPrescription(hospital); break;
                case 2: viewAllPrescriptions(hospital); break;
                case 3: viewPrescriptionByAppointment(hospital); break;
                case 0: return;
            }
            
            pressEnterToContinue();
        } catch (const HospitalException& e) {
            printError(e.what());
            pressEnterToContinue();
        }
    }
}

// ========================= BILLING MANAGEMENT ================================

void generateBill(Hospital& hospital) {
    printHeader("GENERATE NEW BILL");
    
    // Show patients with appointments
    const auto& patients = hospital.getAllPatients();
    cout << "  Registered Patients:" << endl;
    for (const auto& [id, p] : patients) {
        cout << "    " << id << " - " << p.getName() << endl;
    }
    
    // Show appointments
    const auto& appointments = hospital.getAllAppointments();
    cout << "\n  Appointments:" << endl;
    for (const auto& apt : appointments) {
        cout << "    " << apt.getAppointmentId() << " - Patient: " << apt.getPatientId()
             << " | Doctor: " << apt.getDoctorId() << " [" << apt.getStatus() << "]" << endl;
    }
    cout << endl;
    
    try {
        string patientId = readString("Patient ID");
        string appointmentId = readString("Appointment ID");
        double medicineCost = readDouble("Medicine/Pharmacy Charges ($)");
        double roomCharges = readDouble("Room/Bed Charges ($)");
        double discount = readDouble("Discount Percentage (0-100)");
        
        Bill& bill = hospital.generateBill(patientId, appointmentId, medicineCost, roomCharges, discount);
        
        printSuccess("Bill generated successfully!");
        cout << "\n" << bill.printInvoice() << endl;
        
    } catch (const HospitalException& e) {
        printError(e.what());
    }
}

void viewAllBills(Hospital& hospital) {
    printHeader("BILLING RECORDS");
    
    const auto& bills = hospital.getAllBills();
    if (bills.empty()) {
        printWarning("No bills generated yet.");
        return;
    }
    
    cout << "  " << left << setw(8) << "Bill ID"
         << setw(10) << "Patient"
         << setw(10) << "Consult"
         << setw(10) << "Medicine"
         << setw(10) << "Room"
         << setw(10) << "Discount"
         << setw(12) << "Total"
         << setw(10) << "Status" << endl;
    printLine(80);
    
    for (const auto& bill : bills) {
        cout << "  " << left << setw(8) << bill.getBillId()
             << setw(10) << bill.getPatientId()
             << "$" << setw(9) << fixed << setprecision(2) << bill.getConsultationFee()
             << "$" << setw(9) << bill.getMedicineCost()
             << "$" << setw(9) << bill.getRoomCharges()
             << setw(10) << (to_string((int)bill.getDiscount()) + "%")
             << "$" << setw(11) << bill.getTotalAmount()
             << setw(10) << bill.getPaymentStatus() << endl;
    }
    
    printLine(80);
    cout << "  Total: " << bills.size() << " bill(s)" << endl;
}

void payBill(Hospital& hospital) {
    printHeader("PAY BILL");
    
    // Show unpaid bills
    const auto& bills = hospital.getAllBills();
    cout << "  Unpaid Bills:" << endl;
    for (const auto& bill : bills) {
        if (bill.getPaymentStatus() == "UNPAID" || bill.getPaymentStatus() == "PARTIAL") {
            cout << "    " << bill.getBillId() << " - Patient: " << bill.getPatientId()
                 << " - Total: $" << fixed << setprecision(2) << bill.getTotalAmount()
                 << " [" << bill.getPaymentStatus() << "]" << endl;
        }
    }
    cout << endl;
    
    string billId = readString("Enter Bill ID to mark as PAID");
    
    try {
        hospital.payBill(billId);
        printSuccess("Bill " + billId + " has been marked as PAID.");
    } catch (const HospitalException& e) {
        printError(e.what());
    }
}

void viewInvoice(Hospital& hospital) {
    printHeader("VIEW INVOICE");
    
    string billId = readString("Enter Bill ID");
    
    Bill* bill = hospital.findBill(billId);
    if (!bill) {
        printError("Bill '" + billId + "' not found.");
        return;
    }
    
    cout << "\n" << bill->printInvoice() << endl;
}

void billingMenu(Hospital& hospital) {
    while (true) {
        printHeader("BILLING & INVOICING");
        
        cout << "  1. Generate New Bill" << endl;
        cout << "  2. View All Bills" << endl;
        cout << "  3. Pay Bill" << endl;
        cout << "  4. View Invoice" << endl;
        cout << "  0. Back to Main Menu" << endl;
        cout << endl;
        
        try {
            int choice = readChoice("Enter choice", 0, 4);
            
            switch (choice) {
                case 1: generateBill(hospital); break;
                case 2: viewAllBills(hospital); break;
                case 3: payBill(hospital); break;
                case 4: viewInvoice(hospital); break;
                case 0: return;
            }
            
            pressEnterToContinue();
        } catch (const HospitalException& e) {
            printError(e.what());
            pressEnterToContinue();
        }
    }
}

// ========================= OOP DEMONSTRATION =================================

void demonstrateOOP(Hospital& hospital) {
    printHeader("OOP CONCEPTS DEMONSTRATION");
    
    cout << "  1. POLYMORPHISM (Virtual Dispatch)" << endl;
    cout << "     Calling display() and getRole() on Person* pointers:" << endl;
    printLine();
    hospital.displayAllPersonnel(cout);
    printLine();
    
    cout << "\n  2. OPERATOR OVERLOADING (operator<<)" << endl;
    cout << "     Using cout << on Patient and Doctor objects:" << endl;
    printLine();
    
    const auto& patients = hospital.getAllPatients();
    if (!patients.empty()) {
        cout << "  " << patients.begin()->second << endl;
    }
    
    const auto& doctors = hospital.getAllDoctors();
    if (!doctors.empty()) {
        cout << "  " << doctors.begin()->second << endl;
    }
    printLine();
    
    cout << "\n  3. EXCEPTION HANDLING" << endl;
    cout << "     Trying to access non-existent patient:" << endl;
    printLine();
    try {
        hospital.getPatient("INVALID_ID_999");
    } catch (const InvalidIdException& e) {
        cout << "  Caught InvalidIdException: " << e.what() << endl;
    }
    
    cout << "\n     Trying to create patient with invalid age:" << endl;
    try {
        hospital.addPatient("Test", 999, "Male", "1234567890", "Test", "O+", "2024-01-01");
    } catch (const InvalidInputException& e) {
        cout << "  Caught InvalidInputException: " << e.what() << endl;
    }
    printLine();
    
    cout << "\n  4. COMPOSITION" << endl;
    cout << "     Hospital OWNS all entities (composition). When Hospital is destroyed," << endl;
    cout << "     all patients, doctors, appointments, prescriptions, and bills are destroyed." << endl;
    cout << "     Patient OWNS its MedicalRecords. Prescription OWNS its Medicines." << endl;
    printLine();
    
    cout << "\n  5. AGGREGATION" << endl;
    cout << "     Appointment REFERENCES Patient and Doctor by ID (aggregation)." << endl;
    cout << "     They exist independently in the Hospital's maps." << endl;
    printLine();
    
    cout << "\n  6. STL CONTAINERS" << endl;
    cout << "     std::map<string, Patient>  -> O(log n) lookup by ID" << endl;
    cout << "     std::vector<Appointment>   -> Dynamic array of appointments" << endl;
    cout << "     std::sort, std::find_if    -> Algorithm operations" << endl;
    printLine();
    
    cout << "\n  7. FILE I/O" << endl;
    cout << "     All data persisted to pipe-delimited .txt files in data/" << endl;
    cout << "     Loaded on startup, saved after every mutation." << endl;
    printLine();
}

// ========================= MAIN MENU =========================================

int main() {
    Hospital hospital("Smart Hospital", "data");
    
    // Load persisted data
    try {
        hospital.loadAllData();
    } catch (const FileIOException& e) {
        // Data files may not exist yet — that's OK on first run
        cout << "  Note: " << e.what() << " (first run — starting fresh)" << endl;
    } catch (...) {
        // Silently continue on first run
    }
    
    while (true) {
        printHeader("SMART HOSPITAL MANAGEMENT SYSTEM");
        
        cout << "  =================== MAIN MENU ===================" << endl;
        cout << endl;
        cout << "  1.  Dashboard              (View KPIs & Activity)" << endl;
        cout << "  2.  Patient Management     (Register, Search, Records)" << endl;
        cout << "  3.  Doctor Management      (Register, View Directory)" << endl;
        cout << "  4.  Appointment Scheduling  (Book, Complete, Cancel)" << endl;
        cout << "  5.  Prescription Management (Create, View, Search)" << endl;
        cout << "  6.  Billing & Invoicing     (Generate, Pay, View)" << endl;
        cout << "  7.  OOP Concepts Demo       (Polymorphism, Exceptions)" << endl;
        cout << "  0.  Exit" << endl;
        cout << endl;
        cout << "  ==================================================" << endl;
        cout << endl;
        
        try {
            int choice = readChoice("Enter your choice", 0, 7);
            
            switch (choice) {
                case 1: 
                    displayDashboard(hospital);
                    pressEnterToContinue();
                    break;
                case 2: patientMenu(hospital); break;
                case 3: doctorMenu(hospital); break;
                case 4: appointmentMenu(hospital); break;
                case 5: prescriptionMenu(hospital); break;
                case 6: billingMenu(hospital); break;
                case 7:
                    demonstrateOOP(hospital);
                    pressEnterToContinue();
                    break;
                case 0:
                    cout << "\n  Saving all data..." << endl;
                    hospital.saveAllData();
                    printSuccess("Data saved successfully. Goodbye!");
                    cout << endl;
                    return 0;
            }
        } catch (const HospitalException& e) {
            printError(e.what());
            pressEnterToContinue();
        } catch (const exception& e) {
            printError(string("Unexpected error: ") + e.what());
            pressEnterToContinue();
        }
    }
    
    return 0;
}
