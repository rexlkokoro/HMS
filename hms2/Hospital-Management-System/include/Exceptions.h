#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class RecordNotFoundException : public std::runtime_error {
public:
    explicit RecordNotFoundException(const std::string& message = "Record not found.")
        : std::runtime_error(message) {}
};

class DuplicateRecordException : public std::runtime_error {
public:
    explicit DuplicateRecordException(const std::string& message = "Record already exists.")
        : std::runtime_error(message) {}
};

class InvalidInputException : public std::runtime_error {
public:
    explicit InvalidInputException(const std::string& message = "Invalid input provided.")
        : std::runtime_error(message) {}
};

class AuthenticationException : public std::runtime_error {
public:
    explicit AuthenticationException(const std::string& message = "Invalid username or password.")
        : std::runtime_error(message) {}
};

class UnauthorizedException : public std::runtime_error {
public:
    explicit UnauthorizedException(const std::string& message = "Permission denied for this operation.")
        : std::runtime_error(message) {}
};

#endif // EXCEPTIONS_H

