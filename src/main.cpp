#include "tclap/SwitchArg.h"
#include "tclap/CmdLine.h"

#include <iostream>
#include <filesystem>

std::vector<std::string> split (std::string s) {
    std::string delimiter = "/";
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void print()
{
    std::cout << "Hello world!\n";
}

// The only flags we need are for insert entry, generate password, and remove
// entry. Flagless will be showing the directory tree and showing the
// password for an entry.
int main (int argc, char *argv[])
{
    try
    {
        TCLAP::CmdLine cmd("Command description message", ' ', "0.0.0");

        // Bool options is if it is required, then default option and data type
        TCLAP::SwitchArg generate("g", "generate", "Generate basic files",
                cmd, false);

        TCLAP::ValueArg<std::string> insertArg("i", "insert", "Subject/Entry to add",
                false, "NULL", "string");
        cmd.add(insertArg);

        TCLAP::ValueArg<std::string> removeArg("r", "remove", "Subject/Entry to remove",
                false, "NULL", "string");
        cmd.add(removeArg);
        cmd.parse(argc, argv);

        std::string insertPath = insertArg.getValue();
        std::string removePath = removeArg.getValue();
        bool generateOps = generate.getValue();

        if (generateOps)
        {
            std::filesystem::create_directory("temp");
        }
        if (insertPath != "NULL")
        {
            std::cout << "Inserting new entry for: " << insertPath << std::endl;
        }
        if ( removePath!= "NULL")
        {
            std::cout << "Inserting new entry for: " << insertPath << std::endl;
        }

    }
    catch (TCLAP::ArgException &e)
    {
        std::cerr << "error: " << e.error() << " for arg "
            << e.argId() << std::endl;
    }
    return 0;
}

// int main (int argc, char *argv[])
// {
//     std::string entry, dir, name;
//     std::cout << "Subject/Name: " << std::endl;
//     std::getline(std::cin, entry);
//     std::vector<std::string> v = split(entry, "/");
//     for (auto i:v) std::cout << i << std::endl;
//     return 0;
// }
