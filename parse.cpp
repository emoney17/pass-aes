#include "parse.hpp"
#include <exception>

// TODO: Onyl really need the directory so remove  the file var from this
void parse (std::string s, std::string* directory, std::string* file)
{
    size_t pos_start = 0, pos_end;
    std::string token;
    std::vector<std::string> res;

    try
    {
        while ((pos_end = s.find ("/", pos_start)) != std::string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + 1;
            res.push_back (token);
        }
        res.push_back (s.substr (pos_start));
        *directory = res[0];
        *file = res[1];
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception caught:" << e.what() << std::endl;
        exit(1);
    }
}
