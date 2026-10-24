#include "../include/Appointment.h"
#include <iostream>
#include <sstream>

Appointment::Appointment()
    : appointmentId(""), patientId(""), doctorId(""), date(""), time(""), status("Scheduled") {}

Appointment::Appointment(const std::string& appointmentId, const std::string& patientId,
                         const std::string& doctorId, const std::string& date,
                         const std::string& time, const std::string& status)
    : appointmentId(appointmentId), patientId(patientId), doctorId(doctorId),
      date(date), time(time), status(status) {}

void Appointment::display() const {
    std::cout << "------------------------------------------\n";
    std::cout << "Appointment ID: " << appointmentId << "\n";
    std::cout << "Patient ID:     " << patientId << "\n";
    std::cout << "Doctor ID:      " << doctorId << "\n";
    std::cout << "Date:           " << date << "\n";
    std::cout << "Time:           " << time << "\n";
    std::cout << "Status:         " << status << "\n";
    std::cout << "------------------------------------------\n";
}

std::string Appointment::toFileString() const {
    return appointmentId + "|" + patientId + "|" + doctorId + "|" + date + "|" + time + "|" + status;
}

Appointment Appointment::fromFileString(const std::string& line) {
    std::stringstream ss(line);
    std::string apptId, pId, dId, dt, tm, st;

    std::getline(ss, apptId, '|');
    std::getline(ss, pId, '|');
    std::getline(ss, dId, '|');
    std::getline(ss, dt, '|');
    std::getline(ss, tm, '|');
    std::getline(ss, st, '|');

    return Appointment(apptId, pId, dId, dt, tm, st.empty() ? "Scheduled" : st);
}

