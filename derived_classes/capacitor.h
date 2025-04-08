#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "../headers/component.h"

#include <vector>
#include <memory>
#include <complex>


class Capacitor : public Component {

private:

  double capacitance;  // stores the capacitance, class specific

public:

  Capacitor(); // defining a default constructor for the subclass

  /* Defining paramaterized constructor for subclass. 
  Additionally contains capacitance (differing from base class) */
  Capacitor(std::string c_name, double c_frequency, double capacitance); 

  ~Capacitor() override; // overriding the base class destructor

  void set_frequency(double new_frequency) override; // override the setter for frequency

  double get_capacitance() const; // define new getter for capacitance

  /* Override all the base getters */
  double get_frequency() const override;
  std::complex<double> get_impedance() const override;
  double get_impedance_magnitude() const override;
  double get_phase_difference() const override;

  void print_data() const override; // override the print data function

};

#endif // CAPACITOR_H