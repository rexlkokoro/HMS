#include "../include/Prescription.h"
#include <iostream>
#include <sstream>

Prescription::Prescription()
    : prescriptionId(""), patientId(""), doctorId(""), medicine(""), dosage(""), duration("") {}

Prescription::Prescription(const std::string& prescriptionId, const std::string& patientId,
                           const std::string& doctorId, const std::string& medicine,
                           const std::string& dosage, const std::string& duration)
    : prescriptionId(prescriptionId), patientId(patientId), doctorId(doctorId),
      medicine(medicine), dosage(dosage), duration(duration) {}

void Prescription::display() const {
    std::cout << "------------------------------------------\n";
    std::cout << "Prescription ID: " << prescriptionId << "\n";
    std::cout << "Patient ID:      " << patientId << "\n";
    std::cout << "Doctor ID:       " << doctorId << "\n";
    std::cout << "Medicine:        " << medicine << "\n";
    std::cout << "Dosage:          " << dosage << "\n";
    std::cout << "Duration:        " << duration << "\n";
    std::cout << "------------------------------------------\n";
}

std::string Prescription::toFileString() const {
    return prescriptionId + "|" + patientId + "|" + doctorId + "|" + medicine + "|" + dosage + "|" + duration;
}

Prescription Prescription::fromFileString(const std::string& line) {
    std::stringstream ss(line);
    std::string rxId, pId, dId, med, dos, dur;

    std::getline(ss, rxId, '|');
    std::getline(ss, pId, '|');
    std::getline(ss, dId, '|');
    std::getline(ss, med, '|');
    std::getline(ss, dos, '|');
    std::getline(ss, dur, '|');

    return Prescription(rxId, pId, dId, med, dos, dur);
}

