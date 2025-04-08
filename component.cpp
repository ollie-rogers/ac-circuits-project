#ifndef COMPONENT_H
#define COMPONENT_H

#include <complex>


class Component {

private:

  double frequency; // define the frequency as private

  
public:

  // defining purely vitrual setter for the frequency
  virtual void set_frequency(); 
  
  /* Defining purely vitrual getter for the frequency, impedance (complex), 
  the magnitude of the impedance (real) and the phase difference (real).*/
  virtual double getFrequency() const = 0; // use of const = 0 makes these pure virtual
  virtual std::complex<double> getImpedance() const = 0;
  virtual double getMagnitude() const = 0;
  virtual double getPhaseDifference() const = 0;
  
};


#endif // COMPONENT_H