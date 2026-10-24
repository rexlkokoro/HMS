#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>

class Appointment {
private:
    std::string appointmentId;
    std::string patientId;
    std::string doctorId;
    std::string date;
    std::string time;
    std::string status; // e.g. "Scheduled", "Completed", "Cancelled"

public:
    Appointment();
    Appointment(const std::string& appointmentId, const std::string& patientId,
                const std::string& doctorId, const std::string& date,
                const std::string& time, const std::string& status = "Scheduled");

    // Getters
    std::string getAppointmentId() const { return appointmentId; }
    std::string getPatientId() const { return patientId; }
    std::string getDoctorId() const { return doctorId; }
    std::string getDate() const { return date; }
    std::string getTime() const { return time; }
    std::string getStatus() const { return status; }

    // Setters
    void setAppointmentId(const std::string& id) { appointmentId = id; }
    void setPatientId(const std::string& id) { patientId = id; }
    void setDoctorId(const std::string& id) { doctorId = id; }
    void setDate(const std::string& d) { date = d; }
    void setTime(const std::string& t) { time = t; }
    void setStatus(const std::string& s) { status = s; }

    void display() const;
    std::string toFileString() const;
    static Appointment fromFileString(const std::string& line);
};

#endif // APPOINTMENT_H

