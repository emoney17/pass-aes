#include "newUser.h"


std::string generateNewUser()
{
    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
    std::string newUserPassword, newUserPasswordCheck, newUserPasswordEncrypted;
    // Get a password from the new user
    while (true)
    {
        std::cout << "Please enter a password: ";
        std::getline(std::cin, newUserPassword);
        // std::cin >> newUserPassword;
        std::cout << "Re-enter your password: ";
        std::getline(std::cin, newUserPasswordCheck);
        // std::cin >> newUserPasswordCheck;
        if (newUserPassword == newUserPasswordCheck) break;
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

    // std::cout << "Raw: ";
    // encoder.Put((const CryptoPP::byte*)&newUserPasswordEncrypted[0], newUserPasswordEncrypted.size());
    // encoder.MessageEnd();
    // std::cout << std::endl;

    // std::cout << "Password raw: " << newUserPasswordEncrypted << std::endl;
    // std::cout << "Size of password raw: " << newUserPasswordEncrypted.size() << std::endl;

    // Write the encrypted password to the file using StringSource
    // CryptoPP::StringSource writePassword(newUserPasswordEncrypted, true, new CryptoPP::FileSink("pass"));

    // Write the encrypted password to the file normally
    std::ofstream passFile("pass", std::ios::binary);
    passFile << newUserPasswordEncrypted;
    passFile.close();

    // Try and recover the password from the pass file
    // std::string recoveredPassword;
    // try
    // {
    //     CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption d;
    //     d.SetKeyWithIV(key, 16, iv);
    //
    //     CryptoPP::StringSource s(newUserPasswordEncrypted, true,
    //         new CryptoPP::StreamTransformationFilter(d,
    //          new CryptoPP::StringSink(recoveredPassword)
    //         )
    //     );
    //
    //     // std::cout << "Recovered password: " << recoveredPassword << std::endl;
    // }
    // catch(const CryptoPP::Exception& e)
    // {
    //     std::cerr << e.what() << std::endl;
    //     exit(1);
    // }
    return newUserPassword;
}

