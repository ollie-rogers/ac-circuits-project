#include "../headers/utils.h"
#include "../headers/component.h"
#include "../derived_classes/resistor.h"
#include "../derived_classes/capacitor.h"
#include "../derived_classes/inductor.h"
#include "../headers/circuit.h"

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>


// Default constructor definition
Circuit::Circuit() : impedance(std::complex<double> (0.0, 0.0))
{
    print_vspace(); // space for readability
    std::cout << "Calling Default Circuit Constructor\n" 
              << "Memory Location: " << this << std::endl; // call message
}


// Parameterized constructor 
Circuit::Circuit(std::complex<double> impedance)
    : impedance(impedance) 
    {
      print_vspace(); // space for readability
      std::cout << "Calling Component Constructor\nConstructing: " 
                << std::endl; // call message
    }


// Defining a base class destructor for cleanup, if needed
Circuit::~Circuit() 
{
  print_vspace(); // space for readability
  std::cout << "Calling Circuit Destructor:\n"
            << "Destroying: " << this << std::endl; // call message
  // INSERT CLEANUP CODE HERE IF NEEDED
}


void Circuit::add_series(std::shared_ptr<Component>& component) 
{
  /* Parameters:
   - component (smart pointer to an arbitrary component)
   Aims:
   - add the component in series with original circuit
   - modify the impedance of the circuit accordingly */
  
  print_vspace();
  std::cout << "Calling Series Adder Function: " 
            << "\nAdding Component: " << component->get_name() 
            << std::endl; // call message

  // First, use getter to get impedance of added component
  std::complex<double> component_impedance = component->get_impedance(); 

  // add it to the original impedance
  impedance += component_impedance; // modifies impedance

  /* Next we need to store how we added this component:
   - To do this, we need to first store the added component. */
  added_components.push_back(component);

  // Resize the matrix to add a new row and column
  size_t new_size = connection_matrix.size() + 1;  // New size for the matrix

  // Resize matrix: new row and new column
  connection_matrix.resize(new_size);
  for (auto& row : connection_matrix) {
      row.push_back(0);  // Add a new column with 0 (no connection yet)
  }

  // initialise counters for adding component connections
  int column_row_index = new_size - 1;
  int j_counter = 0;

  while(j_counter < column_row_index)
  {
    connection_matrix[column_row_index][j_counter] = 1;
    j_counter += 1;
  }

  int i_counter = 0;

  while(i_counter < column_row_index)
  {
    connection_matrix[i_counter][column_row_index] = 1;
    i_counter += 1;
  }

  // add zero on diagonal as cant be connected to itself
  connection_matrix[column_row_index][column_row_index] = 1; 

}


void Circuit::add_parallel(std::shared_ptr<Component>& component)
{
  /* Parameters:
   - component (smart pointer to an arbitrary component)
   Aims:
   - Add the component in parallel with original circuit
   - modify the impedance accordingly */
  
   print_vspace();
   std::cout << "Calling Parallel Adder Function: " 
             << "\nAdding Component: " << component->get_name() 
             << std::endl; // call message

  // Define complex number 1
  std::complex<double> one(1.0, 0.0);
  
  // First use getter to get impedance of added component
  std::complex<double> component_impedance = component->get_impedance();

  // Add the reciprocals of the impedances
  std::complex<double> reciprocal = (one/impedance) + (one/component_impedance);

  // Convert Reciprocal to impedance
  impedance = one/reciprocal;

  /* Next we need to store how we added this component:
   - To do this, we need to first store the added component. */
  added_components.push_back(component);

  // Resize the matrix to add a new row and column
  size_t new_size = connection_matrix.size() + 1;  // New size for the matrix

  // Resize matrix: new row and new column
  connection_matrix.resize(new_size);
  for (auto& row : connection_matrix) {
      row.push_back(0);  // Add a new column with 0 (no connection yet)
  }
  
  // initialise counters for adding component connections
  int column_row_index = new_size - 1;
  int j_counter = 0;
  
  while(j_counter < column_row_index)
  {
    connection_matrix[column_row_index][j_counter] = 1;
    j_counter += 1;
  }
  
  int i_counter = 0;
  
  while(i_counter < column_row_index)
  {
    connection_matrix[i_counter][column_row_index] = 1;
    i_counter += 1;
  }
  
  // add zero on diagonal as cant be connected to itself
  connection_matrix[column_row_index][column_row_index] = 1; 

}


void Circuit::print_data() const
{
  print_vspace();
  std::cout << "CIRCUIT DATA:\n"
            << "Impedance Magnitude: " 
            <<  std::abs(impedance) << " Ohms"
            << "\nPhase Shift: " 
            << std::arg(impedance) << " radians"
            << "\nMemory Location: " << this << std::endl;

}




