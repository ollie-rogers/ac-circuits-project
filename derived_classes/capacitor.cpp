#include "../headers/utils.h"
#include "capacitor.h"

#include <iostream>
#include <string>
#include <complex>


// Default constructor for Capacitor, calls base Component default constructor
Capacitor::Capacitor() : Component(), capacitance(0.0) 
{
  std::cout << "\nCalling Default Capacitor Constructor\nConstructing: " 
            << get_name() << std::endl; // call message
}


/* Paramaterized contructor. Constructs capacitor by calling base component 
constructor and setting capacitance. */ 
Capacitor::Capacitor(std::string r_name, double r_frequency, double capacitance)
  : Component(r_name, r_frequency), capacitance(capacitance)
  {
    std::cout << "\nCalling Capacitor Constructor\nConstructing: " 
              << get_name() << std::endl; // call message
  }


// Destructor for the capacitor subclass
Capacitor::~Capacitor() 
{
  std::cout << "\nCalling Capacitor Destructor:\nDestroying: "
            << get_name() << std::endl; // call message
  // no memory cleanup required
}


// Overriding the setter for frequency
void Capacitor::set_frequency(double new_frequency)
{
  std::cout << "\nSetting new frequency: " 
            << new_frequency << "Hz" << std::endl; // call message
  frequency = new_frequency; // setting new frequency
}


// Defining a getter for the capacitance
double Capacitor::get_capacitance() const
{
  return capacitance; // return the capacitance
}


/* Overriding all the getters */
double Capacitor::get_frequency() const
{
  return frequency; // return the frequency
}


std::complex<double> Capacitor::get_impedance() const
{
  /* Using the standard formula for the impedance of a capacitor
  Purely complex where complex part is -1/(omega*f) */
  return std::complex<double>(0.0, -1/(capacitance*2*PI*frequency));
}


double Capacitor::get_impedance_magnitude() const
{
  /* Use the complex impedance to find the magnitude */
  std::complex<double> impedance = get_impedance();

  return std::abs(impedance); // returns the magnitude of complex impedance
}


double Capacitor::get_phase_difference() const
{
  /* Use the complex impedance to find the phase difference */
  std::complex<double> impedance = get_impedance();

  return std::arg(impedance); // return the argument of complex impedance
}


void Capacitor::print_data() const
{
  /* Prints the name, memory location, capacitance,
  impedance magnitude, phase difference. */
  std::cout << " # Name: " << get_name()
            << "\n # Memroy Location: " << this
            << "\n # Capacitance: " << get_capacitance()
            << " F\n"
            << " # Impedance Magnitude: " << get_impedance_magnitude()
            << " Ohms\n # Phase Shift: "
            << get_phase_difference() << " radians"
            << std::endl; // call message
} 

