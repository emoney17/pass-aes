#include "gen.hpp"
#include <string>


std::string genPasswordFull(int length)
{
    int index;
    std::string password;
    srand(time(0));
    while (password.length() != length)
    {
        index = rand()%4;
        switch (index) {
            case 0:
                password.push_back(UPPERCASE[(rand()%(sizeof(UPPERCASE)))]);
                break;
            case 1:
                password.push_back(LOWERCASE[(rand()%(sizeof(LOWERCASE)))]);
                break;
            case 2:
                password.push_back(NUMBERS[(rand()%(sizeof(NUMBERS)))]);
                break;
            case 3:
                password.push_back(SYMBOLS[(rand()%(sizeof(SYMBOLS)))]);
                break;
        }
    }
    return password;
}

std::string genPasswordNoSymbol(int length)
{
    int index;
    std::string password;
    srand(time(0));
    while (password.length() != length)
    {
        index = rand()%3;
        switch (index) {
            case 0:
                password.push_back(UPPERCASE[(rand()%(sizeof(UPPERCASE)))]);
                break;
            case 1:
                password.push_back(LOWERCASE[(rand()%(sizeof(LOWERCASE)))]);
                break;
            case 2:
                password.push_back(NUMBERS[(rand()%(sizeof(NUMBERS)))]);
                break;
        }
    }
    return password;
}
