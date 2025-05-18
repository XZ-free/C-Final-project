// Circuit.cpp
#include "Circuit.h"
#include <iostream>
#include <iomanip>
#include <cmath>

const double PI = 3.14159265358979323846;  ///< Pi constant for calculations

// Constructor initializing connection type
Circuit::Circuit(ConnectionType type) : connection_type(type) {}

// Add component to circuit with optional label
void Circuit::add_component(const std::shared_ptr<Component>& comp, const std::string& label) {
    component_nodes.push_back({comp, label});
}

// Set frequency for all components in circuit
void Circuit::set_frequency(double freq) {
    frequency = freq;
    for (auto& node : component_nodes) {
        node.component->set_frequency(freq);
    }
}

// Calculate total impedance based on connection type
std::complex<double> Circuit::get_impedance() const {
    if (component_nodes.empty())
        return {0, 0};

    if (connection_type == SERIES) {
        std::complex<double> total = 0;
        for (const auto& node : component_nodes) {
            total += node.component->get_impedance();
            }
        return total;
        } 
        else {
        std::complex<double> total_inv = 0;
        for (const auto& node : component_nodes) {
            total_inv += 1.0 / node.component->get_impedance();
        }
        return 1.0 / total_inv;
    }
}

// Get circuit type name
std::string Circuit::get_name() const {
    return get_name(false);
}

std::string Circuit::get_name(bool include_type) const {
    std::string name = "";
    for (const auto& node : component_nodes) {
        if (!node.label.empty()) {
            name += node.label + ", ";
        } else {
            name += node.component->get_name() + ", ";
        }
    }
    if (!name.empty()) name = name.substr(0, name.size() - 2); // remove trailing comma

    if (include_type) {
        name += " (" + std::string((connection_type == SERIES) ? "Series Circuit" : "Parallel Circuit") + ")";
    }
    return name;
}


// Print detailed circuit information with formatting
void Circuit::print_details(int indent, bool include_type) const {
    std::string spacer(indent, ' ');
    std::cout << spacer << get_name(include_type) << "\n";
    for (const auto& node : component_nodes) {
        std::cout << spacer << "  - " << node.component->get_name();
        if (!node.label.empty()) std::cout << " (" << node.label << ")";
        std::complex<double> z = node.component->get_impedance();
        std::cout << ": Z = (" << std::fixed << std::setprecision(2)
                  << z.real() << (z.imag() >= 0 ? "+" : "") << z.imag() << "j) ohms";

        auto sub_circuit = std::dynamic_pointer_cast<Circuit>(node.component);
        if (!sub_circuit || sub_circuit->get_nodes().size() == 1) {
            std::cout << ", |Z| = " << std::abs(z)
                      << ", phase = " << std::arg(z) * 180.0 / PI << " degrees";
        }
        std::cout << "\n";
    }
    std::cout << spacer << "  => Total |Z| = " << get_magnitude()
              << " ohms, phase = " << get_phase() * 180.0 / PI << " degrees\n\n";
}

// Visualize circuit structure using ASCII art
void Circuit::visualize(int indent, bool include_type) const {
    std::string spacer(indent, ' ');
    std::string conn_type_str = (connection_type == SERIES) ? "Series" : "Parallel";

    std::cout << spacer << conn_type_str << " Circuit";
    if (!component_nodes.empty()) std::cout << " (" << get_name(include_type) << ")";
    std::cout << ": |Z| = " << std::fixed << std::setprecision(2)
              << get_magnitude() << " ohms, phase = " << get_phase() * 180.0 / PI << " degrees\n";

    std::cout << spacer << "Contains nodes:" << std::endl;
    for (const auto& node : component_nodes) {
        std::cout << spacer << "- " << (node.label.empty() ? node.component->get_name() : node.label) << std::endl;
    }

    bool has_element = false;
    bool has_subcircuit = false;

    for (const auto& node : component_nodes) {
        auto sub_circuit = std::dynamic_pointer_cast<Circuit>(node.component);
        if (sub_circuit) {
            has_subcircuit = true;
        } else {
            has_element = true;
        }
    }

    if (has_element) {
        std::cout << spacer << "Primitive components:" << std::endl;
        for (const auto& node : component_nodes) {
            auto sub_circuit = std::dynamic_pointer_cast<Circuit>(node.component);
            if (!sub_circuit) {
                std::complex<double> z = node.component->get_impedance();
                std::cout << spacer << "  [" << node.component->get_name() << "] Z = ("
                          << std::fixed << std::setprecision(2)
                          << z.real() << (z.imag() >= 0 ? "+" : "") << z.imag() << "j) ohms" << std::endl;
            }
        }
    }

    if (has_subcircuit) {
        std::cout << spacer << "Subcircuits:" << std::endl;
        for (const auto& node : component_nodes) {
            auto sub_circuit = std::dynamic_pointer_cast<Circuit>(node.component);
            if (sub_circuit) {
                sub_circuit->visualize(indent + 4);
            }
        }
    }
}
