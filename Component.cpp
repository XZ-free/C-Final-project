// Component.cpp
#include "Component.h"
#include <cmath>

// Set operating frequency for the component
void Component::set_frequency(double f) {
    frequency = f;
}

// Get current operating frequency
double Component::get_frequency() const {
    return frequency;
}

// Calculate impedance magnitude using complex absolute value
double Component::get_magnitude() const {
    return std::abs(get_impedance());
}

// Calculate phase angle using complex argument
double Component::get_phase() const {
    return std::arg(get_impedance());
}