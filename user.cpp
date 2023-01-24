#include "user.h"

User::User(std::string password, std::string passPath, std::string keyPath)
{
    Password = password;
    PassPath = passPath;
    KeyPath = keyPath;
}

void User::readKeyFile(std::string keyFilePath, std::string* keyFromFile, std::string* ivFromFile)
{
    std::string data;
    CryptoPP::FileSource readKeyFile(keyFilePath.c_str(), false, new CryptoPP::StringSink(data));
    readKeyFile.Pump(16);
    *keyFromFile = data;
    data.clear();
    readKeyFile.PumpAll();
    *ivFromFile = data;
}

void User::printInfo()
{
    std::cout << "User password: " << Password << std::endl;
    std::cout << "User Pass location: " << PassPath << std::endl;
    std::cout << "User Key location: " << KeyPath << std::endl;
}

bool User::validateUser()
{
    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

    std::string keyFromFile, ivFromFile, encryptedPassword, recoveredPassword;
    readKeyFile(KeyPath, &keyFromFile, &ivFromFile);
    const CryptoPP::byte* key = (const CryptoPP::byte*) keyFromFile.data();
    const CryptoPP::byte* iv = (const CryptoPP::byte*) ivFromFile.data();

    CryptoPP::FileSource readPassFile(PassPath.c_str(), false,
            new CryptoPP::StringSink(encryptedPassword));
    readPassFile.Pump(16);

    // std::cout << "Raw: ";
    // encoder.Put((const CryptoPP::byte*)&encryptedPassword[0], encryptedPassword.size());
    // encoder.MessageEnd();
    // std::cout << std::endl;

    // std::cout << "Size of filesource password: " << encryptedPassword.size() << std::endl;

    try
    {
        CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption d;
        d.SetKeyWithIV(key, 16, iv);

        CryptoPP::StringSource s(encryptedPassword, true,
            new CryptoPP::StreamTransformationFilter(d,
             new CryptoPP::StringSink(recoveredPassword)
            )
        );
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    // std::cout << "Recovered password: " << recoveredPassword << std::endl;
    return (Password == recoveredPassword);
}
// int main()
// {
//     // This is for when generating a new user
//     std::string password = generateNewUser();
//     // std::cout << "New user info:\n"
//     //     "Password: " << password << "\n"
//     //     "Pass File: pass\n"
//     //     "Key File: key\n";
//     //
//     User user("123", "pass", "key"); // Set this after user enters flag for password and file paths
//     user.printInfo();
//     std::cout << user.validateUser() << std::endl;
// }
