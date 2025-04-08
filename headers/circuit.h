#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "component.h"
#include "utils.h"
#include "../derived_classes/resistor.h"
#include "../derived_classes/capacitor.h"
#include "../derived_classes/inductor.h"


#include <vector>
#include <memory>
#include <complex>


class Circuit {

protected:

  std::complex<double> impedance;  // stores the impedance of the whole circuit

public:

  Circuit(); // defining a default constructor

  /* Defining paramaterized constructor, containing the impedance */
  Circuit(std::complex<double> impedance); 

  ~Circuit(); // defining destructor

  /* Defining functions to add components in series or parellel */
  void add_series(const std::unique_ptr<Component>& component);
  void add_parallel(const std::unique_ptr<Component>& component);

  void print_data() const; // defining a print data function

};

#endif // CIRCUIT_H