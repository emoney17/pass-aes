#ifndef ENCODE_HPP
#define ENCODE_HPP

#include "cryptopp/cryptlib.h"
#include "cryptopp/filters.h"
#include "cryptopp/rijndael.h"
#include "cryptopp/modes.h"
#include "cryptopp/files.h"
#include "cryptopp/osrng.h"
#include "cryptopp/hex.h"
#include <iostream>

std::string encode(std::string password);
void decode(std::string path);

#endif // !ENCODE_HPP
