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
double FREQUENCY = 50.0; // frequency of AC circuit in Hz (change accordingly)


void error_message() {
    
  //prints an error message if an input is of the wrong form
  std::cin.clear();  // clear a failed state
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
  std::cout << "Invalid input. Please try again" << std::endl;
}


bool input_validity(std::string choice) {

  /* Checks whether the choice of whether to print the full list is of the right form.
  If of the right form returns true.
  If not of the right form, prints error message and returns false. */
  if (std::cin.fail() || std::cin.peek() != '\n') {
      error_message();
      return false;
  } else if (choice == "s" || choice == "p") {
      return true;
  } else {
      error_message();
      return false;
  }

  return false;
}


void read_components(const std::string& filename, std::vector<std::unique_ptr<Component>>& components)
{  
  /* Parameters: 
   - components (vector of smart pointers to arbitrary components)
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
      double value;

      std::getline(ss, type, ','); // read up to first comma, this is type
      std::getline(ss, name, ','); // read up to nect comma, this is name
      ss >> value; // extract the numeric value, this is value

      // Create smart pointers and add to vector
      if (type == "Resistor") { 
          components.push_back(std::make_unique<Resistor>(name, value, FREQUENCY)); // add resistor
      } else if (type == "Capacitor") {
          components.push_back(std::make_unique<Capacitor>(name, value, FREQUENCY)); // add capacitor
      } else if (type == "Inductor") {
          components.push_back(std::make_unique<Inductor>(name, value, FREQUENCY)); // add inductor
      }
  }

}


void print_components_vector(const std::vector<std::unique_ptr<Component>>& components)
{
  /* Parameters:
   - components (vector of smart pointers to arbitrary components)
   Aims:
   - to iterate through the vector
   - use the print data functions to print each component*/
  for (const std::unique_ptr<Component>& component : components) {
    component->print_data();
  }
}


void create_circuit(std::unique_ptr<Circuit>& circuit, const std::vector<std::unique_ptr<Component>>& components)
{
  /* Parameters:
   - circuit (smart pointer to a circuit object)
   - components (vector of smart pointers to arbitrary components) 
   Aims:
   - Iterate through the vector of components
   - For each component, ask the user to add in series or parallel 
   - Uses add_series and add_parallel functions to modify impedance od circuit */

  for (const std::unique_ptr<Component>& component : components) {

    print_vspace(); // space for readability

    component->print_data(); // prints data of component

    bool input_iterator = false; // creating a boolean to check if input valid
    std::string series_or_parallel; // creating a string to store user input of choice

    while(input_iterator == false)
    {
      print_vspace(); // for readability

      std::cout << "How would you like to add this component: Series / Parallel? (s/p)" 
      << std::endl; // asking for user input on how to add the component

      std::cin >> series_or_parallel; // assigns user input to variable

      input_iterator = input_validity(series_or_parallel); // checks to see if valid input

    } // breaks if valid input

    if(series_or_parallel == "s") // if user chose to add in series
    {
      circuit->add_series(component); // use add_series to modify circuit
    }
    else if(series_or_parallel == "p") // if user chose to add in parallel
    {
      circuit->add_parallel(component); // use add_parallel to modify circuit
    }

  }
}


int main() {

  /* Create a vector of smart pointers to arbitrary components */
  std::vector<std::unique_ptr<Component>> components;

  read_components(FILE_NAME, components); // read components from file, add to vector
  print_components_vector(components); // print the contents of the vector

  print_dash(); // space for readability
  std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();

  create_circuit(circuit, components);

  circuit->print_data();

  print_dash();

  return 0;

}