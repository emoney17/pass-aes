#include "cryptopp/cryptlib.h"
#include "cryptopp/filters.h"
#include "cryptopp/rijndael.h"
#include "cryptopp/modes.h"
#include "cryptopp/files.h"
#include "cryptopp/osrng.h"
#include "cryptopp/hex.h"

#include <iostream>

int main (int argc, char *argv[])
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

    std::cout << "Key: ";
    encoder.Put(key, sizeof(key));
    encoder.MessageEnd();
    std::cout << std::endl;

    std::cout << "Iv: ";
    encoder.Put(iv, sizeof(iv));
    encoder.MessageEnd();
    std::cout << std::endl;

    // Byte for recovered key
    CryptoPP::byte recovered_key[CryptoPP::AES::DEFAULT_KEYLENGTH];
    CryptoPP::byte recovered_iv[CryptoPP::AES::DEFAULT_KEYLENGTH];

    // Write key to key.aes file
    CryptoPP::ArraySource key_source((CryptoPP::byte*)&key, sizeof(key), true,
            new CryptoPP::FileSink("./key.aes"));
    // Recover key from key.aes file. Put into recovered
    CryptoPP::FileSource key_file_source("./key.aes", true,
            new CryptoPP::ArraySink((CryptoPP::byte*)&recovered_key,
                sizeof(recovered_key)));

    // Write data to data.aes file
    CryptoPP::ArraySource data_source((CryptoPP::byte*)&iv, sizeof(iv), true,
            new CryptoPP::FileSink("./data.aes"));
    // Recover data from data.aes file. Put into recovered
    CryptoPP::FileSource data_file_source("./data.aes", true,
            new CryptoPP::ArraySink((CryptoPP::byte*)&recovered_iv,
                sizeof(recovered_iv)));

    std::cout << "Recovered Key: ";
    encoder.Put(recovered_key, sizeof(recovered_key));
    encoder.MessageEnd();
    std::cout << std::endl;

    std::cout << "Recovered Iv: ";
    encoder.Put(recovered_iv, sizeof(recovered_iv));
    encoder.MessageEnd();
    std::cout << std::endl;

    return 0;
}
