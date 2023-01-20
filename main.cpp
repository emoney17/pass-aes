#include "cryptopp/cryptlib.h"
#include "cryptopp/rijndael.h"
#include "cryptopp/modes.h"
#include "cryptopp/files.h"
#include "cryptopp/osrng.h"
#include "cryptopp/hex.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

class User
{
    private:
        std::string Password;
        std::string PassFile;
        std::string KeyFile;

    public:
        // Constructor for user
        User(std::string password, std::string passfile, std::string keyfile)
        {
            Password = password;
            PassFile = passfile;
            KeyFile = keyfile;
        }

        // Print info for debugging
        void printInfo()
        {
            std::cout << std::endl;
            std::cout << "Password: " << Password << std::endl;
            std::cout << "Data File: " << PassFile << std::endl;
            std::cout << "Key File: " << KeyFile << std::endl;
            std::cout << std::endl;
        }
};

void generatePassFile(std::string password)
{
    // Read the bytes from the file to strings
    std::string keyFromFile, ivFromFile, cipher, recovered;
    std::ifstream readKeyFile("./test/key");
    std::getline(readKeyFile, keyFromFile);
    std::getline(readKeyFile, ivFromFile);
    readKeyFile.close();

    //convert tokens read from the file to bytes
    const CryptoPP::byte* key = (const CryptoPP::byte*) keyFromFile.data();
    const CryptoPP::byte* iv = (const CryptoPP::byte*) ivFromFile.data();

    // test encryption
    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

    try
    {
        CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption e;
        e.SetKeyWithIV(key, 16, iv);

        CryptoPP::StringSource s(password, true,
        new CryptoPP::StreamTransformationFilter(e,
        new CryptoPP::StringSink(cipher)
            )
        );
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    // std::cout << "Cipher raw: " << cipher << std::endl;

    std::ofstream passFile("./test/pass");
    passFile << cipher;
    passFile.close();

    try
    {
        CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption d;
        d.SetKeyWithIV(key, 16, iv);

        CryptoPP::StringSource s(cipher, true,
            new CryptoPP::StreamTransformationFilter(d,
                new CryptoPP::StringSink(recovered)
            ) // StreamTransformationFilter
        ); // StringSource

        std::cout << "recovered text: " << recovered << std::endl;
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

void generateKeyFile()
{
    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

    CryptoPP::byte key[16];
    CryptoPP::byte iv[16];

    CryptoPP::OS_GenerateRandomBlock(false, key, sizeof(key));
    CryptoPP::OS_GenerateRandomBlock(false, iv, sizeof(iv));

    std::ofstream keyFile("./test/key");
    keyFile << key;
    keyFile << std::endl;
    keyFile << iv;
    keyFile.close();
}

int encrypt(std::string keyFilePath, std::string passFilePath)
{
    // Read the bytes from the file to strings
    std::string keyFromFile, ivFromFile;
    std::ifstream readKeyFile(keyFilePath);
    std::getline(readKeyFile, keyFromFile);
    std::getline(readKeyFile, ivFromFile);
    readKeyFile.close();

    //convert tokens read from the file to bytes
    const CryptoPP::byte* key = (const CryptoPP::byte*) keyFromFile.data();
    const CryptoPP::byte* iv = (const CryptoPP::byte*) ivFromFile.data();

    // test encryption
    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

    // stream to read each line of the file
    std::string line, cipher;
    std::ifstream readPassFile(passFilePath);
    std::ofstream writePassFile("./test/passwrite.bak");
    if (!readPassFile.is_open()) std::cout << "Could not open " << passFilePath << "." << std::endl;
    else
    {
        while(std::getline(readPassFile, line))
        {
            std::cout << line << std::endl;
            line.append("\n");
            try
            {
                CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption e;
                e.SetKeyWithIV(key, 16, iv);

                CryptoPP::StringSource s(line, true,
                new CryptoPP::StreamTransformationFilter(e,
                new CryptoPP::StringSink(cipher)
                    )
                );
            }
            catch(const CryptoPP::Exception& e)
            {
                std::cerr << e.what() << std::endl;
                exit(1);
            }
            writePassFile << cipher;
        }
    }
    return 0;
}

void decrypt(std::string keyFilePath, std::string passFilePath)
{
    // read key and iv from key file
    std::string keyFromFile, ivFromFile;
    std::ifstream readKeyFile(keyFilePath);
    std::getline(readKeyFile, keyFromFile);
    std::getline(readKeyFile, ivFromFile);
    readKeyFile.close();

    // convert tokens read from the file to bytes
    const CryptoPP::byte* key = (const CryptoPP::byte*) keyFromFile.data();
    const CryptoPP::byte* iv = (const CryptoPP::byte*) ivFromFile.data();

    // test decryption
    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

    std::string cipher, recovered;
    std::ifstream readPassFile(passFilePath);
    if (!readPassFile.is_open()) std::cout << "Could not open " << passFilePath << "." << std::endl;
    else
    {
        while(std::getline(readPassFile, cipher))
        {
            // std::cout << cipher << std::endl;
            try
            {
                CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption d;
                d.SetKeyWithIV(key, 16, iv);

                CryptoPP::StringSource s(cipher, true,
                new CryptoPP::StreamTransformationFilter(d,
                new CryptoPP::StringSink(recovered)
                    )
                );
                std::cout << "recovered text: " << recovered << std::endl;
            }
            catch(const CryptoPP::Exception& e)
            {
                std::cerr << e.what() << std::endl;
                exit(1);
            }
        }
    }
}

bool validateUserPass(std::string loginPass, std::string keyFilePath, std::string passFilePath)
{
    std::string keyFromFile, ivFromFile;
    std::ifstream readKeyFile(keyFilePath);
    std::getline(readKeyFile, keyFromFile);
    std::getline(readKeyFile, ivFromFile);
    readKeyFile.close();

    // convert tokens read from the file to bytes
    const CryptoPP::byte* key = (const CryptoPP::byte*) keyFromFile.data();
    const CryptoPP::byte* iv = (const CryptoPP::byte*) ivFromFile.data();

    std::string encryptedPass, recoveredPass;
    std::ifstream readPassFile(passFilePath);
    if (!readPassFile.is_open()) std::cout << "Could not open " << passFilePath << "." << std::endl;
    else
    {
        // read the first line of the pass file where the login password is stored
        std::getline(readPassFile, encryptedPass);
        try
        {
            CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption d;
            d.SetKeyWithIV(key, 16, iv);

            CryptoPP::StringSource s(encryptedPass, true,
            new CryptoPP::StreamTransformationFilter(d,
            new CryptoPP::StringSink(recoveredPass)
                )
            );
            std::cout << "recovered password: " << recoveredPass << std::endl;
        }
        catch(const CryptoPP::Exception& e)
        {
            std::cerr << e.what() << std::endl;
            exit(1);
        }
    }
    return (loginPass == recoveredPass);
}

int main (int argc, char *argv[])
{
    std::string userStatus;
    std::cout << "UNLOCKING DATABASE..." << std::endl;

    // Check if new user or old user
    std::cout << "If this is your first time running please type 'new'\n"
        "If not press 'Enter' to continue." << std::endl;
    std::getline(std::cin, userStatus, '\n');

    // Run new user initialization
    if (userStatus == "new")
    {
        // Get users password
        std::string newUserPassword, newUserPasswordCheck;
        std::cout << "Starting new user process..." << std::endl;
        while (true)
        {
            std::cout << "Please select a password for this account: " << std::endl;
            std::cin >> newUserPassword;
            std::cout << "Enter the same password again: " << std::endl;
            std::cin >> newUserPasswordCheck;
            if (newUserPassword != newUserPasswordCheck)
                std::cout << "The passwords you entered are not the same, please try again." << std::endl;
            else break;
        }

        // Generate new users key and pass files
        std::cout << "Generating necessary files..." << std::endl;
        generateKeyFile();
        std::cout << "Key file generated!" << std::endl;
        generatePassFile(newUserPassword);
        std::cout << "Pass file generated!" << std::endl;
        std::cout << "Please save your pass file and key file somewhere safe!" << std::endl;
        User newUser(newUserPassword, "./test/pass", "./test/key");
        newUser.printInfo();
    }

    // Get old user information
    else if (userStatus.empty())
    {
        int userChoice;
        std::string loginPass, passPath, keyPath;

        while (true)
        {
            while (true)
            {
                // Get user info and validate files exist
                std::cout << "Enter password: " << std::endl;
                std::cin >> loginPass;
                std::cout << "Enter password data path: " << std::endl;
                std::cin >> passPath;
                std::cout << "Enter your encryption key here: " << std::endl;
                std::cin >> keyPath;

                std::ifstream validatePass(passPath);
                std::ifstream validateKey(keyPath);
                if (!validatePass.good()) std::cout << "Could not open " << passPath << "." << std::endl;
                else if (!validateKey.good()) std::cout << "Could not open " << keyPath << "." << std::endl;
                else break;
            }
            if (validateUserPass(loginPass, keyPath, passPath) == true) break;
            else std::cout << "The pass word for this data does not match." << std::endl;
        }

        User oldUser(loginPass, passPath, keyPath);
        oldUser.printInfo();

        // Read password entry from password file and check if correct
        // Decrypt the pass file with the users key file
        // Check if the password is correct
        // if not re-enter user information

        // Entry has been granted to the user
        while (userChoice != 5)
        {
            std::cout << "This is a menu 1. 2. 3. " << std::endl;
            std::cin >> userChoice;
            switch (userChoice)
            {
                case 1: std::cout << "Viewing all stored passwords\n";
                     break;
                case 2: std::cout << "Editing existing passwords\n";
                    break;
                case 3: std::cout << "Adding a new password\n";
                    break;
                case 4: std::cout << "Deleting an existing password\n";
                    break;
                case 5: std::cout << "Qitting the program..." << std::endl;
                    break;
                default: std::cout << "Please enter a valid option from the menu." << std::endl;
            }
        }
    }
    else std::cout << "Invalid option selected, either type 'new' for new user"
        "or just hit Enter to continue normally." << std::endl;
    return 0;
}
