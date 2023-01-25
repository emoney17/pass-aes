#include "CLI11.hpp"
#include "gen.h"
#include <iostream>
#include <filesystem>

int main (int argc, char *argv[])
{
    CLI::App app{"App description"};

    bool generateArg{false};
    std::string insertArg = "NULL";
    std::string removeArg = "NULL";

    app.add_flag("-g,--generate", generateArg, "Generate basic files");
    app.add_option("-i,--insert", insertArg, "Insert new Subject/Entry");
    app.add_option("-r,--remove", removeArg, "Remove a Subjecy/Entry");


    CLI11_PARSE(app, argc, argv);

    if (generateArg)
    {
        std::filesystem::create_directories("temp");
        generateFiles();
    }
    if (insertArg != "NULL")
    {
        std::cout << "you will insert: " << insertArg << std::endl;
    }
    if (removeArg != "NULL")
    {
        std::cout << "you will remove: " << removeArg << std::endl;
    }
    return 0;
}
