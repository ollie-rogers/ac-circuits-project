#ifndef INDUCTOR_H
#define INDUCTOR_H

#include "../headers/component.h"

#include <vector>
#include <memory>
#include <complex>


class Inductor : public Component {

private:

  double inductance;  // stores the inductance, class specific

public:

  Inductor(); // defining a default constructor for the subclass

  /* Defining paramaterized constructor for subclass. 
  Additionally contains inductance (differing from base class) */
  Inductor(std::string c_name, double c_frequency, double inductance); 

  ~Inductor() override; // overriding the base class destructor

  void set_frequency(double new_frequency) override; // override the setter for frequency

  double get_inductance() const; // define new getter for inductance

  /* Override all the base getters */
  double get_frequency() const override;
  std::complex<double> get_impedance() const override;
  double get_impedance_magnitude() const override;
  double get_phase_difference() const override;

  void print_data() const override; // override the print data function

};

#endif // INDUCTOR_H