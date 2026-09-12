#pragma once
#include "Person.h"
#include <string>

class Doctor : public Person {
private:
    std::string doctorId;
    std::string department;
    std::string specialization;
    std::string qualifications;
    double consultationFee;
    bool isAvailable;

public:
    Doctor(const std::string& doctorId, const std::string& name, int age, const std::string& gender,
           const std::string& contact, const std::string& address, const std::string& department,
           const std::string& specialization, const std::string& qualifications, double consultationFee);
    Doctor();

    std::string getDoctorId() const;
    std::string getDepartment() const;
    std::string getSpecialization() const;
    std::string getQualifications() const;
    double getConsultationFee() const;
    bool getIsAvailable() const;

    void setDoctorId(const std::string& doctorId);
    void setDepartment(const std::string& department);
    void setSpecialization(const std::string& specialization);
    void setQualifications(const std::string& qualifications);
    void setConsultationFee(double consultationFee);
    void setIsAvailable(bool isAvailable);

    void display(std::ostream& os) const override;
    std::string getRole() const override;
    std::string serialize() const override;
    static Doctor deserialize(const std::string& line);
};
