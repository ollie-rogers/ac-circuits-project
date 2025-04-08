#include "component.h"
#include "utils.h"

#include <iostream>


// Default constructor definition
Component::Component() : name(std::string("Unknown")), frequency(double(0.0))
{
    print_vspace(); // space for readability
    std::cout << "Calling Default Component Constructor\nConstructing:" 
              << get_name() << std::endl; // call message
}


// Parameterized constructor 
Component::Component(std::string component_name, double component_frequency)
    : name(std::string(component_name)), frequency(component_frequency) 
    {
      print_vspace(); // space for readability
      std::cout << "Calling Component Constructor\nConstructing: " 
                << get_name() << std::endl; // call message
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


