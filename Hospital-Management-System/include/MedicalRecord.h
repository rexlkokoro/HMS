#pragma once
#include <string>
#include <iostream>

class MedicalRecord {
private:
    std::string recordId;
    std::string patientId;
    std::string doctorId;
    std::string diagnosis;
    std::string treatment;
    std::string date;
    std::string notes;

public:
    MedicalRecord();
    MedicalRecord(const std::string& recordId, const std::string& patientId, const std::string& doctorId,
                  const std::string& diagnosis, const std::string& treatment, const std::string& date,
                  const std::string& notes);

    std::string getRecordId() const;
    std::string getPatientId() const;
    std::string getDoctorId() const;
    std::string getDiagnosis() const;
    std::string getTreatment() const;
    std::string getDate() const;
    std::string getNotes() const;

    void display(std::ostream& os) const;
    std::string serialize() const;
    static MedicalRecord deserialize(const std::string& data);
};
