// Resistor.cpp
#include "Resistor.h"
const double PI = 3.14159265358979323846;

// Constructor implementation
Resistor::Resistor(double resistance_val, bool is_ideal, const std::string& label_name)
    : resistance(resistance_val), ideal(is_ideal), label(label_name) {}

// Calculate impedance (purely real for ideal resistor, 0.1nH parasitic inductance if not ideal)
std::complex<double> Resistor::get_impedance() const {
    std::complex<double> impedance = {resistance, 0};
    return ideal ? impedance : std::complex<double>{0, 2 * PI * frequency * 0.00000000001};;
}

// Generate component name in style of: label + model type
std::string Resistor::get_name() const {
    return label + " (" + (ideal ? "Resistor" : "Resistor+Parasitic") + ")";
}