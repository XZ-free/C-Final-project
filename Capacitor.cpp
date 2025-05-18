// Capacitor.cpp
#include "Capacitor.h"
#include <cmath>
#include <limits>

const double PI = 3.14159265358979323846;  ///< Pi constant for calculations

// Constructor implementation
Capacitor::Capacitor(double capacitance_val, bool is_ideal, const std::string& label_name)
    : capacitance(capacitance_val), ideal(is_ideal), label(label_name) {}

// Calculate impedance (negative imaginary for ideal, plus ESR for non-ideal)
std::complex<double> Capacitor::get_impedance() const {
    if (frequency == 0.0) return {INFINITY, INFINITY};  // DC open circuit
    std::complex<double> impedance = {0, -1.0 / (2 * PI * frequency * capacitance)};
    return ideal ? impedance : impedance + std::complex<double>{0.1 * capacitance, 0};
}

// Generate component name with label and model type
std::string Capacitor::get_name() const {
    return label + " (" + (ideal ? "Capacitor" : "Capacitor+ESR") + ")";
}