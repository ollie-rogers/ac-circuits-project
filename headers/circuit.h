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

  double impedance;  // stores the impedance of the whole circuit
  std::vector<std::unique_ptr<Component>> components; // smart pointer to vector of components

public:

  Circuit(); // defining a default constructor

  /* Defining paramaterized constructor, containing the impedance */
  Circuit(double impedance); 

  ~Circuit(); // defining destructor

};

#endif // CIRCUIT_H