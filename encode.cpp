#include "encode.hpp"

std::string encode(std::string password)
{
    std::string encodedPassword;

    // Byte for recovered key
    CryptoPP::byte recovered_key[CryptoPP::AES::DEFAULT_KEYLENGTH];
    CryptoPP::byte recovered_iv[CryptoPP::AES::BLOCKSIZE];

    // Recover key from key.aes file. Put into recovered
    CryptoPP::FileSource keySource("/temp/.key.aes", true,
            new CryptoPP::ArraySink((CryptoPP::byte*)&recovered_key,
                sizeof(recovered_key)));

    // Recover data from data.aes file. Put into recovered
    CryptoPP::FileSource ivSource("/temp/.iv.aes", true,
            new CryptoPP::ArraySink((CryptoPP::byte*)&recovered_iv,
                sizeof(recovered_iv)));

    // Use the keys to encrypt the password and write it to the file
    try
    {
        CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption e;
        e.SetKeyWithIV(recovered_key, sizeof(recovered_key), recovered_iv);

        CryptoPP::StringSource s(password, true,
            new CryptoPP::StreamTransformationFilter(e,
                new CryptoPP::StringSink(encodedPassword)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    std::cout << "Encoded password: " << encodedPassword << std::endl;

    // Write the encoded password to the file test
    CryptoPP::StringSource passwordSource(encodedPassword, true,
            new CryptoPP::FileSink("test"));

    return encodedPassword;
}

void decode(std::string path)
{
    std::string recoveredPassword, encodedPassword;
    // Byte for recovered key
    CryptoPP::byte recovered_key[CryptoPP::AES::DEFAULT_KEYLENGTH];
    CryptoPP::byte recovered_iv[CryptoPP::AES::BLOCKSIZE];

    // Recover key from key.aes file. Put into recovered
    CryptoPP::FileSource keySource("/temp/.key.aes", true,
            new CryptoPP::ArraySink((CryptoPP::byte*)&recovered_key,
                sizeof(recovered_key)));

    // Recover data from data.aes file. Put into recovered
    CryptoPP::FileSource ivSource("/temp/.iv.aes", true,
            new CryptoPP::ArraySink((CryptoPP::byte*)&recovered_iv,
                sizeof(recovered_iv)));

    // Recover the encrypted password from the file
    CryptoPP::FileSource passwordSource(path.c_str(), true,
            new CryptoPP::StringSink(encodedPassword));

    // Use the keys to decrypt the password on the file
    try
    {
        CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption d;
        d.SetKeyWithIV(recovered_key, sizeof(recovered_key), recovered_iv);

        CryptoPP::StringSource s(encodedPassword, true,
            new CryptoPP::StreamTransformationFilter(d,
                new CryptoPP::StringSink(recoveredPassword)
            ) // StreamTransformationFilter
        ); // StringSource

        std::cout << "Recovered password: " << recoveredPassword << std::endl;
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}
