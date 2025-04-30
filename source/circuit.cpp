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
    std::cout << "\nCalling Default Circuit Constructor\n" 
              << "Memory Location: " << this << std::endl; // call message
}


// Parameterized constructor 
Circuit::Circuit(std::complex<double> impedance)
    : impedance(impedance) 
    {
      std::cout << "\nCalling Component Constructor\nConstructing: " 
                << std::endl; // call message
    }


// Defining a base class destructor for cleanup, if needed
Circuit::~Circuit() 
{
  print_vspace(); // space for readability
  std::cout << "Calling Circuit Destructor:\n"
            << "Destroying: " << this << std::endl; // call message
  // no memory cleanup needed
}


std::vector<std::shared_ptr<Component>> Circuit::get_added_components() const
{
  return added_components; // return the added components vector
}


void Circuit::add_series(std::shared_ptr<Component>& component) 
{
  /* Parameters:
  i) component (smart pointer to an arbitrary component)
  Aims: (to add the new component in series with whole circuit)
  i) Modify the impedance of the circuit accordingly
  ii) Modify the connection matrix with the new component
  iii) Add the component to the components vector */
  
  std::cout << "\nCalling Series Adder Function: " 
            << "\nAdding Component: " << component->get_name() 
            << std::endl; // call message

  // First, use getter to get impedance of added component
  std::complex<double> component_impedance = component->get_impedance(); 

  // add it to the original impedance
  impedance += component_impedance; // modifies impedance

  /* Next we need to store the added component 
  We add it to the vector of components */
  added_components.push_back(component);

  // Resize the matrix to add a new row and column
  size_t new_size = connection_matrix.size() + 1;  // New size for the matrix

  // Resize existing rows to add a new column
  for (auto& row : connection_matrix) 
  {
    row.resize(new_size, 0);
  }

  // Add the new row filled with zeros
  connection_matrix.push_back(std::vector<int>(new_size, 0));

  // Define the index of the last row and column
  int column_row_index = new_size - 1;

  // Define a counter for the columns
  int j_counter = 0;
  
  while(j_counter < column_row_index) // whilst the counter is less than length of a column
  {
    connection_matrix[column_row_index][j_counter] = 1; // set the element to 1 for series
    j_counter += 1; // go to the next element in column
  }
  
  // Define a counter for the rows
  int i_counter = 0;
  
  while(i_counter < column_row_index) // whilst the counter is less than length of a row
  {
    connection_matrix[i_counter][column_row_index] = 1; // set the element to 1 for series
    i_counter += 1; // go to next element in the row
  }
  
  // add zero on the diagonal (as cant be connected to itself)
  connection_matrix[column_row_index][column_row_index] = 0; 
}


void Circuit::add_parallel(std::shared_ptr<Component>& component)
{
  /* Parameters:
  i) component (smart pointer to an arbitrary component)
  Aims: (to add the new component in parallel with whole circuit)
  i) Modify the impedance of the circuit accordingly
  ii) Modify the connection matrix with the new component
  iii) Add the component to the components vector */
  
  std::cout << "\nCalling Parallel Adder Function: " 
            << "\nAdding Component: " << component->get_name() 
            << std::endl; // call message

  // Define complex number 1
  std::complex<double> one(1.0, 0.0);
  
  // First use getter to get impedance of added component
  std::complex<double> component_impedance = component->get_impedance();

  // Add the reciprocals of the impedances
  std::complex<double> reciprocal = (one/impedance) + (one/component_impedance);

  // Then change the impedance using the reciprocal
  impedance = one/reciprocal;

  /* Next we need to store the added component
  We add it to the vector of components */
  added_components.push_back(component);

  // Resize the matrix to add a new row and column
  size_t new_size = connection_matrix.size() + 1;  // New size for the matrix
 
  // Resize existing rows to add a new column
  for (auto& row : connection_matrix)
  {
    row.resize(new_size, 0);
  }
 
  // Add the new row
  connection_matrix.push_back(std::vector<int>(new_size, 0));
 
  // Define the index of the last row and column
  int column_row_index = new_size - 1;

  // Define a counter for the columns
  int j_counter = 0;
  
  while(j_counter < column_row_index) // Fill column with 2s
  {
    connection_matrix[column_row_index][j_counter] = 2; // set the element to 2 for parallel
    j_counter += 1; // go to the next element in column
  }
  
  // Define a counter for the rows
  int i_counter = 0;
  
  while(i_counter < column_row_index) // Fill row with 2s
  {
    connection_matrix[i_counter][column_row_index] = 2; // set the element to 2 for parallel
    i_counter += 1; // go to next element in the row
  }
  
  // add zero on the diagonal (as cant be connected to itself)
  connection_matrix[column_row_index][column_row_index] = 0; 

}


void Circuit::calculate_impedance()
{
  /* Parameters:
  i) None (all information needed to calculate impedance is stored in 
     connection matrix and the vector of components)
  Aims: (to calculate the impedance of the whole circuit)
  i) Use the first row of the connection matrix
  ii) And the added components vector
  iii) To determine how each component was added
       and in what order
  iv) Add impedances step by step accordingly */

  impedance = std::complex<double>(0.0, 0.0); // make sure the impedance is initially zero

  if(added_components.empty())
  {
    return;
  }


  int index = 0; // create an index

  std::vector<int> first_row = connection_matrix[0]; // take the first row
  int length = first_row.size(); // find its length

  /* Add impedance of first component in series 
  (cant be in parallel if no other components)*/ 
  impedance += added_components[0]->get_impedance();

  while(index < length) // whilst in the first row
  {
    // get the component from the added components vector
    std::shared_ptr<Component> the_component = added_components[index]; 
    int connection_type = first_row[index]; // get how it was connected (0, 1, 2)

    if(connection_type == 2) // if added in parallel, update impedance
    {
      // Define complex number 1
      std::complex<double> one(1.0, 0.0);
      
      // First use getter to get impedance of added component
      std::complex<double> component_impedance = the_component->get_impedance();

      // Add the reciprocals of the impedances
      std::complex<double> reciprocal = (one/impedance) + (one/component_impedance);

      // Convert Reciprocal to impedance
      impedance = one/reciprocal;
    }

    else if(connection_type == 1) // if added in series, update impedance
    {
      // First, use getter to get impedance of added component
      std::complex<double> component_impedance = the_component->get_impedance(); 

      // add it to the original impedance
      impedance += component_impedance; // modifies impedance
    }

    else // no connection, dont modify impedance
    {
    }

    index += 1; // go to the next component
  }
}



void Circuit::remove_component(int component_index)
{
  std::cout << "Calling Component Remover: " 
            << "\nRemoving: " 
            << added_components[component_index - 1]->get_name() 
            << std::endl; // call message

  // erase component from the vector of components
  added_components.erase(added_components.begin() + (component_index - 1));
  
  // Remove the row from the connection matrix
  connection_matrix.erase(connection_matrix.begin() + (component_index - 1));
        
  // Remove the column
  for (auto& row : connection_matrix) 
  {
    // for each row, remove the index corresponding to the component
    row.erase(row.begin() + (component_index - 1));
  }
}


void Circuit::print_data() const
{
  /* Prints:
  i) the impedance magnitude
  ii) phase shift 
  iii) memory location 
  iv) connection matrix
  v) the vector of components */

  std::cout << "CIRCUIT DATA:\n"
            << " # Impedance Magnitude: " 
            <<  std::abs(impedance) << " Ohms" 
            << "\n # Phase Shift: " 
            << std::arg(impedance) << " radians"
            << "\n # Memory Location: " << this << std::endl;

  /* Print the connection matrix */
  std::cout << " # Connection Matrix:";

  for (const auto& row : connection_matrix) // for each row
  { 
    // Move to the next line after printing a row
    std::cout << "\n    "; 

    for (const auto& value : row) // for each element in the row
    {
      // Print the value and a space
      std::cout << value << " ";
    }
  }
  
  /* Print the vector of components */
  std::cout << "\n # Connection Matrix Components:\n";

  int counter = 1; // counter to label index of each component

  for (const std::shared_ptr<Component>& component : added_components) 
  {
    // print which component is which index
    std::cout << "   # Column/Row " << counter << " = " 
              << component->get_name() << std::endl; 

    counter += 1; // next index
  }
}




