cmake_minimum_required(VERSION 3.15)
project(HospitalManagementSystem LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all source files
file(GLOB SOURCES "src/*.cpp")

# Main executable
add_executable(HospitalManagement main.cpp ${SOURCES})
target_include_directories(HospitalManagement PRIVATE include)

# Threads for future extensibility
find_package(Threads REQUIRED)
target_link_libraries(HospitalManagement Threads::Threads)
