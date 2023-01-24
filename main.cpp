#include "CLI11/CLI11.hpp"
#include "newUser.h"
#include "user.h"

int main(int argc, char *argv[]) {
    CLI::App app{"App description"};

    std::string passPath, keyPath, password;
    CLI::Option* newUser = app.add_flag("-n", "Generate a new user");
    CLI::Option* viewFile = app.add_flag("-v", "View a password file");
    CLI::Option* deleteEntry = app.add_flag("-d", "Delete an entry from a password file");
    CLI::Option* addEntry = app.add_flag("-a", "Add an entry from a password file");

    CLI11_PARSE(app, argc, argv);
    if (*newUser) generateNewUser();
    if (*viewFile)
    {
        std::cout << "Enter pass file location: ";
        std::getline(std::cin, passPath);
        std::cout << "Enter key file location: ";
        std::getline(std::cin, keyPath);
        std::cout << "Enter password: ";
        std::getline(std::cin, password);
        User user(password, passPath, keyPath);
        if (user.validateUser()) std::cout << "Valid user!" << std::endl;
        else std::cout << "Invalid password" << std::endl;
    }
    if (*deleteEntry) std::cout << "Deleting entry" << std::endl;
    if (*addEntry) std::cout << "Adding new entry" << std::endl;
}
