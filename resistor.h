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

  double get_resistance() const;

  void print_data() const override;

};

#endif // RESISTOR_H