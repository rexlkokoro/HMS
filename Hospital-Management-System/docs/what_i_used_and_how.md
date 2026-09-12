# 📚 What I Used & How — Smart Hospital Management System

> This document explains **every single technology, concept, library, design pattern, and tool** used in this project — what it is, why it was chosen, and exactly how it is applied in the code.

---

## 🔷 1. Programming Language — C++ (C++17 Standard)

**What it is:** A high-performance, statically-typed, compiled programming language supporting both procedural and object-oriented paradigms.

**Why used:** The assignment explicitly requires C++ with full OOP concepts (inheritance, polymorphism, encapsulation, abstraction, composition).

**How applied:**
- All backend logic is written in C++17
- `auto` keyword used for type inference in iterators
- Range-based `for` loops: `for (auto& p : patients)`
- Structured bindings: `auto& [key, val] = entry`
- `std::optional` for nullable return values
- `std::string_view` for efficient string passing
- `[[nodiscard]]` attribute on critical return values

---

## 🔷 2. Object-Oriented Programming (OOP) — Core Concepts

### 2.1 Abstraction
**What it is:** Hiding implementation details and exposing only essential interfaces via abstract classes.

**How applied:**
```cpp
// Person.h — Abstract base class
class Person {
protected:
    std::string name;
    int age;
    std::string gender;
    std::string contact;
    std::string address;
public:
    virtual void display() const = 0;      // Pure virtual — must override
    virtual std::string getRole() const = 0; // Pure virtual — must override
    virtual std::string serialize() const = 0;
    virtual ~Person() = default;           // Virtual destructor
};
```
> `Person` cannot be instantiated directly. Only `Patient`, `Doctor`, `Admin`, `Receptionist` can.

---

### 2.2 Inheritance
**What it is:** A class (child) derives properties and behavior from another class (parent).

**How applied:**

| Child Class | Parent Class(es) | What it inherits |
|---|---|---|
| `Patient` | `Person` | name, age, gender, contact, display() |
| `Doctor` | `Person`, `User` | Person attributes + authentication role |
| `Admin` | `User` | username, role, authenticate() |
| `Receptionist` | `User` | username, role, authenticate() |

```cpp
// Patient.h
class Patient : public Person {
private:
    std::string patientId;
    std::string bloodGroup;
    std::string admissionDate;
    std::vector<MedicalRecord> medicalHistory; // Composition
public:
    void display() const override;       // Override pure virtual
    std::string getRole() const override { return "Patient"; }
};
```

```cpp
// Doctor.h — Multiple inheritance
class Doctor : public Person, public User {
private:
    std::string doctorId;
    std::string department;
    double consultationFee;
public:
    void display() const override;
    std::string getRole() const override { return "Doctor"; }
};
```

---

### 2.3 Polymorphism (Runtime)
**What it is:** The same function call behaves differently based on the actual object type at runtime, resolved via virtual table (vtable).

**How applied:**
```cpp
// Hospital.h — polymorphic pointer vector
std::vector<Person*> allPersonnel;

// In Hospital.cpp
allPersonnel.push_back(new Patient(...));
allPersonnel.push_back(new Doctor(...));
allPersonnel.push_back(new Admin(...));

// Runtime dispatch — calls the correct override automatically
for (Person* p : allPersonnel) {
    p->display();    // Calls Patient::display(), Doctor::display(), etc.
    p->getRole();    // Returns "Patient", "Doctor", "Admin"
}
```

---

### 2.4 Encapsulation
**What it is:** Bundling data (attributes) and behavior (methods) inside a class with controlled access via access specifiers.

**How applied:**
```cpp
// Bill.h — all attributes private, validated setters
class Bill {
private:
    double consultationFee;
    double medicineCost;
    double roomCharges;
    double discount;    // percentage (0-100)
    double tax;
    double totalAmount;
    PaymentStatus status;

public:
    // Validated setter — throws if invalid
    void setDiscount(double d) {
        if (d < 0.0 || d > 100.0)
            throw InvalidInputException("Discount must be 0-100%");
        discount = d;
    }
    double getTotalAmount() const { return totalAmount; } // read-only getter
};
```

---

### 2.5 Composition
**What it is:** A "has-a" relationship where one class **owns** another. When the owner is destroyed, so is the owned object.

**How applied at 3 levels:**

```
Hospital ──owns──▶ Patient (Hospital destroyed → patients destroyed)
Patient  ──owns──▶ MedicalRecord (Patient destroyed → records destroyed)
Prescription ──owns──▶ Medicine (struct) instances
```

```cpp
// Hospital.h — Composition: Hospital owns all entities
class Hospital {
private:
    std::map<std::string, Patient>      patients;     // owned by Hospital
    std::map<std::string, Doctor>       doctors;      // owned by Hospital
    std::vector<Appointment>            appointments; // owned by Hospital
    std::vector<Prescription>           prescriptions;
    std::vector<Bill>                   bills;
};

// Patient.h — Composition: Patient owns its MedicalRecords
class Patient : public Person {
private:
    std::vector<MedicalRecord> medicalHistory; // Patient owns records
};

// Prescription.h — Composition: Prescription owns Medicine structs
struct Medicine {
    std::string name, dosage, frequency, duration, notes;
};
class Prescription {
private:
    std::vector<Medicine> medicines; // Prescription owns medicines
};
```

---

### 2.6 Aggregation
**What it is:** A "uses-a" relationship where one class references another but does **not** own it. Both can exist independently.

**How applied:**
```cpp
// Appointment.h — Aggregation: references Patient and Doctor by ID only
class Appointment {
private:
    std::string patientId;   // Reference by ID — not ownership
    std::string doctorId;    // Reference by ID — not ownership
    std::string dateTime;
    AppointmentStatus status;
    // Patient and Doctor objects live independently in Hospital's maps
};
```

---

### 2.7 Operator Overloading
**What it is:** Redefining the behavior of built-in C++ operators for user-defined types.

**How applied:**

```cpp
// Person.h — Stream insertion operator
std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << "[" << p.getRole() << "] " << p.name << " | Age: " << p.age;
    return os;
}

// Bill.h — operator+ to combine two bills (e.g. for a patient with multiple visits)
Bill operator+(const Bill& a, const Bill& b) {
    Bill combined;
    combined.setConsultationFee(a.consultationFee + b.consultationFee);
    combined.setMedicineCost(a.medicineCost + b.medicineCost);
    combined.calculate();
    return combined;
}

// Appointment.h — operator< for sorting by date/time
bool operator<(const Appointment& a, const Appointment& b) {
    return a.dateTime < b.dateTime;
}
```

---

## 🔷 3. Custom Exception Handling

**What it is:** Creating your own exception classes by inheriting from `std::exception` to represent domain-specific error conditions.

**Why used:** Standard exceptions (`std::runtime_error`) don't convey hospital-specific meaning. Custom exceptions allow precise error handling at API boundaries.

**How applied:**
```cpp
// Exceptions.h
class HospitalException : public std::exception {
protected:
    std::string message;
public:
    explicit HospitalException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class InvalidIdException    : public HospitalException { /* Patient/Doctor not found */ };
class DoubleBookingException: public HospitalException { /* Slot already taken */ };
class InvalidInputException : public HospitalException { /* Bad age, fee, etc. */ };
class FileIOException       : public HospitalException { /* Cannot read/write .txt */ };
class AuthenticationException: public HospitalException { /* Wrong password */ };
class UnauthorizedException : public HospitalException { /* Role not permitted */ };
```

```cpp
// Used in Appointment.cpp
void Hospital::bookAppointment(const std::string& patientId,
                                const std::string& doctorId,
                                const std::string& dateTime) {
    // Check for existing booking
    for (auto& appt : appointments) {
        if (appt.getDoctorId() == doctorId && appt.getDateTime() == dateTime
            && appt.getStatus() == SCHEDULED) {
            throw DoubleBookingException(
                "Dr. " + doctorId + " is already booked at " + dateTime
            );
        }
    }
}

// Caught in REST API handler (main.cpp)
try {
    hospital.bookAppointment(patientId, doctorId, dateTime);
    res.set_content(R"({"success":true})", "application/json");
} catch (const DoubleBookingException& e) {
    res.status = 409;
    res.set_content("{\"error\":\"" + std::string(e.what()) + "\"}", "application/json");
} catch (const InvalidIdException& e) {
    res.status = 404;
    res.set_content("{\"error\":\"" + std::string(e.what()) + "\"}", "application/json");
}
```

---

## 🔷 4. STL (Standard Template Library)

### 4.1 `std::map`
**What it is:** A sorted associative container (Red-Black Tree) giving O(log n) lookup by key.

**How applied:**
```cpp
std::map<std::string, Patient> patients;  // key = patientId
std::map<std::string, Doctor>  doctors;   // key = doctorId

// O(log n) lookup
Patient& p = patients.at("P001");  // throws std::out_of_range if missing
```

### 4.2 `std::vector`
**What it is:** A dynamic array with O(1) amortized push and O(n) search.

**How applied:**
```cpp
std::vector<Appointment>   appointments;
std::vector<Prescription>  prescriptions;
std::vector<MedicalRecord> medicalHistory; // inside Patient
std::vector<Medicine>      medicines;      // inside Prescription
```

### 4.3 `std::sort`
**How applied:**
```cpp
#include <algorithm>
// Sort appointments by date-time for display
std::sort(appointments.begin(), appointments.end());
// Uses overloaded operator< on Appointment
```

### 4.4 `std::find_if`
**How applied:**
```cpp
// Search patient by name (partial match)
auto it = std::find_if(patients.begin(), patients.end(),
    [&query](const auto& pair) {
        return pair.second.getName().find(query) != std::string::npos;
    });
```

### 4.5 `std::remove_if`
**How applied:**
```cpp
// Cancel and erase an appointment
appointments.erase(
    std::remove_if(appointments.begin(), appointments.end(),
        [&id](const Appointment& a) { return a.getId() == id; }),
    appointments.end()
);
```

---

## 🔷 5. File I/O — Pipe-Delimited `.txt` Persistence

**What it is:** Reading and writing data to plain text files using `std::fstream`.

**Why pipe `|` delimiter:** Commas conflict with address fields; pipes are unlikely in user data.

**How applied:**

```cpp
// Hospital.cpp — Saving patients to file
void Hospital::savePatientsToFile() {
    std::ofstream file("data/patients.txt");
    if (!file.is_open()) throw FileIOException("Cannot open data/patients.txt");
    for (auto& [id, patient] : patients) {
        file << patient.serialize() << "\n";  // calls Patient::serialize()
    }
}

// Patient.cpp — Serialization
std::string Patient::serialize() const {
    return patientId + "|" + name + "|" + std::to_string(age) + "|" +
           gender + "|" + contact + "|" + address + "|" +
           bloodGroup + "|" + admissionDate + "|" + statusToString();
}

// Patient.cpp — Deserialization (loading from file)
Patient Patient::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> fields;
    while (std::getline(ss, token, '|')) fields.push_back(token);
    Patient p;
    p.patientId     = fields[0];
    p.name          = fields[1];
    p.age           = std::stoi(fields[2]);
    // ... etc.
    return p;
}
```

---

## 🔷 6. Third-Party Libraries

### 6.1 `cpp-httplib` (`third_party/httplib.h`)
**What it is:** A single-header C++ HTTP/HTTPS server and client library.

**Why used:** Lets us embed a full REST API server inside the C++ program — no external web server (Apache/Nginx) needed.

**How applied:**
```cpp
// main.cpp
#include "third_party/httplib.h"

httplib::Server svr;

// Serve frontend files
svr.set_mount_point("/", "./frontend");

// REST API routes
svr.Get("/api/stats", [&](const httplib::Request&, httplib::Response& res) {
    auto stats = hospital.getStats();
    res.set_content(stats.toJson(), "application/json");
});

svr.Post("/api/patients", [&](const httplib::Request& req, httplib::Response& res) {
    // parse body, call hospital.registerPatient(), return JSON
});

svr.listen("0.0.0.0", 8080);  // Starts server on port 8080
```

### 6.2 `nlohmann/json` (`third_party/json.hpp`)
**What it is:** A single-header JSON parsing and serialization library for C++.

**Why used:** REST APIs exchange data in JSON format. This library makes parsing request bodies and building response objects trivial.

**How applied:**
```cpp
#include "third_party/json.hpp"
using json = nlohmann::json;

// Parsing incoming POST body
json body = json::parse(req.body);
std::string name    = body["name"];
int age             = body["age"];
std::string contact = body["contact"];

// Building JSON response
json response;
response["patientId"] = "P001";
response["name"]      = "Alex Johnson";
response["status"]    = "registered";
res.set_content(response.dump(), "application/json");
```

---

## 🔷 7. Role-Based Access Control (RBAC)

**What it is:** Different users (Admin, Doctor, Receptionist) have different permissions.

**How applied:**

| Role | Permissions |
|---|---|
| `ADMIN` | Add/remove doctors, view all reports, manage users |
| `DOCTOR` | View own patients, write prescriptions, complete appointments |
| `RECEPTIONIST` | Register patients, book appointments, generate bills |

```cpp
// User.h
enum class UserRole { ADMIN, DOCTOR, RECEPTIONIST };

// Enforced in API handlers
svr.Post("/api/doctors", [&](const httplib::Request& req, httplib::Response& res) {
    UserRole role = getSessionRole(req);
    if (role != UserRole::ADMIN)
        throw UnauthorizedException("Only admins can add doctors");
    // ... proceed
});
```

---

## 🔷 8. Design Patterns Used

### 8.1 Singleton Pattern — `Hospital` class
The `Hospital` object is the single central orchestrator. Only one instance exists in `main.cpp`.

### 8.2 Repository Pattern — Data Access
Each entity type is managed via map-based "repositories" inside `Hospital`, separating data access from business logic.

### 8.3 Factory-like ID Generation
```cpp
// Hospital.cpp
std::string Hospital::generatePatientId() {
    return "P" + std::to_string(++patientCounter);  // P1, P2, P3...
}
std::string Hospital::generateDoctorId() {
    return "D" + std::to_string(++doctorCounter);
}
```

---

## 🔷 9. Frontend Technologies

### 9.1 HTML5 (`frontend/index.html`)
- Single Page Application (SPA) structure
- Semantic tags: `<nav>`, `<main>`, `<section>`, `<article>`
- All 6 views embedded as `<div>` sections, toggled by JS

### 9.2 CSS3 (`frontend/style.css`)
- CSS Custom Properties (variables) for theming:
  ```css
  :root {
      --navy:  #1b2a4a;
      --teal:  #0e7c7b;
      --light: #f0f4f8;
  }
  ```
- CSS Grid + Flexbox for layout
- CSS transitions for smooth sidebar/modal animations
- Responsive breakpoints with `@media` queries
- Status badge coloring: `.badge-scheduled`, `.badge-completed`, `.badge-cancelled`

### 9.3 Vanilla JavaScript (`frontend/app.js`)
- **`fetch()` API** for all REST calls to `localhost:8080`
- **DOM manipulation** for dynamic table rendering
- **Event delegation** for dynamic button handlers
- **State management** with a simple `appState` object
- **Form validation** before submission
- Real-time search using `input` events + debounce

---

## 🔷 10. Build System

### CMake (`CMakeLists.txt`)
```cmake
cmake_minimum_required(VERSION 3.15)
project(HospitalManagementSystem)
set(CMAKE_CXX_STANDARD 17)

# Collect all source files
file(GLOB SOURCES "src/*.cpp")

add_executable(HospitalManagement main.cpp ${SOURCES})
target_include_directories(HospitalManagement PRIVATE include third_party)
```

**Build commands:**
```bash
mkdir build && cd build
cmake ..
make
./HospitalManagement
```

---

## 🔷 11. Test Files Strategy (`tests/`)

Each test file is standalone — compiled separately, uses `assert()` and `std::cout`.

| File | What it tests |
|---|---|
| `test_patients.cpp` | Register patient, duplicate ID, invalid age (negative, >120), search |
| `test_doctors.cpp` | Register doctor, invalid fee (negative), availability toggle |
| `test_appointments.cpp` | Book slot, `DoubleBookingException` for same slot, cancel, complete |
| `test_billing.cpp` | Bill calculation, discount logic, `operator+`, mark paid |
| `test_validation.cpp` | Phone format, name not empty, blood group valid, age range |
| `test_roles.cpp` | Admin-only actions blocked for Receptionist, Doctor cannot add doctors |

**Example:**
```cpp
// test_appointments.cpp
#include <cassert>
#include "../include/Hospital.h"
#include "../include/Exceptions.h"

void testDoubleBooking() {
    Hospital h;
    h.addDoctor(Doctor("D1","Dr. Smith","Cardiology", 150.0));
    h.addPatient(Patient("P1","John",30,"M"));
    h.bookAppointment("P1","D1","2024-01-15 10:00");

    bool caughtException = false;
    try {
        h.bookAppointment("P1","D1","2024-01-15 10:00"); // Same slot!
    } catch (const DoubleBookingException&) {
        caughtException = true;
    }
    assert(caughtException && "DoubleBookingException should be thrown");
    std::cout << "✅ testDoubleBooking PASSED\n";
}
```

---

## 🔷 12. Documentation Files (`docs/`)

### `class_diagram.txt`
ASCII art representation of the full class hierarchy:
```
Person (Abstract)
├── Patient
├── Doctor (also inherits User)
User
├── Admin
├── Receptionist
├── Doctor

Appointment ──aggregates──▶ Patient, Doctor (by ID)
Hospital ──composes──▶ Patient, Doctor, Appointment, Prescription, Bill
Prescription ──composes──▶ Medicine (struct)
Patient ──composes──▶ MedicalRecord
```

### `flowchart.txt`
ASCII flowcharts for:
- Patient Registration Flow
- Appointment Booking Flow (with double-booking check)
- Bill Generation Flow

### `docs/README.md`
Module-level documentation explaining each class's responsibility.

---

## 📊 Complete Technology Summary Table

| Category | Technology/Concept | Applied In |
|---|---|---|
| Language | C++17 | All `.cpp`/`.h` files |
| OOP: Abstraction | Abstract class `Person` | `Person.h` |
| OOP: Inheritance | Patient, Doctor, Admin, Receptionist | All entity `.h` files |
| OOP: Polymorphism | `Person*` vector, virtual methods | `Hospital.h`, `main.cpp` |
| OOP: Encapsulation | Private attrs + validated setters | All entity classes |
| OOP: Composition | Hospital→Patient, Patient→MedicalRecord | `Hospital.h`, `Patient.h` |
| OOP: Aggregation | Appointment→Patient/Doctor by ID | `Appointment.h` |
| OOP: Operator Overload | `<<`, `+`, `<` | `Person.h`, `Bill.h`, `Appointment.h` |
| Exception Handling | 6-tier custom exception hierarchy | `Exceptions.h`, all `src/` |
| STL | `map`, `vector`, `sort`, `find_if`, `remove_if` | `Hospital.cpp`, `src/` |
| File I/O | Pipe-delimited `.txt` serialize/deserialize | `Hospital.cpp`, all entity `.cpp` |
| HTTP Server | `cpp-httplib` (single-header) | `main.cpp`, `third_party/httplib.h` |
| JSON | `nlohmann/json` (single-header) | `main.cpp`, `third_party/json.hpp` |
| RBAC | `UserRole` enum, session-based | `User.h`, `main.cpp` |
| Design Patterns | Singleton, Repository, Factory ID | `Hospital.h`, `main.cpp` |
| Frontend | HTML5, CSS3 (Grid/Flex), Vanilla JS | `frontend/` |
| API | REST (GET/POST/DELETE) over HTTP | `main.cpp` |
| Build System | CMake (C++17) | `CMakeLists.txt` |
| Testing | `assert()` based unit tests | `tests/` |
| Documentation | ASCII diagrams, Markdown | `docs/` |
