#include "include/Hospital.h"
#include <iostream>

int main() {
    try {
        Hospital hospital;
        hospital.run();
    } catch (const std::exception& ex) {
        std::cerr << "An unexpected error occurred: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}

