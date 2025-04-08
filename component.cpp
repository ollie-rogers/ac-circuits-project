#include "component.h"
#include "utils.h"

#include <iostream>


// Default constructor definition
Component::Component() : frequency(double(0.0))
    {
    print_dash();
    std::cout << "Calling Component Default Constructor\nCalling:" 
              << get_name() << std::endl; // call message
}


// Parameterized constructor 
Component::Component(std::string component_name, double component_frequency)
    : name(std::string(component_name)), frequency(component_frequency) {
    print_dash();
    std::cout << "Calling Parameterized Constructor\nCreating: " 
              << get_name() << std::endl; // call message
}


// Define the base class destructor for cleanup (if any)
Component::~Component() {
  std::cout << "Calling Component Destructor\n"
            << "Destroying: " << get_name() << std::endl;
  // Any cleanup code for the base class (like freeing resources)
}


std::string Component::get_name() const
{
  return name;
}

