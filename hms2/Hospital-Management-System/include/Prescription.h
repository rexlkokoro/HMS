#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <string>

class Prescription {
private:
    std::string prescriptionId;
    std::string patientId;
    std::string doctorId;
    std::string medicine;
    std::string dosage;
    std::string duration;

public:
    Prescription();
    Prescription(const std::string& prescriptionId, const std::string& patientId,
                 const std::string& doctorId, const std::string& medicine,
                 const std::string& dosage, const std::string& duration);

    // Getters
    std::string getPrescriptionId() const { return prescriptionId; }
    std::string getPatientId() const { return patientId; }
    std::string getDoctorId() const { return doctorId; }
    std::string getMedicine() const { return medicine; }
    std::string getDosage() const { return dosage; }
    std::string getDuration() const { return duration; }

    // Setters
    void setPrescriptionId(const std::string& id) { prescriptionId = id; }
    void setPatientId(const std::string& id) { patientId = id; }
    void setDoctorId(const std::string& id) { doctorId = id; }
    void setMedicine(const std::string& med) { medicine = med; }
    void setDosage(const std::string& dos) { dosage = dos; }
    void setDuration(const std::string& dur) { duration = dur; }

    void display() const;
    std::string toFileString() const;
    static Prescription fromFileString(const std::string& line);
};

#endif // PRESCRIPTION_H

