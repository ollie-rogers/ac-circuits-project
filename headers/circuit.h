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
  std::vector<std::vector<int>> connection_matrix; // Empty matrix initially
  std::vector<std::shared_ptr<Component>> added_components;  // To store added components
  // const because we don't want to be editing the Components


public:

  Circuit(); // defining a default constructor

  /* Defining paramaterized constructor, containing the impedance */
  Circuit(std::complex<double> impedance); 

  ~Circuit(); // defining destructor

  // defining getter for the added components vector
  std::vector<std::shared_ptr<Component>> get_added_components() const;

  /* Defining functions to add components in series or parellel */
  void add_series(std::shared_ptr<Component>& component);
  void add_parallel(std::shared_ptr<Component>& component);

  void print_data() const; // defining a print data function

};

#endif // CIRCUIT_H