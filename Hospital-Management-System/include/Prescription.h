#pragma once
#include <string>
#include <vector>
#include <iostream>

struct Medicine {
    std::string name, dosage, frequency, duration, notes;
    std::string serialize() const;
    static Medicine deserialize(const std::string& data);
};

class Prescription {
private:
    std::string prescriptionId;
    std::string appointmentId;
    std::string patientId;
    std::string doctorId;
    std::vector<Medicine> medicines;
    std::string date;
    std::string notes;

public:
    Prescription();
    Prescription(const std::string& prescriptionId, const std::string& appointmentId, const std::string& patientId, const std::string& doctorId, const std::string& date);

    void addMedicine(const Medicine& m);
    void removeMedicine(int index);
    const std::vector<Medicine>& getMedicines() const;

    std::string getPrescriptionId() const;
    std::string getAppointmentId() const;
    std::string getPatientId() const;
    std::string getDoctorId() const;
    std::string getDate() const;
    std::string getNotes() const;
    void setNotes(const std::string& notes);

    std::string serialize() const;
    static Prescription deserialize(const std::string& line);
    friend std::ostream& operator<<(std::ostream& os, const Prescription& p);
};
