#include "../headers/utils.h"
#include "inductor.h"

#include <iostream>
#include <string>
#include <complex>


// Default constructor for Inductor, calls base Component default constructor
Inductor::Inductor() : Component(), inductance(0.0) 
{
  print_vspace(); // space for readability
  std::cout << "Calling Default Inductor Constructor\nConstructing: " 
            << get_name() << std::endl; // call message
}


/* Paramaterized contructor. Constructs capacitor by calling base component constructor and
setting inductance. */ 
Inductor::Inductor(std::string r_name, double r_frequency, double Inductance)
  : Component(r_name, r_frequency), inductance(inductance)
  {
    print_vspace(); // space for readability
    std::cout << "Calling Inductor Constructor\nConstructing: " 
              << get_name() << std::endl; // call message
  }


// Destructor for the Inductor subclass
Inductor::~Inductor() 
{
  print_vspace(); // space for readability
  std::cout << "Calling Inductor Destructor:\nDestroying: "
            << get_name() << std::endl; // call message
  // INSERT CLEANUP CODE HERE
}


// Overriding the setter for frequency
void Inductor::set_frequency(double new_frequency)
{
  print_vspace();
  std::cout << "Setting new frequency: " 
            << new_frequency << "Hz" << std::endl; // call message
  frequency = new_frequency;
}


// Defining a getter for the capacitance
double Inductor::get_inductance() const
{
  return inductance;
}


/* Overriding all the getters */
double Inductor::get_frequency() const
{
  return frequency;
}


std::complex<double> Inductor::get_impedance() const
{
  /* Using the standard formula for the impedance of an inductor
  Purely complex where complex part is omega*L */
  return std::complex<double>(0.0, frequency*inductance);
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
  print_vspace(); // space for readability
  std::cout << "COMPONENT DATA:\n"
            << "Name: " << get_name()
            << "\nMemroy Location: " << this
            << "\nInductance: " << get_inductance()
            << " H"<< std::endl; // call message
} 

