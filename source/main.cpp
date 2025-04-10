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
    std::cout << "\n" << counter << ") " 
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









// bool y_or_n_input_validity(std::string choice) {

//   /* Checks whether the choice of whether to print the full list is of the right form.
//   If of the right form returns true.
//   If not of the right form, prints error message and returns false. */
//   if (std::cin.fail() || std::cin.peek() != '\n') {
//       error_message();
//       return false;
//   } else if (choice == "y" || choice == "n") {
//       return true;
//   } else {
//       error_message();
//       return false;
//   }

//   return false;
// }


// bool s_or_p_input_validity(std::string choice) {

//   /* Checks whether the choice of whether to print the full list is of the right form.
//   If of the right form returns true.
//   If not of the right form, prints error message and returns false. */
//   if (std::cin.fail() || std::cin.peek() != '\n') {
//       error_message();
//       return false;
//   } else if (choice == "s" || choice == "p") {
//       return true;
//   } else {
//       error_message();
//       return false;
//   }

//   return false;
// }


// bool int_input_validity(std::string choice) {

//   /* Checks whether the choice of whether to print the full list is of the right form.
//   If of the right form returns true.
//   If not of the right form, prints error message and returns false. */
//   if (std::cin.fail() || std::cin.peek() != '\n') 
//   {
//       error_message();
//       return false;
//   }    

//   try 
//   { // try converting the input to an integer
//     std::stoi(choice);  
//     return true; // If successful, return true
//   } 
//   catch (const std::invalid_argument& e) 
//   {
//     // If it throws an exception, not an integer
//     error_message(); // print an error message
//     return false; // unsuccesful, so return false
//   }

//   return false;
// }  




// void create_circuit_old_oldest(std::unique_ptr<Circuit>& circuit, const std::vector<std::unique_ptr<Component>>& components)
//{
  /* Parameters:
   - circuit (smart pointer to a circuit object)
   - components (vector of smart pointers to arbitrary components) 
   Aims:
   - Iterate through the vector of components
   - For each component, ask the user to add in series or parallel 
   - Uses add_series and add_parallel functions to modify impedance od circuit */

//  print_dash(); // for readability

//  for (const std::unique_ptr<Component>& component : components) {

//    print_vspace(); // space for readability

//    component->print_data(); // prints data of component

//    bool input_iterator = false; // creating a boolean to check if input valid
//    std::string series_or_parallel; // creating a string to store user input of choice

//    while(input_iterator == false)
//    {
//      print_vspace(); // for readability

//      std::cout << "How would you like to add this component: Series / Parallel? (s/p)" 
//      << std::endl; // asking for user input on how to add the component

//      std::cin >> series_or_parallel; // assigns user input to variable

//      input_iterator = s_or_p_input_validity(series_or_parallel); // checks to see if valid input

//    } // breaks if valid input

//    if(series_or_parallel == "s") // if user chose to add in series
//    {
//      circuit->add_series(component); // use add_series to modify circuit
//    }
//    else if(series_or_parallel == "p") // if user chose to add in parallel
//    {
//      circuit->add_parallel(component); // use add_parallel to modify circuit
//    }

//  }
//}



// void create_circuit_old(std::unique_ptr<Circuit>& circuit, const std::vector<std::unique_ptr<Component>>& components)
// {
//   std::cout << "\nCREATING CIRCUIT:" << std::endl; // call message

//   bool choice_validity = false; // initialising variable to loop until choice is valid
//   std::string component_choice_str; // initialising variable for choosing component to add
//   int component_choice_int; // initialising integer version

//   while(choice_validity == false)
//   {
//     std::cout << "\nWhich component would you like add first?"
//               << "\nNote: first component always adds in series"
//               << "\nPlease choose a number (1, 2, 3... given in library)" << std::endl;
//     std::cin >> component_choice_str;

//     choice_validity = int_input_validity(component_choice_str);
      
//     if(choice_validity == true)
//     {
//       component_choice_int = std::stoi(component_choice_str);
        
//       // store size of library vector as size to check if integer input in range
//       int size = static_cast<int>(components.size()); // make sure its a signed integer

//       if(component_choice_int - 1 >= size) // check if right size
//       {
//         choice_validity = false;
//         std::cout << "Input too high."
//                   << "Please choose integer in library" << std::endl;
//       } 
//       else if(component_choice_int <= 0)
//       {
//         choice_validity = false;
//         std::cout << "Input too low."
//         << "Please choose integer in library" << std::endl;
//       }
//     }
//   }

//   // first component must always add in series
//   circuit->add_series(components[component_choice_int-1]);

//   // initialise variable to loop until series or parallel choice is valid
//   bool choice_yn_validity = false; 
//   // initialise variable to store choice of series or parallel
//   std::string choice_to_add_another;

//   while(choice_yn_validity == false) // while input is invalid
//   {
//     std::cout << "\nWould you like to add another component? (y/n)" << std::endl;
//     std::cin >> choice_to_add_another;
//     choice_yn_validity = y_or_n_input_validity(choice_to_add_another);    
//   } // break if

//   if(choice_to_add_another =="y")
//   {

//     // defining boolean variable to iterate until choose not to add any more components
//     bool choose_to_exit = false; 

//     while(choose_to_exit == false) // iterates until choose not to add any more
//     {
//       bool choice_validity = false; // initialising variable to loop until choice is valid
//       std::string component_choice_str; // initialising variable for choosing component to add
//       int component_choice_int; // initialising integer version

//       while(choice_validity == false)
//       {
//         std::cout << "\nWhich component would you like to add next?"
//                   << "\nPlease choose a number (1, 2, 3... given in library)" << std::endl;
//         std::cin >> component_choice_str;

//         choice_validity = int_input_validity(component_choice_str);

//         if(choice_validity == true)
//         {
//           component_choice_int = std::stoi(component_choice_str);
          
//           // store size of library vector as size to check if integer input in range
//           int size = static_cast<int>(components.size()); // make sure its a signed integer

//           if(component_choice_int - 1 >= size) // check if right size
//           {
//             choice_validity = false;
//             std::cout << "Input too high."
//                       << "Please choose integer in library" << std::endl;
//           } 
//           else if(component_choice_int <= 0)
//           {
//             choice_validity = false;
//             std::cout << "Input too low."
//             << "Please choose integer in library" << std::endl;
//           }
//         }
//       }
        
//       // initialise variable to loop until series or parallel choice is valid
//       bool choice_sp_validity = false;
//       // initialise variable to store choice of series or parallel
//       std::string series_or_parallel;

//       while(choice_sp_validity == false) // while input is invalid
//       {
//         std::cout << "\nWould you like to add in series or parallel?" << std::endl;
//         std::cin >> series_or_parallel;
//         choice_sp_validity = s_or_p_input_validity(series_or_parallel);
//       } // break if choice is valid

//       /*Next we actually add the component in series / parallel */

//       if(series_or_parallel == "s") 
//       {
//         // if chose series, add chosen component in series
//         circuit->add_series(components[component_choice_int-1]);
//       }
//       else if(series_or_parallel == "p")
//       {
//         // if chose parallel, add chosen component in parallel
//         circuit->add_parallel(components[component_choice_int-1]);
//       }

//       /* Next we want to add the component accordingly */

//       // initialise variable to loop until series or parallel choice is valid
//       bool choice_yn_validity = false;
//       // initialise variable to store choice of series or parallel
//       std::string choice_to_add_another;
      
//       while(choice_yn_validity == false) // while input is invalid
//       {
//         std::cout << "\nWould you like to add another component? (y/n)" << std::endl;
//         std::cin >> choice_to_add_another;
//         choice_yn_validity = y_or_n_input_validity(choice_to_add_another);    
//       } // break if choice is valid

//       if(choice_to_add_another == "n")
//       {
//         choose_to_exit = true;
//       }

//     } // exit when choose to do so
//   }

// }
