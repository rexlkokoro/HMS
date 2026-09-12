# Module Documentation

## Core Classes

### Person (Base Class)
Abstract base class representing any human entity in the system. Holds common attributes like name, age, and contact.

### Patient, Doctor, Admin, Receptionist
Derived classes implementing `Person::getRole()`. Doctor and Patient have specific attributes (e.g. specialization, bloodGroup).

### Hospital
The main manager class. Holds vectors of pointers to all entities. 
Handles CRUD operations, data loading/saving, and core business logic (booking, billing).

### Exceptions
Defines `HospitalException` (base) and derived exceptions: `InvalidIdException`, `InvalidInputException`, `DoubleBookingException`.

## Build Instructions
1. Ensure CMake (3.15+) and a C++17 compiler are installed.
2. `mkdir build && cd build`
3. `cmake ..`
4. `make`
5. `./HospitalManagement`

## Testing
Compile tests in the `tests/` directory similarly (you can add them to CMakeLists if desired or compile manually with g++).

## API Endpoints Reference
See project README for full list of REST API endpoints.
