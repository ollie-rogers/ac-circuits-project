#include "utils.h"
#include "component.h"
#include "circuit.h"
#include "resistor.h"
#include "capacitor.h"
#include "inductor.h"

#include <iostream>
#include <string>
#include <vector>
#include <complex>


int main() {

  Resistor test_resistor("Test Resistor", 4.0, 4.0);
  test_resistor.print_data();

  return 0;

}