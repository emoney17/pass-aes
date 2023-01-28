#include "CLI11.hpp"
#include "init.hpp"
#include "gen.hpp"
#include "parse.hpp"
#include "encode.hpp"
#include "tree.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

int main (int argc, char *argv[])
{
    CLI::App app{"App description"};

    Tree tree;
    std::vector<char> password;
    std::string passwordString = "";
    std::vector<std::string> path;
    std::string directorypath = "temp/";
    std::string filepath = "temp/";

    bool initArg{false};
    bool symbolsArg{false};
    int generateArg = 0;
    std::string viewArg = "NULL";
    std::string addArg = "NULL";
    std::string removeArg = "NULL";

    app.add_flag("-i,--init", initArg,
            "First time users generate necessary files");
    app.add_option("-v,--view", viewArg,
            "View all entries with 'all' or a specific entry with 'Subject/Entry'");
    app.add_option("-g,--generate", generateArg,
            "Generate a password for an entry and pick the length size");
    app.add_flag("-s,--nosymbols", symbolsArg,
            "Generate a password with out special characters");
    app.add_option("-a,--add", addArg,
            "Add a new entry with the format 'Subject/Entry'");
    app.add_option("-r,--remove", removeArg,
            "Remove an entry with the format 'Subject/Entry'");

    CLI11_PARSE(app, argc, argv);

    // TODO: Make option for decoding and viewing entries

    if (initArg)
    {
        generateFiles();
    }

    if (viewArg == "all")
    {
        std::cout << "temp" << std::endl;
        tree.walk("temp", " ");
        tree.summary();
    }
    else if (viewArg != "NULL")
    {
        filepath.append(viewArg);
        decode(filepath);
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

        // TODO: Fix passwords not being proper length

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

    // TODO: Finish removeArg flag

    if (removeArg != "NULL")
    {
        std::cout << "you will remove: " << removeArg << std::endl;
    }
    return 0;
}
