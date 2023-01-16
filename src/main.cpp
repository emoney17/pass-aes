#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"

#include <iostream>
#include <fstream>
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
            std::cout << "Password: " << Password << std::endl;
            std::cout << "Data File: " << PassFile << std::endl;
            std::cout << "Key File: " << KeyFile << std::endl;
        }
};

// Function to generate a key along with iv
void genKey()
{
    using namespace CryptoPP;

    AutoSeededRandomPool prng;
    HexEncoder encoder(new CryptoPP::FileSink(std::cout));

    SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
    SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);

    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());

    std::cout << "key: ";
    encoder.Put(key, key.size());
    encoder.MessageEnd();
    std::cout << std::endl;

    std::cout << "iv: ";
    encoder.Put(iv, iv.size());
    encoder.MessageEnd();
    std::cout << std::endl;

    /*********************************\
    \*********************************/

    // Convert byte to string COMPLETE!
    std::string keyS;
    HexEncoder encodeS;
    encodeS.Attach(new StringSink(keyS));
    encodeS.Put(key.data(), key.size());
    encodeS.MessageEnd();
    // std::cout << "Decoded string key: " << keyS << std::endl;

    // Convert string hex to byte COMPLETE!
    // std::cout << "key raw: " << key.data() << std::endl;
    std::string destination;
    StringSource ss(keyS, true, new HexDecoder(new StringSink(destination)));
    const byte* result = (const byte*) destination.data();
    // std::cout << "Decoded byte key: " << result << std::endl;

    // Chec if can be written to file COMPLETE!
    std::ofstream testFile("./test/testFile");
    testFile << keyS << std::endl;
    testFile << result << std::endl;
    testFile.close();

    // Check if can be read from a file COMPLETE!
    std::string line1, line2;
    std::ifstream readTest("./test/testFile");
    std::getline(readTest, line1);
    std::getline(readTest, line2);
    // std::cout << "Line 1 from the file encoded: " << line1 << std::endl;
    // std::cout << "Line 2 from the file raw: " << line2 << std::endl;
    readTest.close();

    // Testing encryption

    std::string plain = "This is a cipher test.";
    std::string cipher, recovered;

    std::cout << "Plain text: " << plain << std::endl;

    try
    {
        CBC_Mode< AES >::Encryption e;
        e.SetKeyWithIV(result, 16, iv);

        StringSource s(plain, true,
            new StreamTransformationFilter(e,
                new StringSink(cipher)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch(const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    // Print out hexcode of encoded plain text
    std::cout << "cipher text: ";
    encoder.Put((const byte*)&cipher[0], cipher.size());
    encoder.MessageEnd();
    std::cout << std::endl;

    std::cout << "cipher text raw: " << cipher << std::endl;

    // Recover the text
    try
    {
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(result, 16, iv);

        StringSource s(cipher, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered)
            ) // StreamTransformationFilter
        ); // StringSource

        std::cout << "recovered text: " << recovered << std::endl;
    }
    catch(const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

// Move this to main
void printMenu()
{
    std::string menu = "___________________________________________\n"
                      "|                                          |\n"
                      "|          Entry to data GRANTED           |\n"
                      "|         1. View all passwords            |\n"
                      "|         2. Edit passwords                |\n"
                      "|         3. Add a password                |\n"
                      "|         4. Delete a password             |\n"
                      "|         5. Quit                          |\n"
                      "|__________________________________________|\n";
    std::cout << menu << std::endl;
}

// Move this to main
void printDashboard()
{
    std::string dashboard = "___________________________________________\n"
                           "|                                          |\n"
                           "|      Unlocking password database...      |\n"
                           "|__________________________________________|\n";
    std::cout << dashboard << std::endl;
}

int main (int argc, char *argv[])
{
    genKey();

    std::string userStatus;
    printDashboard();

    // Check if new user or old user
    std::cout << "If this is your first time running please type 'new'\n"
        "If not press 'Enter' to continue." << std::endl;
    std::getline(std::cin, userStatus, '\n');
    if (userStatus == "new")
    {
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

        std::cout << "Generating necessary files..." << std::endl;

        std::string newUserKeyFile = "./test/key";
        std::string newUserPassFile = "./test/pass";
        std::fstream keyFile, passFile;

        keyFile.open(newUserKeyFile, std::ios::out);
        if (!keyFile.is_open())
        {
            std::cout << "Error creating key file! Exiting!" << std::endl;
            return -1;
        }
        else std::cout << "Key file generated!" << std::endl;
        passFile.open(newUserPassFile, std::ios::out);
        if (!passFile.is_open())
        {
            std::cout << "Error creating pass file! Exiting!" << std::endl;
            return -1 ;
        }
        else std::cout << "Pass file generated!" << std::endl;
        std::cout << "Necessary files created. \n"
            "Please rename and save your pass file and key file somewhere safe!\n"
            "Also remember your password for this program!" << std::endl;
        User newUser(newUserPassword, newUserPassFile, newUserKeyFile);
        newUser.printInfo();
    }
    else if (userStatus.empty())
    {
        int userChoice;
        std::string loginPass, passPath, keyPath;

        std::cout << "Enter password: " << std::endl;
        std::cin >> loginPass;
        std::cout << "Enter password data path: " << std::endl;
        std::cin >> passPath;
        std::cout << "Enter your encryption key here: " << std::endl;
        std::cin >> keyPath;

        User oldUser(loginPass, passPath, keyPath);
        oldUser.printInfo();

        // Continue validation of all entered information
        std::cout << "Validating info..." << std::endl;
        std::cout << std::endl;

        // Check if password file exists
        std::ifstream passFile(passPath);
        if(!passFile.is_open())
        {
            std::cout << "The pass file does not exist." << std::endl;
            return -1;
        }

        // Check if key file exists
        std::ifstream keyFile(keyPath);
        if(!keyFile.is_open())
        {
            std::cout << "The key file does not exist." << std::endl;
            return -1;
        }

        // Read password entry from password file and check if correct
        // Decrypt the pass file with the users key file
        // Check if the password is correct
        // if not re-enter user information

        // Entry has been granted to the user
        while (userChoice != 5)
        {
            printMenu();
            std::cin >> userChoice;
            switch (userChoice)
            {
                case 1:
                    {
                        std::cout << "Viewing all stored passwords\n";
                        if(passFile.is_open()) std::cout << passFile.rdbuf();
                        break;
                    }
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
        "or just hit Enter to continue normally" << std::endl;
    return 0;
}
