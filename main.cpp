#include "CLI11.hpp"
#include "init.hpp"
#include "gen.hpp"
#include "parse.hpp"
#include "encode.hpp"
#include "tree.hpp"

#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>


int main (int argc, char *argv[])
{
    CLI::App app{"App description"};

    Tree tree;
    std::string password;
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

    if (std::filesystem::exists("temp/"))
    {
        // VIEW
        if (viewArg == "all")
        {
            std::cout << "temp" << std::endl;
            tree.walk("temp", " ");
            tree.summary();
        }
        else if (viewArg != "NULL")
        {
            filepath.append(viewArg);
            if (countDelimiter(viewArg) && std::filesystem::exists(filepath))
            {
                decode(filepath);
            }
            else std::cout << "Wrong format or entry does not exist" << std:: endl;
        }

        // ADD
        if (addArg != "NULL")
        {
            if (countDelimiter(addArg))
            {
                parse(addArg, &directory, &file);
                if (file.size() != 0)
                {
                    directorypath.append(directory);
                    std::filesystem::create_directories(directorypath);
                    filepath.append(addArg);
                    std::ofstream entry(filepath);

                    // TODO: Fix passwords not being proper length
                    if (generateArg != 0)
                    {
                        if (symbolsArg)
                        {
                            password = genPasswordNoSymbol(generateArg);
                            entry << encode(password);
                            entry.close();
                        }
                        else
                        {
                            password = genPasswordFull(generateArg);
                            entry << encode(password);
                            entry.close();
                        }
                    }
                    else
                    {
                        std::cout << "Enter password for this entry: ";
                        std::getline(std::cin, passwordString);
                        std::cout << "Password: " << passwordString << std::endl;
                        entry << encode(passwordString);
                        entry.close();
                    }
                }
                else std::cout << "Wrong format" << std::endl;
            }
            else std::cout << "Wrong format" << std::endl;
        }

        // REMOVE
        if (removeArg != "NULL")
        {
            if (countDelimiter(removeArg) && std::filesystem::exists(directorypath))
            {
                std::filesystem::remove_all(directorypath);
                std::cout << "Removed: " << directorypath << std::endl;
            }
            else std::cout << "Wrong format or path does not exist" << std::endl;
        }
    }
    else std::cout << "You have not initialized yet" << std::endl;
    return 0;
}
