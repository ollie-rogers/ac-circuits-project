#include "utils.h"
#include "resistor.h"

#include <iostream>
#include <string>


// Default constructor for Resistor, calls base Component default constructor
Resistor::Resistor() : Component(), resistance(0.0) 
{
  print_vspace(); // space for readability
  std::cout << "Calling Default Resistor Constructor\nConstructing: " 
            << get_name() << "with resistance " 
            << get_resistance() << " Ohms"  << std::endl; // call message
}


/* Paramaterized contructor. Constructs resistor by calling base component constructor and
setting resistance. */ 
Resistor::Resistor(std::string r_name, double r_frequency, double resistance)
  : Component(r_name, r_frequency), resistance(resistance)
  {
    print_vspace(); // space for readability
    std::cout << "Calling Resistor Constructor\nConstructing: " 
              << get_name() << "with resistance " 
              << get_resistance() << " Ohms" << std::endl; // call message
  }


// Destructor for the resistor subclass
Resistor::~Resistor() 
{
  print_vspace(); // space for readability
  std::cout << "Calling Resistor Destructor:\nDestroying: "
            << get_name() << std::endl; // call message
  // INSERT CLEANUP CODE HERE
}


// Defining a getter for the resistance
double Resistor::get_resistance() const
{
  return resistance;
}



