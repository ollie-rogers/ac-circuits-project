#include "../headers/utils.h"
#include "../headers/component.h"
#include "../derived_classes/resistor.h"
#include "../derived_classes/capacitor.h"
#include "../derived_classes/inductor.h"
#include "../headers/circuit.h"

#include <iostream>
#include <vector>
#include <complex>


// Default constructor definition
Circuit::Circuit() : impedance(double (0.0))
{
    print_vspace(); // space for readability
    std::cout << "Calling Default Circuit Constructor - Building Circuit" 
              <<  std::endl; // call message
}


// Parameterized constructor 
Circuit::Circuit(double impedance)
    : impedance(impedance) 
    {
      print_vspace(); // space for readability
      std::cout << "Calling Component Constructor\nConstructing: " 
                << std::endl; // call message
    }


// Defining a base class destructor for cleanup, if needed
Component::~Component() 
{
  print_vspace(); // space for readability
  std::cout << "Calling Component Destructor\n"
            << "Destroying: " << get_name() << std::endl;
  // INSERT CLEANUP CODE HERE IF NEEDED
}


// Define getter for the name of component, const as doesnt edit the value (for clarity)
std::string Component::get_name() const
{
  return name;
}


