#include "CLI11.hpp"
#include "gen.h"
#include <iostream>
#include <filesystem>

int main (int argc, char *argv[])
{
    CLI::App app{"App description"};

    bool initArg{false};
    bool passwordArg{false};
    std::string insertArg = "NULL";
    std::string removeArg = "NULL";

    app.add_flag("-i,--init", initArg, "Initialize and generate basic files");
    app.add_flag("-g,--generate", passwordArg, "Aenerate a password for an entry");
    app.add_option("-a,--add", insertArg, "Add a new Subject/Entry");
    app.add_option("-r,--remove", removeArg, "Remove a Subjecy/Entry");



    CLI11_PARSE(app, argc, argv);

    if (initArg)
    {
        std::filesystem::create_directories("temp");
        generateFiles();
    }
    if (insertArg != "NULL")
    {
        if (passwordArg)
        {
            //generatePassword();
            std::cout << "Generating password...\n";
        }
        std::cout << "you will insert: " << insertArg << std::endl;
    }
    if (removeArg != "NULL")
    {
        std::cout << "you will remove: " << removeArg << std::endl;
    }
    return 0;
}
