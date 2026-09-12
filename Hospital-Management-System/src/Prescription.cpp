#include "Prescription.h"
#include "Exceptions.h"
#include <sstream>

std::string Medicine::serialize() const {
    return name + ":" + dosage + ":" + frequency + ":" + duration + ":" + notes;
}

Medicine Medicine::deserialize(const std::string& data) {
    std::stringstream ss(data);
    Medicine m;
    std::getline(ss, m.name, ':');
    std::getline(ss, m.dosage, ':');
    std::getline(ss, m.frequency, ':');
    std::getline(ss, m.duration, ':');
    std::getline(ss, m.notes, ':');
    return m;
}

Prescription::Prescription() {}

Prescription::Prescription(const std::string& prescriptionId, const std::string& appointmentId, const std::string& patientId, const std::string& doctorId, const std::string& date)
    : prescriptionId(prescriptionId), appointmentId(appointmentId), patientId(patientId), doctorId(doctorId), date(date) {}

void Prescription::addMedicine(const Medicine& m) {
    medicines.push_back(m);
}

void Prescription::removeMedicine(int index) {
    if (index >= 0 && index < static_cast<int>(medicines.size())) {
        medicines.erase(medicines.begin() + index);
    } else {
        throw InvalidInputException("Invalid medicine index.");
    }
}

const std::vector<Medicine>& Prescription::getMedicines() const {
    return medicines;
}

std::string Prescription::getPrescriptionId() const { return prescriptionId; }
std::string Prescription::getAppointmentId() const { return appointmentId; }
std::string Prescription::getPatientId() const { return patientId; }
std::string Prescription::getDoctorId() const { return doctorId; }
std::string Prescription::getDate() const { return date; }
std::string Prescription::getNotes() const { return notes; }
void Prescription::setNotes(const std::string& n) { notes = n; }

std::string Prescription::serialize() const {
    std::string res = prescriptionId + "|" + appointmentId + "|" + patientId + "|" + doctorId + "|" + date + "|" + notes + "|";
    for (size_t i = 0; i < medicines.size(); ++i) {
        res += medicines[i].serialize();
        if (i < medicines.size() - 1) res += ";";
    }
    return res;
}

Prescription Prescription::deserialize(const std::string& line) {
    std::stringstream ss(line);
    Prescription p;
    std::getline(ss, p.prescriptionId, '|');
    std::getline(ss, p.appointmentId, '|');
    std::getline(ss, p.patientId, '|');
    std::getline(ss, p.doctorId, '|');
    std::getline(ss, p.date, '|');
    std::getline(ss, p.notes, '|');
    
    std::string meds;
    if (std::getline(ss, meds, '|')) {
        std::stringstream mss(meds);
        std::string medStr;
        while (std::getline(mss, medStr, ';')) {
            if(!medStr.empty()) p.addMedicine(Medicine::deserialize(medStr));
        }
    }
    return p;
}

std::ostream& operator<<(std::ostream& os, const Prescription& p) {
    os << "Prescription: " << p.prescriptionId << " | Appt: " << p.appointmentId << " | Medicines: " << p.medicines.size();
    return os;
}
