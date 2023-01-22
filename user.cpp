#include "cryptopp/cryptlib.h"
#include "cryptopp/filters.h"
#include "cryptopp/rijndael.h"
#include "cryptopp/modes.h"
#include "cryptopp/files.h"
#include "cryptopp/osrng.h"
#include "cryptopp/hex.h"

#include <fstream>
#include <iostream>
#include <string>

CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

void readKeyFile(std::string keyFilePath, std::string* keyFromFile, std::string* ivFromFile)
{
    // Read first 16 bytes and save to string then skip the first and read the second 16 etc.
    std::string data;
    CryptoPP::FileSource readKeyFile(keyFilePath.c_str(), false, new CryptoPP::StringSink(data));
    readKeyFile.Pump(16);
    *keyFromFile = data;
    data.clear();
    std::cout << "Key from file: " << *keyFromFile << std::endl;
    readKeyFile.PumpAll();
    *ivFromFile = data;
    std::cout << "IV from file: " << *ivFromFile << std::endl;
}


class User
{
    private:
        std::string Password;
        std::string PassPath;
        std::string KeyPath;
    public:
        User(std::string password, std::string passPath, std::string keyPath)
        {
            Password = password;
            PassPath = passPath;
            KeyPath = keyPath;
        }

        void printInfo()
        {
            std::cout << "User password: " << Password << std::endl;
            std::cout << "User Pass location: " << PassPath << std::endl;
            std::cout << "User Key location: " << KeyPath << std::endl;
        }

        bool validateUser() // Function to check if users password is the same as the pass files
        {
            std::string keyFromFile, ivFromFile, encryptedPassword, recoveredPassword;
            readKeyFile(KeyPath, &keyFromFile, &ivFromFile);
            const CryptoPP::byte* key = (const CryptoPP::byte*) keyFromFile.data();
            const CryptoPP::byte* iv = (const CryptoPP::byte*) ivFromFile.data();

            // Read first 16 bytes of pass file where password is located
            CryptoPP::FileSource readPassFile(PassPath.c_str(), true, new CryptoPP::StringSink(encryptedPassword));
            // readPassFile.Pump(16);
            std::cout << "From Filesource: " << encryptedPassword << std::endl;
            std::cout << "Size of filesource password: " << encryptedPassword.size() << std::endl;
            try
            {
                CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption d;
                d.SetKeyWithIV(key, 16, iv);

                CryptoPP::StringSource s(encryptedPassword, true,
                    new CryptoPP::StreamTransformationFilter(d,
                     new CryptoPP::StringSink(recoveredPassword)
                    )
                );

                std::cout << "Recovered password: " << recoveredPassword << std::endl;
            }
            catch(const CryptoPP::Exception& e)
            {
                std::cerr << e.what() << std::endl;
                exit(1);
            }

            return (Password == recoveredPassword);
        }

        void add() // Function to add an entry to the pass file
        {
            std::string entry,entryEncrypted, keyFromFile, ivFromFile;
            readKeyFile(KeyPath, &keyFromFile, &ivFromFile);
            const CryptoPP::byte* key = (const CryptoPP::byte*) keyFromFile.data();
            const CryptoPP::byte* iv = (const CryptoPP::byte*) ivFromFile.data();

            std::cout << "Entry: ";
            std::getline(std::cin, entry);
            // std::cout << "You are adding " << entry << " to the pass file." << std::endl;
            try
            {
                CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption e;
                e.SetKeyWithIV(key, 16, iv);

                CryptoPP::StringSource s(entry, true,
                new CryptoPP::StreamTransformationFilter(e,
                new CryptoPP::StringSink(entryEncrypted)
                    )
                );
            }
            catch(const CryptoPP::Exception& e)
            {
                std::cerr << e.what() << std::endl;
                exit(1);
            }

        }
};

std::string generateNewUser()
{
    std::string newUserPassword, newUserPasswordCheck, newUserPasswordEncrypted;
    // Get a password from the new user
    while (true)
    {
        std::cout << "Please enter a password: ";
        std::cin >> newUserPassword;
        std::cout << "Re-enter your password: ";
        std::cin >> newUserPasswordCheck;
        if (newUserPassword == newUserPasswordCheck)
        {
            std::cout << "Password saved." << std::endl;
            break;
        }
        else std::cout << "The passwords do not match." << std::endl;
    }

    // Generate key file for the new user
    CryptoPP::byte key[16];
    CryptoPP::byte iv[16];

    CryptoPP::OS_GenerateRandomBlock(false, key, sizeof(key));
    CryptoPP::OS_GenerateRandomBlock(false, iv, sizeof(iv));

    // Test writing to file using StringSource
    // CryptoPP::StringSource keyFile(key, 16, true, new CryptoPP::FileSink("key"));
    // CryptoPP::StringSource ivFile(iv, 16, true, new CryptoPP::FileSink("key"));

    std::ofstream keyFile("key", std::ios::binary);
    keyFile << key << iv;
    keyFile.close();

    // Generate pass file for the new user using their password
    try
    {
        CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption e;
        e.SetKeyWithIV(key, 16, iv);

        CryptoPP::StringSource s(newUserPassword, true,
        new CryptoPP::StreamTransformationFilter(e,
        new CryptoPP::StringSink(newUserPasswordEncrypted)
            )
        );
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    std::cout << "Password raw: " << newUserPasswordEncrypted << std::endl;
    std::cout << "Size of password raw: " << newUserPasswordEncrypted.size() << std::endl;

    // Write the encrypted password to the file using StringSource
    // CryptoPP::StringSource writePassword(newUserPasswordEncrypted, true, new CryptoPP::FileSink("pass"));

    // Write the encrypted password to the file normally
    std::ofstream passFile("pass", std::ios::binary);
    passFile << newUserPasswordEncrypted;
    passFile.close();

    // Try and recover the password from the pass file
    std::string recoveredPassword;
    try
    {
        CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption d;
        d.SetKeyWithIV(key, 16, iv);

        CryptoPP::StringSource s(newUserPasswordEncrypted, true,
            new CryptoPP::StreamTransformationFilter(d,
             new CryptoPP::StringSink(recoveredPassword)
            )
        );

        std::cout << "Recovered password: " << recoveredPassword << std::endl;
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    return newUserPassword;
}

int main()
{
    // This is for when generating a new user
    std::string password = generateNewUser();
    // std::cout << "New user info:\n"
    //     "Password: " << password << "\n"
    //     "Pass File: pass\n"
    //     "Key File: key\n";
    //
    User user("123", "pass", "key");
    // user.printInfo();
    std::cout << user.validateUser() << std::endl;
    // user.add();
}
