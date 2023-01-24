#ifndef NEWUSER_H
#define NEWUSER_H

#include "cryptopp/cryptlib.h"
#include "cryptopp/filters.h"
#include "cryptopp/rijndael.h"
#include "cryptopp/modes.h"
#include "cryptopp/files.h"
#include "cryptopp/osrng.h"
#include "cryptopp/hex.h"

// #include <iostream>
// #include <string>
// #include <fstream>

std::string generateNewUser();

#endif // !#ifndef NEWUSER_H
