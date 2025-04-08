#include "../headers/utils.h"
#include "../headers/component.h"
#include "../derived_classes/resistor.h"
#include "../derived_classes/capacitor.h"
#include "../derived_classes/inductor.h"
#include "../headers/circuit.h"

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>


// Default constructor definition
Circuit::Circuit() : impedance(std::complex<double> (0.0, 0.0))
{
    print_vspace(); // space for readability
    std::cout << "Calling Default Circuit Constructor - Building Circuit" 
              <<  std::endl; // call message
}


// Parameterized constructor 
Circuit::Circuit(std::complex<double> impedance)
    : impedance(impedance) 
    {
      print_vspace(); // space for readability
      std::cout << "Calling Component Constructor\nConstructing: " 
                << std::endl; // call message
    }


// Defining a base class destructor for cleanup, if needed
Circuit::~Circuit() 
{
  print_vspace(); // space for readability
  std::cout << "Calling Circuit Destructor\n" << std::endl;
  // INSERT CLEANUP CODE HERE IF NEEDED
}


void Circuit::add_series(const std::unique_ptr<Component>& component) 
{
  /* Parameters:
   - component (smart pointer to an arbitrary component)
   Aims:
   - add the component in series with original circuit
   - modify the impedance of the circuit accordingly */

  // First, use getter to get impedance of added component
  std::complex<double> component_impedance = component->get_impedance(); 

  // add it to the original impedance
  impedance += component_impedance; // modifies impedance

}


void Circuit::add_parallel(const std::unique_ptr<Component>& component)
{
  /* Parameters:
   - component (smart pointer to an arbitrary component)
   Aims:
   - Add the component in parallel with original circuit
   - modify the impedance accordingly */

  // Define complex number 1
  std::complex<double> one(1.0, 0.0);
  
  // First use getter to get impedance of added component
  std::complex<double> component_impedance = component->get_impedance();

  // Add the reciprocals of the impedances
  std::complex<double> reciprocal = (one/impedance) + (one/component_impedance);

  // Convert Reciprocal to impedance
  impedance = one/reciprocal;

}


void Circuit::print_data() const
{
  std::cout << "Circuit Impedane: " 
            << impedance.real() << " + " 
            << impedance.imag() << "i" << std::endl;
}




