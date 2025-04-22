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

  /* Defining "connection matrix" to store the connection of each component
   - Each row and column represent a component (same index)
   - 0 means not connected
   - 1 means connected in series
   - 2 means connected in parallel 
     - good sense check is diagonal always zero (cannot be connected to itself) 
   - From this, circuits can be easily reproduced */
  std::vector<std::vector<int>> connection_matrix; 

  /* However, we also need to know what each row and column is
  So we need a vector of the added components */
  std::vector<std::shared_ptr<Component>> added_components;

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

  /* Defining function to calculate the impedance from the connection matrix */
  void calculate_impedance_from_connection_matrix();

  /* Defining a function to remove a component, modify the connection
  matrix accordingly and recalculate the impedance */
  void remove_component(int component_index);

  void print_data() const; // defining a print data function

};

#endif // CIRCUIT_H