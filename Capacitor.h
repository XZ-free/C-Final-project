// Capacitor.h
#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "Component.h"
#include <string>

/**
 * @brief Represents a capacitor component with optional ESR (Equivalent Series Resistance).
 * 
 * Impedance is purely reactive in ideal case. Non-ideal model includes ESR.
 */
class Capacitor : public Component {
    double capacitance; ///< Capacitance value in Farads
    bool ideal;         ///< Flag for ideal/non-ideal model
    std::string label;  ///< Component label/identifier
    
public:
    Capacitor(double c, bool ideal = true, const std::string& label = "");
    std::complex<double> get_impedance() const override;
    std::string get_name() const override;
};

#endif