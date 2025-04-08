#include "headers/utils.h"
#include "headers/component.h"
#include "headers/circuit.h"
#include "derived_classes/resistor.h"
#include "derived_classes/inductor.h"
#include "derived_classes/capacitor.h"

#include <iostream>
#include <string>
#include <vector>
#include <complex>


int main() {

  Resistor test_resistor("Test Resistor", 4.0, 4.0);
  test_resistor.print_data();

  return 0;

}