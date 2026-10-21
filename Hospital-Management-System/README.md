# Smart Hospital Management System

A robust C++17 based backend for managing hospital operations including patient registration, doctor schedules, appointments, billing, and prescriptions. Features a built-in HTTP server exposing a RESTful JSON API.

## Features
- OOP Based Design (Inheritance, Polymorphism)
- REST API Server (httplib)
- Custom Exceptions and Validations
- File-based persistence
- Operator Overloading for Billing
- JSON Serialization

## File Structure
- `include/`: Header files
- `src/`: Implementation files
- `tests/`: Unit tests for all modules
- `data/`: Text files for data persistence
- `docs/`: Design docs and flowcharts
- `frontend/`: Static frontend files (to be mounted)

## Build Instructions
```bash
mkdir build && cd build
cmake ..
make
./HospitalManagement
```
(Requires C++17, CMake 3.15+)

## Usage Instructions
Once started, the server listens on `http://localhost:8080`.
Data is automatically loaded from `data/` and saved back upon changes.

## OOP Concepts Used
| Concept | Implementation |
|---------|----------------|
| Inheritance | Patient, Doctor inherit from Person |
| Polymorphism | Person::getRole() is virtual |
| Encapsulation | Private data members with getters/setters |
| Operator Overloading | `Bill operator+(const Bill&)` |
| Exception Handling | Custom exception classes |

## API Endpoints
| Method | Endpoint | Description |
|--------|----------|-------------|
| GET | `/api/stats` | Get hospital stats |
| GET | `/api/patients` | List all patients |
| POST | `/api/patients` | Add a patient |
| GET | `/api/doctors` | List all doctors |
| POST | `/api/doctors` | Add a doctor |
| GET | `/api/appointments` | List all appointments |
| POST | `/api/appointments` | Book appointment |
| DELETE | `/api/appointments/:id` | Cancel appointment |
| GET | `/api/billing` | List all bills |
| POST | `/api/billing` | Generate a bill |

(See main.cpp for full list)
