#include "../headers/utils.h"
#include "inductor.h"

#include <iostream>
#include <string>
#include <complex>


// Default constructor for Inductor, calls upon base Component default constructor
Inductor::Inductor() : Component(), inductance(0.0) 
{
  std::cout << "\nCalling Default Inductor Constructor\nConstructing: " 
            << get_name() << std::endl; // call message
}


/* Paramaterized contructor. Constructs capacitor by calling base component 
constructor and setting inductance. */ 
Inductor::Inductor(std::string r_name, double r_frequency, double inductance)
  : Component(r_name, r_frequency), inductance(inductance)
  {
    std::cout << "\nCalling Inductor Constructor\nConstructing: " 
              << get_name() << std::endl; // call message
  }


// Destructor for the Inductor subclass
Inductor::~Inductor() 
{
  std::cout << "\nCalling Inductor Destructor:\nDestroying: "
            << get_name() << std::endl; // call message
  // no memory cleanup required
}


// Overriding the setter for frequency
void Inductor::set_frequency(double new_frequency)
{
  /* Changes frequency to the input frequency */
  std::cout << "\nSetting new frequency: " 
            << new_frequency << "Hz" << std::endl; // call message
  frequency = new_frequency; // setting new frequency
}


// Defining a getter for the capacitance
double Inductor::get_inductance() const
{
  return inductance; // returns the inductance
}


/* Overriding all the getters */
double Inductor::get_frequency() const
{
  return frequency; // returns the frequency
}


std::complex<double> Inductor::get_impedance() const
{
  /* Using the standard formula for the impedance of an inductor
  Purely complex where complex part is omega*L */
  return std::complex<double>(0.0, 2*PI*frequency*inductance);
}


double Inductor::get_impedance_magnitude() const
{
  /* Use the complex impedance to find the magnitude */
  std::complex<double> impedance = get_impedance();

  return std::abs(impedance); // returns the magnitude of complex impedance
}


double Inductor::get_phase_difference() const
{
  /* Use the complex impedance to find the phase difference */
  std::complex<double> impedance = get_impedance();

  return std::arg(impedance); // return the argument of complex impedance
}


void Inductor::print_data() const
{
  /* Prints the name, memory location, inductance,
  impedance magnitude, phase difference. */
  std::cout << " # Name: " << get_name()
            << "\n # Memroy Location: " << this
            << "\n # Inductance: " << get_inductance()
            << " H\n"
            << " # Impedance Magnitude: " << get_impedance_magnitude()
            << " Ohms\n # Phase Shift: "
            << get_phase_difference() << " radians"
            << std::endl; // call message
} 

