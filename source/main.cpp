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


// void initial_statement()
// {
//   print_dash(); // for readability
//   std::cout << "\nPROGRAM FUNCTIONALITY:\n" 
//             << "\n - Reads in components from library\n" 
//             << " - Takes user input to construct an arbitrary circuit\n"
//             << std::endl; // print statement to explain the program
// }


void error_message() {
    
  //prints an error message if an input is of the wrong form
  std::cin.clear();  // clear a failed state
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
  std::cout << "Invalid input. Please try again" << std::endl;
}


void print_user_guide() 
{
  print_dash(); // to separate from above outputs

  std::cout << "Command\t\tDescription" << std::endl;
  std::cout << "---------------------------------------------" << std::endl;
  std::cout << "h\t\tDisplay user guide" << std::endl;
  std::cout << "c\t\tCreate a new circuit (Basic)" << std::endl;
  std::cout << "e\t\tEdit a circuit (Basic)" << std::endl;
  std::cout << "k\t\tOpen complex circuit editor" << std::endl;
  std::cout << "g\t\tDisplay component library" << std::endl;
  std::cout << "q\t\tDisplay circuit library" << std::endl;
  std::cout << "x\t\tExit the program" << std::endl;
}


void read_components(const std::string& filename, std::vector<std::shared_ptr<Component>>& components)
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

  print_dash(); // for readability
  std::cout << "\nGENERATING COMPONENTS:" << std::endl;

  while (std::getline(file, line)) { // Whilst lines remain

      std::stringstream ss(line); // make stringstream of current line
      std::string type, name; // deinfing variables to store type, name, frequency and value (e.g. resistance)
      double value;

      std::getline(ss, type, ','); // read up to first comma, this is type
      std::getline(ss, name, ','); // read up to nect comma, this is name
      ss >> value; // extract the numeric value, this is value

      // Create smart pointers and add to vector
      if (type == "Resistor") { 
          components.push_back(std::make_shared<Resistor>(name, FREQUENCY, value)); // add resistor
      } else if (type == "Capacitor") {
          components.push_back(std::make_shared<Capacitor>(name, FREQUENCY, value)); // add capacitor
      } else if (type == "Inductor") {
          components.push_back(std::make_shared<Inductor>(name, FREQUENCY, value)); // add inductor
      }
  }

}


void print_component_library(std::vector<std::shared_ptr<Component>>& components)
{
  /* Parameters:
   - components (vector of smart pointers to arbitrary components)
   Aims:
   - to iterate through the vector
   - use the print data functions to print each component*/

  print_dash(); // for readability
  std::cout << "\nCOMPONENT LIBRARY:" << std::endl;

  int counter = 1; // initialising variable to label number of component

  for (const std::shared_ptr<Component>& component : components) {
    std::cout << "\n" << counter << ") " 
              << std::endl; // label component number in library
    component->print_data(); // print data of component
    counter += 1;
  }

}


void print_circuit_library(const std::vector<std::unique_ptr<Circuit>>& circuits)
{
  /* Parameters:
   - components (vector of smart pointers to arbitrary components)
   Aims:
   - to iterate through the vector
   - use the print data functions to print each component*/

  print_dash(); // for readability
  std::cout << "\nCIRCUIT LIBRARY:" << std::endl;

  int counter = 1; // initialising variable to label number of component

  for (const std::unique_ptr<Circuit>& circuit : circuits) {
    std::cout << "\nCIRCUIT " << counter << ") " 
              << std::endl; // label component number in library
    circuit->print_data(); // print data of component
    counter += 1;
  }

}


int choose_component(std::vector<std::shared_ptr<Component>>& components)
{
  std::string component_choice_str;
  int component_choice_int = -995; 

  while(true)
  {
    std::cout << "\nEnter Component Number: " << std::endl;
    std::cin >> component_choice_str;

    try 
    { // try converting the input to an integer
      component_choice_int = std::stoi(component_choice_str);  
    } 
    catch (const std::invalid_argument& e) 
    {
      std::cout << "Invalid input. Please enter a valid number." << std::endl;
    }
          
    // store size of library vector as size to check if integer input in range
    int size = static_cast<int>(components.size()); // make sure its a signed integer

    if(component_choice_int - 1 >= size) // check if right size
    {
      std::cin.clear();  // clear a failed state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
      std::cout << "Input too high."
                 << " Please choose integer in library" << std::endl;
    } 
    
    else if(component_choice_int <= 0 && component_choice_int != -995)
    {
      std::cin.clear();  // clear a failed state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
      std::cout << "Input too low."
      << " Please choose integer in library" << std::endl;
    }

    else if(component_choice_int == -995) // will be this if the input wasnt integer
    {
      // do nothing (already printed error)
    }

    else
    {
      break;
    }
  }

  return component_choice_int;
}


int choose_remove_component(std::unique_ptr<Circuit>& circuit)
{
  std::string component_choice_str;
  int component_choice_int = -995; 

  while(true)
  {
    std::cout << "\nEnter Component Index to Remove: " << std::endl;
    std::cin >> component_choice_str;

    try 
    { // try converting the input to an integer
      component_choice_int = std::stoi(component_choice_str);  
    } 
    catch (const std::invalid_argument& e) 
    {
      std::cout << "Invalid input. Please enter a valid number." << std::endl;
    }
    
    std::vector<std::shared_ptr<Component>> added_components = circuit->get_added_components();
    // store size of library vector as size to check if integer input in range
    int size = static_cast<int>(added_components.size()); // make sure its a signed integer

    if(component_choice_int - 1 >= size) // check if right size
    {
      std::cin.clear();  // clear a failed state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
      std::cout << "Input too high."
                 << " Please choose integer in library" << std::endl;
    } 
    
    else if(component_choice_int <= 0 && component_choice_int != -995)
    {
      std::cin.clear();  // clear a failed state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
      std::cout << "Input too low."
      << " Please choose integer in library" << std::endl;
    }

    else if(component_choice_int == -995) // will be this if the input wasnt integer
    {
      // do nothing (already printed error)
    }

    else
    {
      break;
    }
  }

  return component_choice_int;
}


void add_component(std::unique_ptr<Circuit>& circuit, std::shared_ptr<Component>& component)
{
  std::string choice;

  while (true) 
  {
    std::cout << "Series or Parallel? (s/p) ";
    std::cin >> choice;

    if (choice == "s" || choice == "S") 
    {
      circuit->add_series(component);
      break;
    } 

    else if (choice == "p" || choice == "P") 
    {
      circuit->add_parallel(component);
      break;  // Exit the loop and terminate the program
    } 

    else 
    {
        // If input is not s or p 
        std::cin.clear();  // clear a failed state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
        std::cout << "Invalid input" << std::endl; // say its invalid
    }

  }
}


void create_circuit(std::unique_ptr<Circuit>& circuit, std::vector<std::shared_ptr<Component>>& components) 
{
  int component_index = choose_component(components);
  circuit->add_series(components[component_index-1]);

  std::string add_another;

  while (true) 
  {
    // Wait for user input. The program will pause here.
    print_dash();
    std::cout << "Add another? (y/n) ";
    std::cin >> add_another;

    if (add_another == "y") 
    {
      component_index = choose_component(components);
      add_component(circuit, components[component_index-1]);
    } 

    else if (add_another == "n") 
    {
        // If 'e' is entered, exit the program
        std::cout << "Circuit Creation Complete" << std::endl;
        break;  // Exit the loop and terminate the program
    } 

    else 
    {
        // If input is not 'c' or 'e', you can handle it here.
        std::cin.clear();  // clear a failed state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
        std::cout << "Invalid input." << std::endl;
    }
  }

  circuit->print_data(); // print the circuit information once created

}


int choose_circuit(const std::vector<std::unique_ptr<Circuit>>& circuits)
{
  std::string circuit_choice_str;
  int circuit_choice_int = -995; 

  while(true)
  {
    std::cout << "\nEnter Circuit Number: " << std::endl;
    std::cin >> circuit_choice_str;

    try 
    { // try converting the input to an integer
      circuit_choice_int = std::stoi(circuit_choice_str);  
    } 
    catch (const std::invalid_argument& e) 
    {
      std::cout << "Invalid input. Please enter a valid number." << std::endl;
    }
          
    // store size of library vector as size to check if integer input in range
    int size = static_cast<int>(circuits.size()); // make sure its a signed integer

    if(circuit_choice_int - 1 >= size) // check if right size
    {
      std::cin.clear();  // clear a failed state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
      std::cout << "Input too high."
                 << " Please choose integer in library" << std::endl;
    } 
    
    else if(circuit_choice_int <= 0 && circuit_choice_int != -995)
    {
      std::cin.clear();  // clear a failed state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
      std::cout << "Input too low."
      << " Please choose integer in library" << std::endl;
    }

    else if(circuit_choice_int == -995) // will be this if the input wasnt integer
    {
      // do nothing (already printed error)
    }

    else
    {
      break;
    }
  }

  return circuit_choice_int;
}


void edit_circuit(std::vector<std::shared_ptr<Component>>& components, std::vector<std::unique_ptr<Circuit>>& circuits)
{
  if(circuits.size() == 0)
  {
    std::cout << "No circuits have been created.\n"
              << "To edit a circuit - you must make one." << std::endl;
    return;
  }

  std::cout << "Which circuit would you like to edit? (see library)" << std::endl;
  int circuit_index = choose_circuit(circuits);
  std::string add_another;

  while (true) 
  {
    // Wait for user input. The program will pause here.
    print_dash();
    std::cout << "Add component? (y/n) ";
    std::cin >> add_another;
    int component_index = 0; // define the component index

    if (add_another == "y") 
    {
      component_index = choose_component(components);
      add_component(circuits[circuit_index - 1], components[component_index-1]);
    } 

    else if (add_another == "n") 
    {
        // If 'e' is entered, exit the program
        std::cout << "Circuit Editting Complete" << std::endl;
        break;  // Exit the loop and terminate the program
    } 

    else 
    {
        // If input is not 'c' or 'e', you can handle it here.
        std::cin.clear();  // clear a failed state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
        std::cout << "Invalid input." << std::endl;
    }
  }

  circuits[circuit_index - 1]->print_data(); // print the circuit information once created

}


void complex_circuit_editor_guide()
{
  print_dash(); // to separate from above outputs

  std::cout << "Command\t\tDescription" << std::endl;
  std::cout << "---------------------------------------------" << std::endl;
  std::cout << "h\t\tDisplay circuit editor guide" << std::endl;
  std::cout << "a\t\tAdd component" << std::endl;
  std::cout << "r\t\tRemove component" << std::endl;
  std::cout << "n\t\tAdd nested circuit" << std::endl;
  std::cout << "i\t\tDisplay current circuit info" << std::endl;
  std::cout << "g\t\tDisplay component library" << std::endl;
  std::cout << "x\t\tExit the circuit editor" << std::endl;
}


void complex_circuit_editor(std::vector<std::shared_ptr<Component>>& components, std::unique_ptr<Circuit>& circuit) 
{
  complex_circuit_editor_guide();
  // Your program will now just wait for the user input
  std::string user_input;
  /* Tnitialise integer to check if adding first component.
  If so, we want to add in series (avoid dividing by 0)
  Add 1 every time use add function. */
  int check_if_first_component = 0;

  while (true) 
  {
    // Wait for user input here for user input
    print_dash(); // formatting
    std::cout << " " << std::endl; // to allow for an input
    std::cin >> user_input; // wait for input

    if(user_input == "h") // if choose the help guide
    {
      complex_circuit_editor_guide(); // print the help guide
    }

    else if(user_input == "i") // if choose to print circuit info
    {
      circuit->print_data(); // print the info of the circuit
    }

    else if(user_input == "x") // if chose to exit the program
    {
      break;  // Then break the loop
    } 

    else if(user_input == "g") // if choose to display component library
    {
      // display the component library
      print_component_library(components);
    }

    else if(user_input == "r")
    {
      std::vector<std::shared_ptr<Component>> added_components = circuit->get_added_components();
      int num_of_components = added_components.size();

      if (num_of_components > 0)
      {
        circuit->print_data(); // print the current circuit info

        // take user input for which component to remove
        int remove_component_index = choose_remove_component(circuit);

        // print the choice to check
        std::cout << "Choice: " << remove_component_index << std::endl;

        // use member funtion to remove the component
        circuit->remove_component(remove_component_index);

        // print info for the new circuit
        std::cout << "New circuit info:" << std::endl;
        circuit->print_data();
      }
    
      else
      {
        std::cout << "Add some components first!" << std::endl;
        std::cout << "Press i to see the circuit. " 
                  << "It probably has nothing in it" << std::endl;
      }

    }

    else if(user_input == "a") // if choose to add a component
    {
      // ask the user which component they would like to add
      int component_index = choose_component(components);

      /* If this is the first component being added */
      if(check_if_first_component == 0)
      {
        // then add it in series
        circuit->add_series(components[component_index-1]);
        check_if_first_component += 1;
      }      
      else 
      { // otherwise, ask user how they whether to add in s/p
      add_component(circuit, components[component_index-1]);
      }
    }

    else 
    {
      // If input is not given by the above
      std::cin.clear();  // clear a failed state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input

      // prompt user to open the menu to help with what to do
      std::cout << "Invalid option. Refer to the circuit editor guide (h)" << std::endl;
    }
  }

  circuit->print_data(); // print data when exit
  std::cout << "Exiting circuit editor." << std::endl; // exit call message
}


int main() {

//  initial_statement(); // output to explain program

  /* Create a vector of smart pointers to arbitrary components */
  std::vector<std::shared_ptr<Component>> components;
  std::vector<std::unique_ptr<Circuit>> circuits;

  read_components(FILE_NAME, components); // read components from file, add to vector

  print_user_guide();

  // Your program will now just wait for the user input
  std::string user_input;

  while (true) 
  {
    // Wait for user input. The program will pause here.
    print_dash();
    std::cout << " " << std::endl;
    std::cin >> user_input;

    if (user_input == "c") 
    {
      print_dash(); // readability
      std::cout << "CREATING CIRCUIT:" << std::endl;

      // create a smart pointer to a circuit
      std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();

      // ask user to build circuit with components
      // create_circuit_old(circuit, components); (old create circtui function)
      create_circuit(circuit, components);

      // add circuit to circuit library
      circuits.push_back(std::move(circuit));  // Move the unique_ptr to the vector
    } 

    else if(user_input == "h")
    {
      print_user_guide();
    }

    else if(user_input == "g") // if user inputs g
    {
      print_component_library(components); // print the library
    }

    else if(user_input == "x") 
    {
        // If 'e' is entered, exit the program
        std::cout << "Exiting program." << std::endl;
        break;  // Exit the loop and terminate the program
    } 

    else if(user_input == "e")
    {
      print_circuit_library(circuits);
      print_dash();
      edit_circuit(components, circuits);
    }

    else if(user_input == "q")
    {
      print_circuit_library(circuits);
    }

    else if(user_input == "k")
    {
      print_dash();
      std::cout << "OPENING CIRCUIT EDITOR" << std::endl;

      // create a smart pointer to a circuit
      std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();

      // ask user to build circuit with components
      // create_circuit_old(circuit, components); (old create circtui function)
      complex_circuit_editor(components, circuit);

      // add circuit to circuit library
      circuits.push_back(std::move(circuit)); 

    }

    else 
    {
      // If input is not 'c' or 'e', you can handle it here.
      std::cin.clear();  // clear a failed state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
      std::cout << "Invalid option. Refer to the user guide (h)" << std::endl;
    }
  }

  print_dash(); // for readability

  return 0;

}







