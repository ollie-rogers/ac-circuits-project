#include "utils.h"
#include "resistor.h"

#include <iostream>
#include <string>


// Default constructor for Resistor, calls base Component default constructor
Resistor::Resistor() : Component(), resistance(0.0) 
{
  print_vspace(); // space for readability
  std::cout << "Calling Default Resistor Constructor\nConstructing: " 
            << get_name() << std::endl; // call message
}


/* Paramaterized contructor. Constructs resistor by calling base component constructor and
setting resistance. */ 
Resistor::Resistor(std::string r_name, double r_frequency, double resistance)
  : Component(r_name, r_frequency), resistance(resistance)
  {
    print_vspace(); // space for readability
    std::cout << "Calling Resistor Constructor\nConstructing: " 
              << get_name() << std::endl; // call message
  }


// Destructor for the resistor subclass
Resistor::~Resistor() 
{
  print_vspace(); // space for readability
  std::cout << "Calling Resistor Destructor:\nDestroying: "
            << get_name() << std::endl; // call message
  // INSERT CLEANUP CODE HERE
}


// Overriding the setter for frequency
void Resistor::set_frequency()
{
  print_vspace();
  std::cout << "Setting new frequency: " << std::endl;
  // RETURN TO THE SETTER
}


// Defining a getter for the resistance
double Resistor::get_resistance() const
{
  return resistance;
}


/* Overriding all the getters */
double Resistor::get_frequency() const
{
  return frequency;
}


std::complex<double> Resistor::get_impedance() const
{
  /* Impedance for a resistor is just its resistance.
  Function returns the resistance as a complex number*/
  return std::complex<double>(resistance, 0.0);
}


double Resistor::get_impedance_magnitude() const
{
  /* Magnitude of impedance for resistor is just the resistance.
  So function returns the resistance. */
  return resistance; 
}


double Resistor::get_phase_difference() const
{
  /* Impedance is non complex for resistor so always pahse difference of zero. */
  return 0.0;
}


void Resistor::print_data() const
{
  print_vspace(); // space for readability
  std::cout << "COMPONENT DATA:\n"
            << "Name: " << get_name()
            << "\nMemroy Location: " << this
            << "\nResistance: " << get_resistance()
            << " Ohms"<< std::endl; // call message
} 

