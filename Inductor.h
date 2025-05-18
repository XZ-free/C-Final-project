// Inductor.h
#ifndef INDUCTOR_H
#define INDUCTOR_H

#include "Component.h"
#include <string>

/**
 * @brief Represents an inductor component with optional loss resistance.
 * 
 * Impedance is purely reactive in ideal case. Non-ideal model includes ESR.
 */
class Inductor : public Component {
    double inductance;  ///< Inductance value in Henries
    bool ideal;         ///< Flag for ideal/non-ideal model
    std::string label;  ///< Component label/identifier
    
public:
    Inductor(double l, bool ideal = true, const std::string& label = "");
    std::complex<double> get_impedance() const override;
    std::string get_name() const override;
};

#endif