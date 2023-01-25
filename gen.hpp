#include <iostream>
#include <random>
#include <vector>

const char UPPERCASE[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
const char LOWERCASE[] = {"abcdefghijklmnopqrstuvwxyz"};
const char SYMBOLS[] = {"[]{}()*&^%$#@!~"};

std::vector<char> genPasswordFull(int length);
std::vector<char> genPasswordNoSymbol(int length);
