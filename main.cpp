#include "CLI11.hpp"
#include "init.hpp"
#include "gen.hpp"

#include <algorithm>
#include <iostream>
#include <filesystem>

int main (int argc, char *argv[])
{
    CLI::App app{"App description"};

    bool initArg{false};
    bool symbolsArg{false};
    int generateArg {30};
    std::string insertArg = "NULL";
    std::string removeArg = "NULL";

    app.add_flag("-i,--init", initArg, "Initialize and generate basic files");
    app.add_option("-g,--generate", generateArg, "Generate a password for an entry");
    app.add_flag("-s,--nosymbols", symbolsArg, "No symbols on generated password");
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
        if (generateArg != 30)
        {
            if (symbolsArg) {
                genPasswordNoSymbol(generateArg);
                std::cout << "Generated password no symbols\n";
            }
            else
            {
                genPasswordFull(generateArg);
                std::cout << "Generated password[size]\n";
            }
        }
        else
        {
            genPasswordNoSymbol(generateArg);
            std::cout << "Generated password[30]\n";
        }
    }
    if (removeArg != "NULL")
    {
        std::cout << "you will remove: " << removeArg << std::endl;
    }
    return 0;
}
