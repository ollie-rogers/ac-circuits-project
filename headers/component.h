#ifndef COMPONENT_H
#define COMPONENT_H

#include <complex>


class Component {

protected:

  /* Note: do not need to define impedance, magnitude of impedance or phase differnce
  as data members, as these can be calculated on demand. */
  std::string name; // define name of component
  double frequency; // define frequency


public:

  Component(); // default constructor for base class

  Component(std::string component_name, double component_frequency); // parameterized constructor for base class

  virtual ~Component(); // desctructor for base class

  // defining purely vitrual setter for the frequency (const = 0 so pure virtual)
  virtual void set_frequency(double new_frequency) = 0; 

  // Default getter for name, this does not need to be overriden in derived classes
  std::string get_name() const;
  
  /* Defining purely vitrual getter for the frequency, impedance (complex), 
  the magnitude of the impedance (real) and the phase difference (real).*/
  virtual double get_frequency() const = 0; // use of const = 0 makes these pure virtual
  virtual std::complex<double> get_impedance() const = 0;
  virtual double get_impedance_magnitude() const = 0;
  virtual double get_phase_difference() const = 0;

  // defining a print data function as purely virtual, such that it must be overriden
  virtual void print_data() const = 0;
  
};


#endif // COMPONENT_H