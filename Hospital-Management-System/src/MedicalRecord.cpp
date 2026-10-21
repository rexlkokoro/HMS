#include "../include/MedicalRecord.h"
#include "../include/Exceptions.h"
#include <sstream>
#include <vector>

MedicalRecord::MedicalRecord() {}

MedicalRecord::MedicalRecord(const std::string& recordId, const std::string& patientId, const std::string& doctorId,
                             const std::string& diagnosis, const std::string& treatment, const std::string& date,
                             const std::string& notes)
    : recordId(recordId), patientId(patientId), doctorId(doctorId), diagnosis(diagnosis),
      treatment(treatment), date(date), notes(notes) {}

std::string MedicalRecord::getRecordId() const { return recordId; }
std::string MedicalRecord::getPatientId() const { return patientId; }
std::string MedicalRecord::getDoctorId() const { return doctorId; }
std::string MedicalRecord::getDiagnosis() const { return diagnosis; }
std::string MedicalRecord::getTreatment() const { return treatment; }
std::string MedicalRecord::getDate() const { return date; }
std::string MedicalRecord::getNotes() const { return notes; }

void MedicalRecord::display(std::ostream& os) const {
    os << "Record ID: " << recordId << "\n"
       << "Date: " << date << "\n"
       << "Doctor ID: " << doctorId << "\n"
       << "Diagnosis: " << diagnosis << "\n"
       << "Treatment: " << treatment << "\n"
       << "Notes: " << notes << "\n";
}

std::string MedicalRecord::serialize() const {
    return recordId + ";" + patientId + ";" + doctorId + ";" + diagnosis + ";" + treatment + ";" + date + ";" + notes;
}

MedicalRecord MedicalRecord::deserialize(const std::string& data) {
    std::vector<std::string> tokens;
    std::stringstream ss(data);
    std::string token;
    while (std::getline(ss, token, ';')) {
        tokens.push_back(token);
    }
    // Note: empty notes might cause fewer tokens if it's the last one, so we pad or check
    while (tokens.size() < 7) {
        tokens.push_back("");
    }
    return MedicalRecord(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], tokens[6]);
}
