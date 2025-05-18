// Inductor.cpp
#include "Inductor.h"
#include <cmath>

const double PI = 3.14159265358979323846;  ///< Pi constant for calculations

// Constructor implementation
Inductor::Inductor(double l, bool ideal, const std::string& label)
    : inductance(l), ideal(ideal), label(label) {}

// Calculate impedance (positive imaginary for ideal, plus resistance for non-ideal)
std::complex<double> Inductor::get_impedance() const {
    std::complex<double> Zl = {0, 2 * PI * frequency * inductance};
    return ideal ? Zl : Zl + std::complex<double>{0.1 * inductance, 0};
}

// Generate component name with label and model type
std::string Inductor::get_name() const {
    return label + " (" + (ideal ? "Inductor" : "Inductor+Loss") + ")";
}