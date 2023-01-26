#include "CLI11.hpp"
#include "init.hpp"
#include "gen.hpp"
#include "parse.hpp"

#include <algorithm>
#include <iostream>
#include <filesystem>
#include <string>

int main (int argc, char *argv[])
{
    CLI::App app{"App description"};

    std::vector<char> password;
    std::vector<std::string> path;
    std::string directory = "temp/";

    bool initArg{false};
    bool symbolsArg{false};
    int generateArg = 0;
    std::string addArg = "NULL";
    std::string removeArg = "NULL";

    app.add_flag("-i,--init", initArg,
            "First time users generate necessary files");
    app.add_option("-g,--generate", generateArg,
            "Generate a password for an entry and pick the length size");
    app.add_flag("-s,--nosymbols", symbolsArg,
            "Generate a password with out special characters");
    app.add_option("-a,--add", addArg,
            "Add a new entry with the format 'Subject/Entry'");
    app.add_option("-r,--remove", removeArg,
            "Remove an entry with the format 'Subject/Entry'");

    CLI11_PARSE(app, argc, argv);

    if (initArg)
    {
        std::filesystem::create_directories("temp");
        generateFiles();
    }

    if (addArg != "NULL")
    {
        path = parse(addArg);
        for (auto j:path) std::cout << j << std::endl;
        directory.append(path[0]);
        std::filesystem::create_directories(directory);
        std::cout << directory << std::endl;

        if (generateArg != 0)
        {
            if (symbolsArg) {
                password = genPasswordNoSymbol(generateArg);
                for (auto i:password) std::cout << i;
                // std::cout << std::endl << password.size() << std::endl;
            }
            else
            {
                password = genPasswordFull(generateArg);
                for (auto i:password) std::cout << i;
                // std::cout << std::endl << password.size() << std::endl;
            }
        }
        else
        {
            password = genPasswordFull(30);
            for (auto i:password) std::cout << i;
            // std::cout << std::endl << password.size() << std::endl;
        }
    }

    if (removeArg != "NULL")
    {
        std::cout << "you will remove: " << removeArg << std::endl;
    }
    return 0;
}
