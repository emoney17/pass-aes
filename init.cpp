#include "init.hpp"
void generateFiles()
{
    // Random byte generator
    CryptoPP::AutoSeededRandomPool rng;

    // Hex encoder
    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

    // Generate key and iv
    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH];
    rng.GenerateBlock(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::byte iv[CryptoPP::AES::DEFAULT_KEYLENGTH];
    rng.GenerateBlock(iv, CryptoPP::AES::BLOCKSIZE);

    // Encoded key
    std::cout << "Key: ";
    encoder.Put(key, sizeof(key));
    encoder.MessageEnd();
    std::cout << std::endl;

    // Encoded iv
    std::cout << "Iv: ";
    encoder.Put(iv, sizeof(iv));
    encoder.MessageEnd();
    std::cout << std::endl;

    // Byte for recovered key
    CryptoPP::byte recovered_key[CryptoPP::AES::DEFAULT_KEYLENGTH];
    CryptoPP::byte recovered_iv[CryptoPP::AES::DEFAULT_KEYLENGTH];

    // Write key to key.aes file
    CryptoPP::ArraySource key_source((CryptoPP::byte*)&key, sizeof(key), true,
            new CryptoPP::FileSink("./temp/key.aes"));
    // Recover key from key.aes file. Put into recovered
    CryptoPP::FileSource key_file_source("./temp/key.aes", true,
            new CryptoPP::ArraySink((CryptoPP::byte*)&recovered_key,
                sizeof(recovered_key)));

    // Write data to data.aes file
    CryptoPP::ArraySource data_source((CryptoPP::byte*)&iv, sizeof(iv), true,
            new CryptoPP::FileSink("./temp/data.aes"));
    // Recover data from data.aes file. Put into recovered
    CryptoPP::FileSource data_file_source("./temp/data.aes", true,
            new CryptoPP::ArraySink((CryptoPP::byte*)&recovered_iv,
                sizeof(recovered_iv)));

    // Encoded key recovered
    std::cout << "Recovered Key: ";
    encoder.Put(recovered_key, sizeof(recovered_key));
    encoder.MessageEnd();
    std::cout << std::endl;

    // Encoded iv recovered
    std::cout << "Recovered Iv: ";
    encoder.Put(recovered_iv, sizeof(recovered_iv));
    encoder.MessageEnd();
    std::cout << std::endl;
}
