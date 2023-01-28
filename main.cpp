#include "CLI11.hpp"
#include "init.hpp"
#include "gen.hpp"
#include "parse.hpp"
#include "encode.hpp"
#include "tree.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>

int main (int argc, char *argv[])
{
    CLI::App app{"App description"};

    std::vector<char> password;
    std::string passwordString;
    std::vector<std::string> vec;
    std::string directorypath = "temp/";
    std::string filepath = "temp/";

    bool initArg{false};
    bool symbolsArg{false};
    int generateArg = 0;
    std::string addArg = "NULL";
    std::string removeArg = "NULL";
    std::string viewArg = "NULL";

    app.add_option("-v,--view", viewArg,
            "Enter Subject/Entry to see specific password or enter 'all' to view full list");
    app.add_flag("-i,--init", initArg,
            "First time users generate necessary files");
    app.add_option("-g,--generate", generateArg,
            "Generate a password for an entry and pick the length size");
    app.add_flag("-s,--nosymbols", symbolsArg,
            "Generate a password with out special characters");
    app.add_option("-a,--add", addArg,
            "Add a new entry with the format 'Subject/Entry'");
    app.add_option("-r,--remove", removeArg,
            "Remove a Subject or Entry with the format 'Subject/Entry'");

    CLI11_PARSE(app, argc, argv);

    if (initArg)
    {
        generateFiles();
    }

    if (viewArg == "all")
    {
        tree("temp");
    }
    else
    {
        filepath.append(viewArg);
        decode(filepath);
    }

    if (addArg != "NULL")
    {
        vec = parse(addArg);
        directorypath.append(vec[0]);
        std::filesystem::create_directories(directorypath);
        filepath.append(vec[0]);
        filepath.append("/");
        filepath.append(vec[1]);
        std::ofstream entry(filepath);

        // TODO: Fix passwords not being proper length

        if (generateArg != 0)
        {
            if (symbolsArg) {
                password = genPasswordNoSymbol(generateArg);
                for (auto i:password) passwordString.push_back(i);
                std::cout << "Password: " << passwordString << std::endl;
                // entry << encode(passwordString);
                entry.close();
                // decode(filepath);
            }
            else
            {
                password = genPasswordFull(generateArg);
                for (auto i:password) passwordString.push_back(i);
                std::cout << "Password: " << passwordString << std::endl;
                // entry << encode(passwordString);
                entry.close();
                // decode(filepath);
            }
        }
        else if (symbolsArg)
        {
            password = genPasswordNoSymbol(30);
            for (auto i:password) passwordString.push_back(i);
            std::cout << "Password: " << passwordString << std::endl;
            // entry << encode(passwordString);
            entry.close();
            // decode(filepath);
        }
        else
        {
            password = genPasswordFull(30);
            for (auto i:password) passwordString.push_back(i);
            std::cout << "Password: " << passwordString << std::endl;
            // entry << encode(passwordString);
            entry.close();
            // decode(filepath);
        }
    }

    if (removeArg != "NULL")
    {
        filepath.append(removeArg);
        std::cout << filepath << std::endl;
        std::filesystem::remove_all(filepath);
        std::cout << "Entry " << filepath << " deleted" << std::endl;
    }
    return 0;
}
