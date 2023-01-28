#include "CLI11.hpp"
#include "init.hpp"
#include "gen.hpp"
#include "parse.hpp"
#include "encode.hpp"
#include "tree.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

void writePassword(std::vector<char> password, std::ofstream& entry)
{
    std::string passwordString;
    for (auto i:password) passwordString.push_back(i);
    std::cout << "Password: " << passwordString << std::endl;
    entry << encode(passwordString);
    entry.close();
}

int main (int argc, char *argv[])
{
    CLI::App app{"App description"};

    Tree tree;
    std::vector<char> password;
    std::string passwordString, encodedPassword;
    std::vector<std::string> path;
    std::string directorypath = "temp/";
    std::string filepath = "temp/";
    std::string directory, file;

    bool initArg{false};
    bool symbolsArg{false};
    int generateArg = 0;
    std::string viewArg = "NULL";
    std::string addArg = "NULL";
    std::string removeArg = "NULL";

    app.add_flag("-i,--init", initArg, "First time users generate necessary files");
    app.add_option("-v,--view", viewArg, "View all entries with 'all' or a specific entry with 'Subject/Entry'");
    app.add_option("-g,--generate", generateArg, "Generate a password when adding an entry and pick the length");
    app.add_flag("-s,--nosymbols", symbolsArg, "Generate a password with out special characters");
    app.add_option("-a,--add", addArg, "Add a new entry with the format 'Subject/Entry' and enter a password");
    app.add_option("-r,--remove", removeArg, "Remove a 'Subject/' or a 'Subject/Entry'");

    CLI11_PARSE(app, argc, argv);

    if (initArg) generateFiles();

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
        parse(addArg, &directory, &file);
        directorypath.append(directory);
        std::filesystem::create_directories(directorypath);
        filepath.append(addArg);
        std::ofstream entry(filepath);

        // TODO: Fix passwords not being proper length
        if (generateArg != 0)
        {
            if (symbolsArg) {
                password = genPasswordNoSymbol(generateArg);
                writePassword(password, entry);
                decode(filepath);
            }
            else
            {
                password = genPasswordFull(generateArg);
                writePassword(password, entry);
                decode(filepath);
            }
        }
        // else if (symbolsArg)
        // {
        //     password = genPasswordNoSymbol(30);
        //     writePassword(password, entry);
        //     decode(filepath);
        // }
        // else
        // {
        //     password = genPasswordFull(30);
        //     writePassword(password, entry);
        //     decode(filepath);
        // }
        // Let user manualy enter a password
        else
        {
            std::cout << "Enter password for this entry: ";
            std::getline(std::cin, passwordString);
            std::cout << "Password: " << passwordString << std::endl;
            entry << encode(passwordString);
            entry.close();
            decode(filepath);
        }
    }

    // TODO: Check if the directory or file even exists first
    if (removeArg != "NULL")
    {
        directorypath.append(removeArg);
        std::filesystem::remove_all(directorypath);
        std::cout << "Removed: " << directorypath << std::endl;
    }
    return 0;
}
