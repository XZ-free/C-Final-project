// Resistor.h
#ifndef RESISTOR_H
#define RESISTOR_H

#include "Component.h"
#include <string>

/**
 * @brief Represents a resistor component with optional parasitic properties.
 * 
 * In ideal case, impedance is purely resistive. Non-ideal model can be extended
 * with additional parasitic inductor with inductance of 0.01nH.
 */
class Resistor : public Component {
    double resistance;  ///< Resistance value in ohms
    bool ideal;         ///< Flag for ideal/non-ideal model
    std::string label;  ///< Component label/identifier
    
public:
    Resistor(double r, bool ideal = true, const std::string& label = "");
    std::complex<double> get_impedance() const override;
    std::string get_name() const override;
};

#endif