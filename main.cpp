#include "CLI11.hpp"
#include "init.hpp"
#include "gen.hpp"
#include "parse.hpp"
#include "encode.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

int main (int argc, char *argv[])
{
    CLI::App app{"App description"};

    std::vector<char> password;
    std::string passwordString = "";
    std::vector<std::string> path;
    std::string directorypath = "temp/";
    std::string filepath = "temp/";

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
        directorypath.append(path[0]);
        std::filesystem::create_directories(directorypath);
        filepath.append(path[0]);
        filepath.append("/");
        filepath.append(path[1]);
        std::ofstream entry(filepath);

        if (generateArg != 0)
        {
            if (symbolsArg) {
                password = genPasswordNoSymbol(generateArg);
                for (auto i:password) passwordString.push_back(i);
                std::cout << "Password: " << passwordString << std::endl;
                entry << encode(passwordString);
                entry.close();
                decode(filepath);
            }
            else
            {
                password = genPasswordFull(generateArg);
                for (auto i:password) passwordString.push_back(i);
                std::cout << "Password: " << passwordString << std::endl;
                entry << encode(passwordString);
                entry.close();
                decode(filepath);
            }
        }
        else if (symbolsArg)
        {
            password = genPasswordNoSymbol(30);
            for (auto i:password) passwordString.push_back(i);
            std::cout << "Password: " << passwordString << std::endl;
            entry << encode(passwordString);
            entry.close();
            decode(filepath);
        }
        else
        {
            password = genPasswordFull(30);
            for (auto i:password) passwordString.push_back(i);
            std::cout << "Password: " << passwordString << std::endl;
            entry << encode(passwordString);
            entry.close();
            decode(filepath);
        }
    }

    if (removeArg != "NULL")
    {
        std::cout << "you will remove: " << removeArg << std::endl;
    }
    return 0;
}
