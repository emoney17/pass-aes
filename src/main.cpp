#include <iostream>
#include <fstream>

void printMenu()
{
    std::string menu = "___________________________________________\n"
                       "|                                          |\n"
                       "|          Entry to data GRANTED           |\n"
                       "|         1. View all passwords            |\n"
                       "|         2. Edit passwords                |\n"
                       "|         3. Add a password                |\n"
                       "|         4. Delete a password             |\n"
                       "|         5. Quit                          |\n"
                       "|__________________________________________|\n";
    std::cout << menu << std::endl;
}

void printDashboard()
{
    std::string dashboard = "___________________________________________\n"
                            "|                                          |\n"
                            "|      Unlocking password database...      |\n"
                            "|__________________________________________|\n";
    std::cout << dashboard << std::endl;
}

int main (int argc, char *argv[])
{
    std::string password, path, key;
    int userChoice, newUser;
    // Validate the user
    printDashboard();
    std::cout << "If this is your first time running please type '0' to being the new user process" << std::endl;
    std::cin >> newUser;
    if (newUser == 0) std::cout << "Starting new user process..." << std::endl;
    std::cout << "Enter password: " << std::endl;
    std::cin >> password;
    std::cout << "Enter password data path: " << std::endl;
    std::cin >> path;
    std::cout << "Enter your encryption key here: " << std::endl;
    std::cin >> key;
    // Continue validation of all entered information
    std::cout << "Validating info..." << std::endl;
    std::cout << std::endl;

    // Check if password file exists
    std::ifstream file(path);
    if(!file.is_open())
    {
        std::cout << "The password file does not exist." << std::endl;
        return 0;
    }


    // Entry has been granted to the user
    while (userChoice != 5)
    {
        printMenu();
        std::cin >> userChoice;
        switch (userChoice)
        {
            case 1:
                {
                    std::cout << "Viewing all stored passwords\n";
                    if(file.is_open()) std::cout << file.rdbuf();
                    break;
                }
            case 2: std::cout << "Editing existing passwords\n";
                break;
            case 3: std::cout << "Adding a new password\n";
                break;
            case 4: std::cout << "Deleting an existing password\n";
                break;
            case 5: std::cout << "Qitting the program..." << std::endl;
                break;
            default: std::cout << "Please enter a valid option from the menu." << std::endl;
        }
    }
    return 0;
}
