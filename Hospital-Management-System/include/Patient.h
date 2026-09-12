#pragma once
#include "Person.h"
#include "MedicalRecord.h"
#include <vector>
#include <string>

class Patient : public Person {
private:
    std::string patientId;
    std::string bloodGroup;
    std::string admissionDate;
    std::vector<MedicalRecord> medicalHistory;
    std::string assignedDoctorId;
    std::string status;

public:
    Patient(const std::string& patientId, const std::string& name, int age, const std::string& gender,
            const std::string& contact, const std::string& address, const std::string& bloodGroup,
            const std::string& admissionDate);
    Patient();

    void addMedicalRecord(const MedicalRecord& record);
    const std::vector<MedicalRecord>& getMedicalHistory() const;

    std::string getPatientId() const;
    std::string getBloodGroup() const;
    std::string getAdmissionDate() const;
    std::string getAssignedDoctorId() const;
    std::string getStatus() const;

    void setPatientId(const std::string& patientId);
    void setBloodGroup(const std::string& bloodGroup);
    void setAdmissionDate(const std::string& admissionDate);
    void setAssignedDoctorId(const std::string& assignedDoctorId);
    void setStatus(const std::string& status);

    void display(std::ostream& os) const override;
    std::string getRole() const override;
    std::string serialize() const override;
    static Patient deserialize(const std::string& line);
};
