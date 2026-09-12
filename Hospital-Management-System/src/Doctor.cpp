#include "../include/Doctor.h"
#include "../include/Exceptions.h"
#include <sstream>
#include <vector>
#include <iomanip>

Doctor::Doctor(const std::string& doctorId, const std::string& name, int age, const std::string& gender,
               const std::string& contact, const std::string& address, const std::string& department,
               const std::string& specialization, const std::string& qualifications, double consultationFee)
    : Person(name, age, gender, contact, address), isAvailable(true) {
    setDoctorId(doctorId);
    setDepartment(department);
    setSpecialization(specialization);
    setQualifications(qualifications);
    setConsultationFee(consultationFee);
}

Doctor::Doctor() : Person(), consultationFee(0.0), isAvailable(true) {}

std::string Doctor::getDoctorId() const { return doctorId; }
std::string Doctor::getDepartment() const { return department; }
std::string Doctor::getSpecialization() const { return specialization; }
std::string Doctor::getQualifications() const { return qualifications; }
double Doctor::getConsultationFee() const { return consultationFee; }
bool Doctor::getIsAvailable() const { return isAvailable; }

void Doctor::setDoctorId(const std::string& doctorId) {
    if (doctorId.empty()) throw InvalidInputException("Doctor ID cannot be empty.");
    this->doctorId = doctorId;
}

void Doctor::setDepartment(const std::string& department) {
    this->department = department;
}

void Doctor::setSpecialization(const std::string& specialization) {
    this->specialization = specialization;
}

void Doctor::setQualifications(const std::string& qualifications) {
    this->qualifications = qualifications;
}

void Doctor::setConsultationFee(double consultationFee) {
    if (consultationFee < 0) throw InvalidInputException("Consultation fee cannot be negative.");
    this->consultationFee = consultationFee;
}

void Doctor::setIsAvailable(bool isAvailable) {
    this->isAvailable = isAvailable;
}

void Doctor::display(std::ostream& os) const {
    os << "--- Doctor Details ---\n"
       << "ID: " << doctorId << "\n"
       << "Name: " << name << "\n"
       << "Department: " << department << "\n"
       << "Specialization: " << specialization << "\n"
       << "Qualifications: " << qualifications << "\n"
       << "Fee: $" << std::fixed << std::setprecision(2) << consultationFee << "\n"
       << "Available: " << (isAvailable ? "Yes" : "No") << "\n";
}

std::string Doctor::getRole() const { return "Doctor"; }

std::string Doctor::serialize() const {
    std::stringstream ss;
    ss << doctorId << "|" << name << "|" << age << "|" << gender << "|" << contact << "|"
       << address << "|" << department << "|" << specialization << "|" << qualifications << "|"
       << std::fixed << std::setprecision(2) << consultationFee << "|" << (isAvailable ? "1" : "0");
    return ss.str();
}

Doctor Doctor::deserialize(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }
    while (tokens.size() < 11) {
        tokens.push_back("");
    }
    Doctor d(tokens[0], tokens[1], std::stoi(tokens[2]), tokens[3], tokens[4], tokens[5],
             tokens[6], tokens[7], tokens[8], std::stod(tokens[9]));
    d.setIsAvailable(tokens[10] == "1");
    return d;
}
