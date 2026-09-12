#pragma once
#include <exception>
#include <string>

class HospitalException : public std::exception {
protected:
    std::string message;
public:
    explicit HospitalException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class InvalidIdException : public HospitalException {
public:
    explicit InvalidIdException(const std::string& msg) : HospitalException("Invalid ID: " + msg) {}
};

class DoubleBookingException : public HospitalException {
public:
    explicit DoubleBookingException(const std::string& msg) : HospitalException("Double Booking: " + msg) {}
};

class InvalidInputException : public HospitalException {
public:
    explicit InvalidInputException(const std::string& msg) : HospitalException("Invalid Input: " + msg) {}
};

class FileIOException : public HospitalException {
public:
    explicit FileIOException(const std::string& msg) : HospitalException("File I/O Error: " + msg) {}
};

class AuthenticationException : public HospitalException {
public:
    explicit AuthenticationException(const std::string& msg) : HospitalException("Auth Error: " + msg) {}
};

class UnauthorizedException : public HospitalException {
public:
    explicit UnauthorizedException(const std::string& msg) : HospitalException("Unauthorized: " + msg) {}
};
