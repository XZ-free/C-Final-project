// Circuit.h
#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "Component.h"
#include <vector>
#include <memory>
#include <string>

/**
 * @brief Represents a circuit composed of multiple components in series/parallel.
 * 
 * Can contain both basic components and nested sub-circuits. Provides visualizationand impedance 
 * calculation for complex circuit configurations.
 * add_component()
 * set_frequency(): Default value of 0, need to arrange value before actually using it
 * get_impedance(): recursively calculate the impedance of circuit
 * get_name(): Function inherited and overridden, user can choose if want to include connecting type
 * visualize(): recursively calculate and print the impedance of circuit. This function also outputs
 * the structure of the circuit.
 * print_details(): Simplified visualize, with less information.
 */
class Circuit : public Component {
public:
    enum ConnectionType { SERIES, PARALLEL };  ///< Connection type enumeration

    /// Circuit node containing component and optional label
    struct Node {
        std::shared_ptr<Component> component;  ///< Component/subsystem pointer
        std::string label;                     ///< Node label/identifier
    };

private:
    std::vector<Node> component_nodes;  ///< List of components/nodes in circuit
    ConnectionType connection_type;     ///< Connection configuration type

public:
    explicit Circuit(ConnectionType type = SERIES);
    void add_component(const std::shared_ptr<Component>& comp, const std::string& label = "");
    void set_frequency(double f) override;
    std::complex<double> get_impedance() const override;
    std::string get_name(bool include_type = false) const;
    std::string get_name() const override;
    void print_details(int indent = 0, bool include_type = false) const;
    const std::vector<Node>& get_nodes() const { return component_nodes; }
    void visualize(int indent = 0, bool include_type = false) const;
};

#endif