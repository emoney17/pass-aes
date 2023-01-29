#include "init.hpp"

void generateFiles()
{
    std::filesystem::create_directories("temp");
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH];
    rng.GenerateBlock(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
    rng.GenerateBlock(iv, CryptoPP::AES::BLOCKSIZE);

    CryptoPP::ArraySource key_source((CryptoPP::byte*)&key, sizeof(key), true,
            new CryptoPP::FileSink("./temp/.key.aes"));

    CryptoPP::ArraySource data_source((CryptoPP::byte*)&iv, sizeof(iv), true,
            new CryptoPP::FileSink("./temp/.iv.aes"));
}
