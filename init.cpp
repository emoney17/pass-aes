#include "init.hpp"

void generateFiles()
{
    // Random byte generator
    CryptoPP::AutoSeededRandomPool rng;

    // Hex encoder
    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

    // Generate temp
    std::filesystem::create_directories("temp");
    // Generate key and iv
    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH];
    rng.GenerateBlock(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
    rng.GenerateBlock(iv, CryptoPP::AES::BLOCKSIZE);

    // Write key to key.aes file
    CryptoPP::ArraySource key_source((CryptoPP::byte*)&key, sizeof(key), true,
            new CryptoPP::FileSink("./temp/.key.aes"));

    // Write data to data.aes file
    CryptoPP::ArraySource data_source((CryptoPP::byte*)&iv, sizeof(iv), true,
            new CryptoPP::FileSink("./temp/.iv.aes"));
}
