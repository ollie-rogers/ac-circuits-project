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
#include <memory>


std::string FILE_NAME = "input_components.csv"; // defining the input file name


void read_components(const std::string& filename, std::vector<std::unique_ptr<Component>>& components)
{  
  /* Parameters: 
   - components (vector of smart pointers to components)
   - filename (string) (kept abitrary so can use for different files)
  Aims:
   - reads file line by line
   - determines which component each line is
   - adds a smart pointer to that component to vector */
  
  std::ifstream file(filename); // opening the file
  std::string line; // defining a string which holds each line whilst reading

  while (std::getline(file, line)) { // Whilst lines remain

      std::stringstream ss(line); // make stringstream of current line
      std::string type, name; // deinfing variables to store type, name, frequency and value (e.g. resistance)
      double value, frequency;

      std::getline(ss, type, ','); // read up to first comma, this is type
      std::getline(ss, name, ','); // read up to nect comma, this is name
      ss >> value; // extract the numeric value, this is value
      ss.ignore(1, ',');  // Skip the comma after value
      ss >> frequency; // so all thats left is frequency

      // Create smart pointers and add to vector
      if (type == "Resistor") { 
          components.push_back(std::make_unique<Resistor>(name, value, frequency)); // add resistor
      } else if (type == "Capacitor") {
          components.push_back(std::make_unique<Capacitor>(name, value, frequency)); // add capacitor
      } else if (type == "Inductor") {
          components.push_back(std::make_unique<Inductor>(name, value, frequency)); // add inductor
      }
  }

}


void print_components_vector(const std::vector<std::unique_ptr<Component>>& components)
{
  /* Parameters:
   - vector of smart pointers to components (passed by ref) 
   Aims:
   - to iterate through the vector
   - use the print data functions to print each component*/
  for (const std::unique_ptr<Component>& component : components) {
    component->print_data();
  }
}


int main() {

  /* Create a vector of smart pointers to arbitrary components */
  std::vector<std::unique_ptr<Component>> components;

  read_components(FILE_NAME, components); // read components from file, add to vector
  print_components_vector(components); // print the contents of the vector

  return 0;

}