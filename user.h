#ifndef USER_H
#define USER_H

// #include <iostream>

#include "cryptopp/cryptlib.h"
#include "cryptopp/filters.h"
#include "cryptopp/rijndael.h"
#include "cryptopp/modes.h"
#include "cryptopp/files.h"
#include "cryptopp/osrng.h"
#include "cryptopp/hex.h"


class User
{
    private:

        std::string Password;
        std::string PassPath;
        std::string KeyPath;

    public:

        User(std::string password, std::string passPath, std::string keyPath);

        void readKeyFile(std::string keyFilePath, std::string* keyFromFile, std::string* ivFromFile);

        void printInfo();

        bool validateUser();
};

#endif // !USER_H
