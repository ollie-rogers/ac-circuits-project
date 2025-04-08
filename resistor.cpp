#include "utils.h"
#include "resistor.h"

#include <iostream>
#include <string>


// Default constructor for Resistor, calls base Component default constructor
Resistor::Resistor() : Component(), resistance(0.0) 
{
  std::cout << "Default Resistor created with 0 resistance." << std::endl;
}

/* Paramaterized contructor. Constructs resistor by calling base component constructor and
setting resistance. */ 
Resistor::Resistor(std::string r_name, double r_frequency, double resistance)
  : Component(r_name, r_frequency), resistance(resistance)
  {
    std::cout << "Calling Resistor Constructor\nConstructing: " 
              << resistance << std::endl; // call message
  }



