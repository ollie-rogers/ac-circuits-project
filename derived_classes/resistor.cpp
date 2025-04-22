#include "../headers/utils.h"
#include "resistor.h"

#include <iostream>
#include <string>


// Default constructor for Resistor, calls upon base Component default constructor
Resistor::Resistor() : Component(), resistance(0.0) 
{
  std::cout << "\nCalling Default Resistor Constructor\nConstructing: " 
            << get_name() << std::endl; // call message
}


/* Paramaterized contructor. Constructs resistor by calling base component constructor and
setting resistance. */ 
Resistor::Resistor(std::string r_name, double r_frequency, double resistance)
  : Component(r_name, r_frequency), resistance(resistance)
  {
    std::cout << "\nCalling Resistor Constructor\nConstructing: " 
              << get_name() << std::endl; // call message
  }


// Destructor for the resistor subclass
Resistor::~Resistor() 
{
  std::cout << "\nCalling Resistor Destructor:\nDestroying: "
            << get_name() << std::endl; // call message
  // no memory cleanup required here
}


// Overriding the setter for frequency
void Resistor::set_frequency(double new_frequency)
{
  /* Changes frequency to the input frequency */
  std::cout << "\nSetting new frequency: "
            << new_frequency << " Hz" << std::endl; // call message
  frequency = new_frequency; // setting new frequency
}


// Defining a getter for the resistance
double Resistor::get_resistance() const
{
  return resistance; // returns the resistance
}


/* Overriding all the getters */
double Resistor::get_frequency() const
{
  return frequency; // returns the frequency
}


std::complex<double> Resistor::get_impedance() const
{
  /* Impedance for a resistor is just its resistance.
  Function returns the resistance as a complex number */
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
  /* Prints the name, memory location, resistance,
  impedance magnitude, phase difference. */
  std::cout << " # Name: " << get_name() 
            << "\n # Memroy Location: " << this // this for memory location
            << "\n # Resistance: " << get_resistance() 
            << " Ohms\n" 
            << " # Impedance Magnitude: " << get_impedance_magnitude()
            << " Ohms\n # Phase Shift: "
            << get_phase_difference() << " radians"
            << std::endl; 
} 

