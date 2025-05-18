// main.cpp
#include "Resistor.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Circuit.h"

#include <memory>
#include <iostream>
/**
 * @brief 
 *  Example main function for printing details of: single component, single node circuit and multiple node circuit.
 * This project is finished with help of generative AI. Include but not limited to aspect of: 
 * grammar check, debug, clarity improvement.
 */
int main() {
    //Example of creating basic components, set frequency and print the impedance
    std::cout << "---=== Single Component Test ===---" << std::endl;
    auto c0 = std::make_shared<Capacitor>(1.0, false, "C0");
    auto l0 = std::make_shared<Inductor>(1.5, true, "L0");
    c0->set_frequency(50);
    l0->set_frequency(50);
    std::cout << "Impedance amplitude of non-ideal capacitor " << abs(c0->get_impedance()) <<std::endl;
    std::cout << "Impedance amplitude of ideal inductor" << abs(l0->get_impedance()) << std::endl;


    std::cout << "====== Non-Ideal Labeled Component Test ======" << std::endl;

    // Example of creating labeled basic components（non-ideal model）
    auto c1 = std::make_shared<Capacitor>(1.0, false, "C1");
    auto l1 = std::make_shared<Inductor>(1.5, false, "L1");



    // Construct parallel circuit node（Node1），which includes parallely connected C1 and L1
    auto node1 = std::make_shared<Circuit>(Circuit::PARALLEL);
    node1->add_component(c1);
    node1->add_component(l1);

    // construct serial circuit "full_circuit"，which only include one subcircuit Node1
    auto full_circuit = std::make_shared<Circuit>(Circuit::SERIES);
    full_circuit->add_component(node1, "Node1");

    full_circuit->set_frequency(5); // Set frequency to 50Hz

    // Visualization by printing
    full_circuit->print_details();
    std::cout << "Visualization:" << std::endl;
    full_circuit->visualize();


    // Construct second serial current full_circuit1，which includes two identical sub circuit node1
    //with different label (user defined name)
    auto full_circuit1 = std::make_shared<Circuit>(Circuit::SERIES);
    full_circuit1->add_component(node1, "Node1");
    full_circuit1->add_component(node1, "Node2");

    full_circuit1->set_frequency(50); // Set frequency to 50Hz

    // Visualization by printing
    full_circuit1->print_details();
    std::cout << "Visualization1:" << std::endl;
    full_circuit1->visualize();

    return 0;
}
