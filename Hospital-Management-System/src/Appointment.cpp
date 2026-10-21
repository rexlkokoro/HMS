#include "Appointment.h"
#include "Exceptions.h"
#include <sstream>

Appointment::Appointment() : status("SCHEDULED") {}

Appointment::Appointment(const std::string& appointmentId, const std::string& patientId, const std::string& doctorId, const std::string& dateTime, const std::string& reason)
    : appointmentId(appointmentId), patientId(patientId), doctorId(doctorId), dateTime(dateTime), status("SCHEDULED"), reason(reason) {}

std::string Appointment::getAppointmentId() const { return appointmentId; }
std::string Appointment::getPatientId() const { return patientId; }
std::string Appointment::getDoctorId() const { return doctorId; }
std::string Appointment::getDateTime() const { return dateTime; }
std::string Appointment::getStatus() const { return status; }
std::string Appointment::getReason() const { return reason; }
std::string Appointment::getNotes() const { return notes; }
void Appointment::setNotes(const std::string& notes) { this->notes = notes; }

void Appointment::complete() {
    if (status == "CANCELLED") throw InvalidInputException("Cannot complete a cancelled appointment.");
    status = "COMPLETED";
}

void Appointment::cancel() {
    if (status == "COMPLETED") throw InvalidInputException("Cannot cancel a completed appointment.");
    status = "CANCELLED";
}

void Appointment::reschedule(const std::string& newDateTime) {
    if (status != "SCHEDULED") throw InvalidInputException("Can only reschedule scheduled appointments.");
    dateTime = newDateTime;
}

std::string Appointment::serialize() const {
    return appointmentId + "|" + patientId + "|" + doctorId + "|" + dateTime + "|" + status + "|" + reason + "|" + notes;
}

Appointment Appointment::deserialize(const std::string& line) {
    std::stringstream ss(line);
    Appointment appt;
    std::getline(ss, appt.appointmentId, '|');
    std::getline(ss, appt.patientId, '|');
    std::getline(ss, appt.doctorId, '|');
    std::getline(ss, appt.dateTime, '|');
    std::getline(ss, appt.status, '|');
    std::getline(ss, appt.reason, '|');
    std::getline(ss, appt.notes, '|');
    return appt;
}

bool Appointment::operator<(const Appointment& other) const {
    return dateTime < other.dateTime;
}

std::ostream& operator<<(std::ostream& os, const Appointment& appt) {
    os << "Appointment: " << appt.appointmentId << " | Patient: " << appt.patientId << " | Doctor: " << appt.doctorId 
       << " | Date: " << appt.dateTime << " | Status: " << appt.status << " | Reason: " << appt.reason;
    return os;
}
