#include "../include/Patient.h"
#include "../include/Exceptions.h"
#include <sstream>

Patient::Patient(const std::string& patientId, const std::string& name, int age, const std::string& gender,
                 const std::string& contact, const std::string& address, const std::string& bloodGroup,
                 const std::string& admissionDate)
    : Person(name, age, gender, contact, address) {
    setPatientId(patientId);
    setBloodGroup(bloodGroup);
    setAdmissionDate(admissionDate);
    this->status = "OPD"; // default status
}

Patient::Patient() : Person() {}

void Patient::addMedicalRecord(const MedicalRecord& record) {
    medicalHistory.push_back(record);
}

const std::vector<MedicalRecord>& Patient::getMedicalHistory() const {
    return medicalHistory;
}

std::string Patient::getPatientId() const { return patientId; }
std::string Patient::getBloodGroup() const { return bloodGroup; }
std::string Patient::getAdmissionDate() const { return admissionDate; }
std::string Patient::getAssignedDoctorId() const { return assignedDoctorId; }
std::string Patient::getStatus() const { return status; }

void Patient::setPatientId(const std::string& patientId) {
    if (patientId.empty()) throw InvalidInputException("Patient ID cannot be empty.");
    this->patientId = patientId;
}

void Patient::setBloodGroup(const std::string& bloodGroup) {
    this->bloodGroup = bloodGroup;
}

void Patient::setAdmissionDate(const std::string& admissionDate) {
    this->admissionDate = admissionDate;
}

void Patient::setAssignedDoctorId(const std::string& assignedDoctorId) {
    this->assignedDoctorId = assignedDoctorId;
}

void Patient::setStatus(const std::string& status) {
    if (status != "ADMITTED" && status != "DISCHARGED" && status != "OPD") {
        throw InvalidInputException("Status must be ADMITTED, DISCHARGED, or OPD.");
    }
    this->status = status;
}

void Patient::display(std::ostream& os) const {
    os << "--- Patient Details ---\n"
       << "ID: " << patientId << "\n"
       << "Name: " << name << "\n"
       << "Age: " << age << "\n"
       << "Gender: " << gender << "\n"
       << "Contact: " << contact << "\n"
       << "Address: " << address << "\n"
       << "Blood Group: " << bloodGroup << "\n"
       << "Admission Date: " << admissionDate << "\n"
       << "Status: " << status << "\n"
       << "Assigned Doctor: " << (assignedDoctorId.empty() ? "None" : assignedDoctorId) << "\n";
}

std::string Patient::getRole() const { return "Patient"; }

std::string Patient::serialize() const {
    return patientId + "|" + name + "|" + std::to_string(age) + "|" + gender + "|" + contact + "|" +
           address + "|" + bloodGroup + "|" + admissionDate + "|" + status + "|" + assignedDoctorId;
}

Patient Patient::deserialize(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }
    while (tokens.size() < 10) {
        tokens.push_back("");
    }
    Patient p(tokens[0], tokens[1], std::stoi(tokens[2]), tokens[3], tokens[4], tokens[5], tokens[6], tokens[7]);
    p.setStatus(tokens[8].empty() ? "OPD" : tokens[8]);
    p.setAssignedDoctorId(tokens[9]);
    return p;
}
