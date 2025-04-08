#ifndef RESISTOR_H
#define RESISTOR_H

#include "utils.h"
#include "Component.h"

#include <vector>
#include <memory>


class Resistor : public Component {

private:

  double resistance;  // stores the resistance, class specific

public:

  Resistor(); // defining a default constructor for the subclass

  /* Defining paramaterized constructor for subclass. 
  Additionally contains resistance (differing from base class) */
  Resistor(std::string r_name, double r_frequency, double resistance); 

  void set_frequency() override; // override the setter for frequency

  double get_resistance() const; // define new getter for resistance

  /* Override all the base getters */
  double get_frequency() const override;
  std::complex<double> get_impedance() const override;
  double get_impedance_magnitude() const override;
  double get_phase_difference() const override;

  void print_data() const override; // override the print data function

};

#endif // RESISTOR_H