#ifndef INIT_HPP
#define INIT_HPP

#include "cryptopp/cryptlib.h"
#include "cryptopp/filters.h"
#include "cryptopp/rijndael.h"
#include "cryptopp/modes.h"
#include "cryptopp/files.h"
#include "cryptopp/osrng.h"
#include "cryptopp/hex.h"
#include <filesystem>
#include <iostream>

void generateFiles();

#endif // !INIT_HPP
