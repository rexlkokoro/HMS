#pragma once
#include <string>
#include <iostream>

class Appointment {
private:
    std::string appointmentId;
    std::string patientId;
    std::string doctorId;
    std::string dateTime;
    std::string status;
    std::string reason;
    std::string notes;

public:
    Appointment();
    Appointment(const std::string& appointmentId, const std::string& patientId, const std::string& doctorId, const std::string& dateTime, const std::string& reason);

    std::string getAppointmentId() const;
    std::string getPatientId() const;
    std::string getDoctorId() const;
    std::string getDateTime() const;
    std::string getStatus() const;
    std::string getReason() const;
    std::string getNotes() const;
    void setNotes(const std::string& notes);

    void complete();
    void cancel();
    void reschedule(const std::string& newDateTime);

    std::string serialize() const;
    static Appointment deserialize(const std::string& line);

    bool operator<(const Appointment& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Appointment& appt);
};
