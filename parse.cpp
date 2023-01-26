#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> parse (std::string s)
{
    std::vector<std::string> result;
    size_t pos = 0;
    std::string token;
    std::string delimiter = "/";
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        std::cout << token << std::endl;
        s.erase(0, pos + delimiter.length());
    }
    result.push_back(s);
    // for (auto i:result) std::cout << i << std::endl;
    return result;
}
