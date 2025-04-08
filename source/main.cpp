#include "../headers/utils.h"
#include "../headers/component.h"
#include "../headers/circuit.h"
#include "../derived_classes/resistor.h"
#include "../derived_classes/inductor.h"
#include "../derived_classes/capacitor.h"

#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <fstream>


std::string FILE_NAME = "input_components.csv";


void read_components(const std::string& filename, std::vector<std::unique_ptr<Component>>& components)
{  
  std::ifstream file(filename);
  std::string line;

  // Don't include the first line (skip it)
  std::getline(file, line);

  while (std::getline(file, line)) { // Read the rest of the lines

      std::stringstream ss(line);
      std::string type, name;
      double value, frequency;

      // Read values from the stream
      std::getline(ss, type, ',');
      std::getline(ss, name, ',');
      ss >> value;
      ss.ignore(1, ',');  // Skip the comma after value
      ss >> frequency;

      // Create the corresponding component object
      if (type == "Resistor") {
          components.push_back(std::make_unique<Resistor>(name, value, frequency));
      } else if (type == "Capacitor") {
          components.push_back(std::make_unique<Capacitor>(name, value, frequency));
      } else if (type == "Inductor") {
          components.push_back(std::make_unique<Inductor>(name, value, frequency));
      }
  }

}


void print_components_vector(const std::vector<std::unique_ptr<Component>>& components)
{
  for (const std::unique_ptr<Component>& component : components) {
    component->print_data();
  }
}


int main() {

  /* Create a vector of smart pointers to arbitrary components */
  std::vector<std::unique_ptr<Component>> components;

  read_components(FILE_NAME, components);
  print_components_vector(components);

  return 0;

}