#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>

class Appointment {
private:
    std::string appointmentId;
    std::string patientId;
    std::string doctorId;
    std::string date;

public:
    Appointment();
    Appointment(const std::string& appointmentId, const std::string& patientId,
                const std::string& doctorId, const std::string& date);

    std::string getAppointmentId() const { return appointmentId; }
    std::string getPatientId() const { return patientId; }
    std::string getDoctorId() const { return doctorId; }
    std::string getDate() const { return date; }

    void setAppointmentId(const std::string& id) { appointmentId = id; }
    void setPatientId(const std::string& pId) { patientId = pId; }
    void setDoctorId(const std::string& dId) { doctorId = dId; }
    void setDate(const std::string& d) { date = d; }

    void display() const;
    std::string toFileString() const;
    static Appointment fromFileString(const std::string& line);
};

#endif // APPOINTMENT_H

