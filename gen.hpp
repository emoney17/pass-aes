#ifndef GEN_HPP
#define GEN_HPP

#include <iostream>
#include <random>
#include <string>
#include <vector>

const char UPPERCASE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char LOWERCASE[] = "abcdefghijklmnopqrstuvwxyz";
const char NUMBERS[] = "0123456789";
const char SYMBOLS[] = "~`!@#$%^&*()_-+={[}]|:;'<,>.?/";

std::string genPasswordFull(int length);
std::string genPasswordNoSymbol(int length);

#endif // !DEBUG
