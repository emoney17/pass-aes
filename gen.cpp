#include "gen.hpp"
#include <iostream>

std::vector<char> genPasswordFull(int length)
{
    srand(time(0));
    std::vector<char> password;
    while (int (password.size()) < length)
    {
        int index = rand() % 4;
        switch (index) {
            case 0: password.push_back(UPPERCASE[(rand()%sizeof(UPPERCASE))]);
                break;
            case 1: password.push_back(LOWERCASE[(rand()%sizeof(LOWERCASE))]);
                break;
            case 2: password.push_back(SYMBOLS[(rand()%sizeof(SYMBOLS))]);
                break;
            case 3: char c = (rand()%9)+'0'; password.push_back(c);
                break;
        }
    }
    for (auto i:password) std::cout << i;
    std::cout << std::endl;
    return password;
}

std::vector<char> genPasswordNoSymbol(int length = 30)
{
    srand(time(0));
    std::vector<char> password;
    while (int (password.size()) < length)
    {
        int index = rand() % 3;
        switch (index) {
            case 0: password.push_back(UPPERCASE[(rand()%sizeof(UPPERCASE))]);
                break;
            case 1: password.push_back(LOWERCASE[(rand()%sizeof(LOWERCASE))]);
                break;
            case 2: char c = (rand()%9)+'0'; password.push_back(c);
                break;
        }
    }
    for (auto i:password) std::cout << i;
    std::cout << std::endl;
    return password;
}
