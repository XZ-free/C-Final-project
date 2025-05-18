// Component.h
#ifndef COMPONENT_H
#define COMPONENT_H

#include <complex>
#include <string>

/**
 * @brief Abstract base class for electrical circuit components.
 * 
 * Provides interface for components to calculate impedance and frequency-related properties.
 * Derived classes must implement pure virtual methods.
 */
class Component {
protected:
    double frequency = 0.0;  ///< Operating frequency in Hz
public:
    virtual void set_frequency(double f);          ///< Set operating frequency
    virtual double get_frequency() const;          ///< Get current frequency
    virtual std::complex<double> get_impedance() const = 0;  ///< Calculate complex impedance
    virtual double get_magnitude() const;          ///< Get impedance magnitude
    virtual double get_phase() const;              ///< Get impedance phase angle
    virtual std::string get_name() const = 0;      ///< Get component name/type
    virtual ~Component() = default;                ///< Virtual destructor
};

#endif