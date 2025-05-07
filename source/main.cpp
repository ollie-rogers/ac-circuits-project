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


void print_user_guide() 
{
    /* Output table with two columns:
  i) First Column is the command (typed)
  ii) Second Column is the description
  Covers all main functionality of 'homepage' */

  print_dash(); // to separate from previous outputs

  // outputting main table
  std::cout << "Command\t\tDescription" << std::endl;
  std::cout << "---------------------------------------------" << std::endl;
  std::cout << "help\t\tDisplay user guide" << std::endl;
  std::cout << "create\t\tCreate a new circuit (Basic)" << std::endl;
  std::cout << "edit\t\tEdit a circuit (Basic)" << std::endl;
  std::cout << "editor\t\tOpen complex circuit editor" << std::endl;
  std::cout << "components\tDisplay component library" << std::endl;
  std::cout << "circuits\tDisplay circuit library" << std::endl;
  std::cout << "exit\t\tExit the program" << std::endl;
}


void read_components(const std::string& filename, std::vector<std::shared_ptr<Component>>& components)
{  
  /* Parameters: 
   - components (vector of smart pointers components) - to store the components
   - filename (string) - kept abitrary so can use for different files
  Aims:
   - reads file line by line
   - determines which component each line is
   - adds a smart pointer to that component to vector */
  
  std::ifstream file(filename); // opening the file
  std::string line; // defining a string which holds each line whilst reading

  print_dash(); // for readability
  std::cout << "\nGENERATING COMPONENTS:" << std::endl; // call message

  while (std::getline(file, line)) { // Whilst lines remain

      std::stringstream ss(line); // making stringstream of current line
      std::string type, name; // deinfing variables to store type, name, frequency and value (e.g. resistance)
      double value;

      std::getline(ss, type, ','); // read up to first comma, this is type
      std::getline(ss, name, ','); // read up to next comma, this is name
      ss >> value; // extract the numeric value, this is value

      /* Create smart pointers and add to vector */
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
   - components (vector of smart pointers to components) - stores the components
   Aims:
   - to iterate through the vector
   - use the print data functions to print each component */

  print_dash(); // for readability
  std::cout << "\nCOMPONENT LIBRARY:" << std::endl; // call message

  int counter = 1; // initialising variable to label number of component

  for (const std::shared_ptr<Component>& component : components) {
    std::cout << "\n" << counter << ") " 
              << std::endl; // label component number in library
    component->print_data(); // print data of component
    counter += 1; // add one to label
  }

}


void print_circuit_library(const std::vector<std::unique_ptr<Circuit>>& circuits)
{
  /* Parameters:
   - components (vector of smart pointers to components) - stores the components
   Aims:
   - to iterate through the vector
   - use the print data functions to print each component*/

  print_dash(); // for readability
  std::cout << "\nCIRCUIT LIBRARY:" << std::endl;

  int counter = 1; // initialising variable to label number of component

  for (const std::unique_ptr<Circuit>& circuit : circuits) {
    std::cout << "\n" << counter << ") " 
              << std::endl; // label component number in library
    circuit->print_data(); // print data of component
    counter += 1;
  }

}


int choose_component(std::vector<std::shared_ptr<Component>>& components)
{
  /* Parameters
  i) Components (vector of smart pointers) - stores the components 
  Aims:
  i) Loop asking the user for input and takes input as a string
  ii) Tries converting to an integer
  iii) If fails, prints error and loops again
  iv) If succeed, checks if integer is in the range of components vector
  v) If no, prints error and loops again
  vi) If yes, returns the choice of component (integer index) */

  std::string component_choice_str; // to store the input as string

  // define random number (will see why later)
  int component_choice_int = -999; 

  while(true) // whilst user input is invalid
  {
    // ask user for input
    std::cout << "\nEnter Component Number (1, 2, 3...): " << std::endl;
    std::cin >> component_choice_str;

    try 
    { 
      // try converting input to integer
      component_choice_int = std::stoi(component_choice_str);  
    } 
    catch (const std::invalid_argument& e) 
    {
      // if can't convert, print error
      std::cout << "Invalid input. Please enter a valid number." << std::endl;
    }
          
    // store size of library vector as size to check if integer input in range
    int size = static_cast<int>(components.size()); // make sure its a signed integer

    if(component_choice_int - 1 >= size) // check if right size
    {
      std::cin.clear();  // clear the failed state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
      std::cout << "Input too high." // error message
                 << " Please choose integer in library" << std::endl;
    } 
    
    else if(component_choice_int <= 0 && component_choice_int != -999) // check if right size
    {
      std::cin.clear();  // clear the failed state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
      std::cout << "Input too low." // error message
      << " Please choose integer in library" << std::endl; 
    }

    else if(component_choice_int > 0 && component_choice_int < size + 1)
    {
      break; // exit the loop as choice in the right range
    }

    else
    {
      // print nothing
    }
  }

  return component_choice_int; // return the choice of component
}


int choose_remove_component(std::unique_ptr<Circuit>& circuit)
{
    /* Parameters
  i) Circuit (object) - contains a vector of the added components
  Aims:
  i) Loop asking the user for input and takes input as a string
  ii) Tries converting to an integer
  iii) If fails, prints error and loops again
  iv) If succeed, checks if integer is in the range of components vector
  v) If no, prints error and loops again
  vi) If yes, returns the choice of component (integer index) */

  std::string component_choice_str; // define string to store input

  // define random number 
  int component_choice_int = -995; 

  while(true) // whilst user input is invalid
  {
    // ask for user input
    std::cout << "\nEnter Component Index to Remove: " << std::endl;
    std::cin >> component_choice_str;

    try 
    { 
      // try converting the input to an integer
      component_choice_int = std::stoi(component_choice_str);  
    } 
    catch (const std::invalid_argument& e) 
    {
      // if cant convert, print error message
      std::cout << "Invalid input. Please enter a valid number." << std::endl;
    }
    
    // use getter to get the vector of added components
    std::vector<std::shared_ptr<Component>> added_components = circuit->get_added_components();

    // store size of library vector as size to check if integer input in range
    int size = static_cast<int>(added_components.size()); // make sure its a signed integer

    if(component_choice_int - 1 >= size) // check if right size
    {
      std::cin.clear();  // clear a failed state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
      std::cout << "Input too high." // error message
                 << " Please choose integer in library" << std::endl;
    } 
    
    else if(component_choice_int <= 0 && component_choice_int != -995) // check if right size
    {
      std::cin.clear();  // clear a failed state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
      std::cout << "Input too low." // error message
      << " Please choose integer in library" << std::endl;
    }

    else if(component_choice_int > 0 && component_choice_int < size + 1) // will be this if the input wasnt integer
    {
      break; // break if in the right range
    }

    else
    {
      // do nothing
    }
  }

  return component_choice_int; // return the choice
}


void add_component(std::unique_ptr<Circuit>& circuit, std::shared_ptr<Component>& component)
{
  /* Parameter:
  i) circuit (object) - the circuit object being added to
  ii) component (object) - the component being added to circuit
  Aims:
  i) to ask the user whether they would like to add in s/p
  ii) use the adder functions from circuit class
   - to add the component accordingly */

  std::string choice; // to hold user input for series or parallel

  while (true) // while user input invalid
  {
    // as whether to add in series or parallel
    std::cout << "Series or Parallel? (s/p) ";
    std::cin >> choice;

    if (choice == "s" || choice == "S") 
    {
      /* if choose series, use the series adder function from the circuit class
      to add accordingly */
      circuit->add_series(component);

      break; // break the loop (valid input)
    } 

    else if (choice == "p" || choice == "P") 
    {
      /* if choose parallel, use the parallel adder function from the circuit
      class to add accordingly */
      circuit->add_parallel(component);

      break; // break the loop (valid input)
    } 

    else 
    {
        // If input is not s or p (invalid)
        std::cin.clear();  // clear a failed state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
        std::cout << "Invalid input" << std::endl; // error message
    }

  }
}


void create_circuit(std::unique_ptr<Circuit>& circuit, std::vector<std::shared_ptr<Component>>& components) 
{
  /* Parameters:
  i) Circuit (unique pointer) - circuit being created
  ii) Components (vector of smart pointers) - list of possible components
  Aims:
  i) Prints component library
  ii) User must input first component using component nums from library
     - This is added in series (must be)
  iii) Asks whether user would like to add another
  iv) If so, asks to choose the component and series or parallel
  v) Adds accordingly and repeats until user choose not to add any more */

  // get user input for choice of first component
  int component_index = choose_component(components); 

  // add the first component in series
  circuit->add_series(components[component_index-1]);

  // define a string to store users choice whether to add another component
  std::string add_another;

  while (true) // whilst the user is choosing to add more components
  {
    // Ask the user to choose
    std::cout << "\nAdd another? (y/n) ";
    std::cin >> add_another;

    if (add_another == "y") // if choose to add another
    {
      // ask which component to add and if series or parallel
      component_index = choose_component(components);

      // add that component in series or parallel
      add_component(circuit, components[component_index-1]);
    } 

    else if (add_another == "n") // if choose not to add another
    {
      print_vspace(); // formatting

      break;  // Exit the loop
    } 

    else // if input is not valid
    {
        std::cin.clear();  // clear the failed state

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input

        std::cout << "Invalid input." << std::endl; // print error message
    }
  }

  circuit->print_data(); // print the circuit information once created
}


int choose_circuit(const std::vector<std::unique_ptr<Circuit>>& circuits)
{
  /* Parameters:
  i) Circuits (vector of smart pointers) - list of created circuits
  Aims:
  i) To take user input for which circuit they would like to choose */

  // define a string to store users choice of circuit
  std::string circuit_choice_str; 
  int circuit_choice_int = -999; 

  while(true) // whilst user input is invalid
  {
    std::cout << "\nEnter Circuit Number: " << std::endl; // prompt

    // define string to store input
    std::cin >> circuit_choice_str;

    try 
    { 
      // try converting input to integer
      circuit_choice_int = std::stoi(circuit_choice_str);  
    } 
    catch (const std::invalid_argument& e) 
    {
      // if cant convert, error message
      std::cout << "Invalid input. Please enter a valid number." << std::endl;
    }
          
    // store size of library vector as size to check if integer input in range
    int size = static_cast<int>(circuits.size()); // make sure its a signed integer

    if(circuit_choice_int - 1 >= size) // check if right size
    {
      std::cin.clear();  // clear the failed state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
      std::cout << "Input too high."
                 << " Please choose integer in library" << std::endl;
    } 
    
    else if(circuit_choice_int <= 0 && circuit_choice_int != -999) // check if right size
    {
      std::cin.clear();  // clear the failed state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
      std::cout << "Input too low."
      << " Please choose integer in library" << std::endl;
    }

    else if(circuit_choice_int > 0 && circuit_choice_int < size + 1) // will be this if the input wasnt integer
    {
      break; // if in the right range, break loop
    }

    else
    {
      // do nothing and loop again
    }
  }

  return circuit_choice_int; // return the choice of circuit
}


void edit_circuit(std::vector<std::shared_ptr<Component>>& components, std::vector<std::unique_ptr<Circuit>>& circuits)
{
  /* Parameters:
  i) components (vector of smart pointers to components) - stores the components
  ii) circuits (vector of smart pointers to circuits) - stores the created circuits
  Aims:
  i) Print the list of circuits that have been created
  ii) Ask the user which one they would like to edit
  iii) Allow the user to add more components in series or parallel */

  if(circuits.size() == 0) 
  {
    // if no circuits have been created
    std::cout << "No circuits have been created.\n" // error message
              << "To edit a circuit - you must make one." << std::endl;

    return; // no circuits to edit so go back to home
  }

  // ask user which circuit to edit
  std::cout << "Which circuit would you like to edit? (see library: 1, 2, 3...)" << std::endl;

  // use the choose circuit function to print list of circuits and get user input
  int circuit_index = choose_circuit(circuits);

  std::string add_another; // to store choice of whether to add another component

  // print component library so user can see what they want to add
  print_component_library(components);

  while (true) // whilst choice of whether to add another is invalid
  {
    // ask whether to add a component
    std::cout << "\nAdd component? (y/n) ";
    std::cin >> add_another;

    int component_index = 0; // define the component index

    if (add_another == "y") 
    {
      /* if choose to add another, choose the components, choose
      whether series or parallel, add to circuit */
      component_index = choose_component(components);
      add_component(circuits[circuit_index - 1], components[component_index-1]);
    } 

    else if (add_another == "n") 
    {
      // if choose not to add another, print a space
      print_vspace();

      break;  // break the loop
    } 

    else 
    {
        // If input is invalid
        std::cin.clear();  // clear the failed state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input
        std::cout << "Invalid input." << std::endl; // error message
    }
  }

  circuits[circuit_index - 1]->print_data(); // print the circuit information once created
}


void complex_circuit_editor_guide()
{
  /* Output table with two columns:
  i) First Column is the command (typed)
  ii) Second Column is the description
  Covers all main functionality of the editor */

  print_dash(); // to separate from above outputs

  // output main table
  std::cout << "Command\t\tDescription" << std::endl;
  std::cout << "---------------------------------------------" << std::endl;
  std::cout << "help\t\tDisplay circuit editor guide" << std::endl;
  std::cout << "add\t\tAdd component" << std::endl;
  std::cout << "remove\t\tRemove component" << std::endl;
  std::cout << "info\t\tDisplay current circuit info" << std::endl;
  std::cout << "components\tDisplay component library" << std::endl;
  std::cout << "exit\t\tExit the circuit editor" << std::endl;
}


void complex_circuit_editor(std::vector<std::shared_ptr<Component>>& components, std::unique_ptr<Circuit>& circuit) 
{
  /* Parameters:
  i) components (vector of smart pointers to components) - stores the components
  ii) circuit (smart pointer to circuit object) - circuit to be editted
  Aims:
  - Program "waits" for user input
  - The possible inputs are given in the editor guide
  - Function are:
  i) Print the editor guide 
  ii) Display the component library (components vector)
  iii) Display the current circuit info
       (the circuit being editted)
  iv) Add a component
  v) Remove a component
  vi) Exit the editor */

  // print the editor guide to help user
  complex_circuit_editor_guide();

  std::string user_input; // to store user input

  /* Initialise integer to check if adding first component.
  If so, we want to add in series (avoid dividing by 0)
  Add 1 every time use add function. */
  int check_if_first_component = 0;

  while (true) 
  {
    /* This loop will keep running until the user chooses 
    to exit the editor. */

    print_dash(); // formatting

    // wait here for user input
    std::cout << "Editor: What would you like to do? " 
              << "(type 'help' for guide)" << std::endl;
    std::cin >> user_input; 

    if(user_input == "help") // if choose the help guide
    {
      complex_circuit_editor_guide(); // print the help guide
    }

    else if(user_input == "info") // if choose to print circuit info
    {
      circuit->print_data(); // print the info of the circuit
    }

    else if(user_input == "exit") // if chose to exit the program
    {
      break;  // Then break the loop
    } 

    else if(user_input == "components") // if choose to display component library
    {
      // display the component library
      print_component_library(components);
    }

    else if(user_input == "remove") 
    {
      /* If choose to remove a component
      - First get the vector of added components from the circuit object
      - Next, check if there are any components added
        - If no components in circuit, print error message
      - If circuit has components, ask which to remove
      - Recalculate the impedance of the circuit
      - Update the connection matrix and added components vector */

      // use getter to get vector of added components
      std::vector<std::shared_ptr<Component>> added_components = circuit->get_added_components();

      int num_of_components = added_components.size(); // get num added

      if (num_of_components > 0)
      {
        // if some components have been added

        circuit->print_data(); // print the current circuit info

        // take user input for which component to remove
        int remove_component_index = choose_remove_component(circuit);

        // use member funtion to remove the component
        circuit->remove_component(remove_component_index);

        // recalculate the impedance
        circuit->calculate_impedance();

        // print info for the new circuit
        std::cout << "New circuit info:" << std::endl;
        circuit->print_data();
      }
    
      else
      {
        // if no components in circuit
        std::cout << "Add some components first!" << std::endl;
        std::cout << "Type 'info' to see the circuit - " 
                  << "It probably has nothing in it." << std::endl;
      }

    }

    else if(user_input == "add")
    {
      /* If choose to add a component, add in similar way to
      add component function */

      // ask the user which component they would like to add
      int component_index = choose_component(components);

      if(check_if_first_component == 0)
      {
        // if its the first component added, add in series
        circuit->add_series(components[component_index-1]);

        check_if_first_component += 1; // add one to the checker
      }      
      else 
      { 
        // otherwise, ask user how they whether to add in s/p
        // add component accordingly, updating matrix, vector
        add_component(circuit, components[component_index-1]);
      }
    }

    else 
    {
      // If input is invalid (not given above)
      std::cin.clear();  // clear the failed state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input

      // prompt user to open the menu to help with what to do (error message)
      std::cout << "Invalid option. Refer to the circuit editor guide (h)" << std::endl;
    }
  }

  circuit->print_data(); // print the data of the created circuit when returning to home
}


void return_statement()
{ 
  // prints statement to let user know returning to home
  std::cout << "\nReturning to home." << std::endl; 

  print_user_guide(); // print the user guide
}


int main() 
{

  /* Create a vector of smart pointers to store the components */
  std::vector<std::shared_ptr<Component>> components;

  /* Create a vector of smart pointers to store the circuits */
  std::vector<std::unique_ptr<Circuit>> circuits;

  // read in the components from the file and add to the components vector
  read_components(FILE_NAME, components); 

  // print the user guide
  print_user_guide();


  std::string user_input; // define variable for user input

  // loop until the user chooses to exit the program
  while (true) 
  {
    /* Aims:
     - Program "waits" for user input
     - The possible inputs are given in the guide
     - Function are:
      i) Print the user guide 
      ii) Display the component library (components vector)
      iii) Display the circuit library (circuits vector)
      iv) Create a new circuit in the basic way
          (explained in function)
      v) Edit a circuit in the basic way
          (explained in function)
      vi) Open the complex circuit editor
          (explained in the function)
      vii) Exit the program */

    print_dash(); // formatting
    // print to let user know when in home screen

    /* Wait here until the user inputs something
    Prompts the user that they need to input to proceed */
    std::cout << "Home: What would you like to do? (type 'help' for guide)" << std::endl;
    std::cin >> user_input;

    if (user_input == "create") // if the user inputs "create"
    {
      print_dash(); // formatting
      std::cout << "CREATING CIRCUIT:" << std::endl; // call message

      // create a smart pointer to a circuit
      std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();

      // print component library so user can choose components
      print_component_library(components);
      print_dash(); // formatting

      /* Build the circuit (see function) */
      create_circuit(circuit, components);

      // add circuit to circuits vector
      circuits.push_back(std::move(circuit));

      return_statement(); // let user know returning to home
    } 

    else if(user_input == "help") // if user inputs "help"
    {
      print_user_guide(); // print the user guide
    }

    else if(user_input == "components") // if user inputs "components"
    {
      // print the vector of components
      print_component_library(components);
    }

    else if(user_input == "exit") // if the user inputs "exit"
    {
        std::cout << "Exiting program." << std::endl; // call message
        break;  // break the loop
    } 

    else if(user_input == "edit") // if the user inputs "edit"
    {
      // print the vector of circuits so user can choose which to edit
      print_circuit_library(circuits);

      print_dash(); // formatting

      // allow the user to add more components to circuit of choice
      edit_circuit(components, circuits);

      return_statement(); // let user know returning to home
    }

    else if(user_input == "circuits") // if user inputs "circuits"
    {
      // print the vector of circuits
      print_circuit_library(circuits);
    }

    else if(user_input == "editor") // if user inputs "open editor"
    {
      print_dash(); // formatting

      std::cout << "OPENING CIRCUIT EDITOR" << std::endl; // call message

      std::string input; // define variable for user input

      while(true) // loop until user makes valid choice
      {
        // ask user whether to create or edit a circuit
        std::cout << "Would you like to create a new circuit"
        << " or edit an existing circuit (c/e)" << std::endl;
        std::cin >> input;

        if(input == "c" || input == "C") // if choose to create new circuit
        {
          /* Lets the user build a new circuit from scratch using the 
          complex editor*/
          // create a new smart pointer to a circuit
          std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();

          // open the complex circuit editor
          complex_circuit_editor(components, circuit);

          // add the new circuit to circuit library
          circuits.push_back(std::move(circuit)); 

          break; // break the loop
        }

        else if(input == "e" || input == "E") // if choose to edit a circuit
        {
          /* If the circuits vector contains any circuits, user can choose which
          circuit they edit. If not, tells user they need to make a circuit first */

          if(circuits.size() == 0) // check if the circuits vector has any circuits
          {
            std::cout << "No circuits have been created.\n"
                      << "To edit a circuit - you must make one." << std::endl;
            // if no circuits created, print the message above
          }
          else
          {
            print_circuit_library(circuits); // print the circuit library

            // asks which circuit user would like to edit
            std::cout << "Which circuit would you like to edit? (see library)" << std::endl;
            int circuit_index = choose_circuit(circuits);

            // open the complex circuit editor
            complex_circuit_editor(components, circuits[circuit_index - 1]);

            // Note: no need to add the circuit to the library (already stored)
          }

          break; // break the loop
        }

        else // if user input is not of the right form
        {
          std::cin.clear();  // clear the failed state

          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input

          // print error message
          std::cout << "Invalid option. Refer to the user guide." << std::endl; 

          complex_circuit_editor_guide(); // print the guide
        }
      }

      return_statement(); // lets user know returning to home
    }

    else // if the user input is not of the right form
    {
      std::cin.clear();  // clear the failed state

      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // empty input

      // print error message
      std::cout << "Invalid option. Refer to the user guide." << std::endl;

      print_user_guide();
    }
  }

  print_dash(); // for readability

  return 0; // end of program
}
