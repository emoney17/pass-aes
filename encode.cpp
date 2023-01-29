#include "encode.hpp"

std::string encode(std::string password)
{
    std::string encodedPassword;
    CryptoPP::byte recovered_key[CryptoPP::AES::DEFAULT_KEYLENGTH];
    CryptoPP::byte recovered_iv[CryptoPP::AES::BLOCKSIZE];

    try
    {
        CryptoPP::FileSource keySource("./temp/.key.aes", true,
                new CryptoPP::ArraySink((CryptoPP::byte*)&recovered_key,
                    sizeof(recovered_key)));

        CryptoPP::FileSource ivSource("./temp/.iv.aes", true,
                new CryptoPP::ArraySink((CryptoPP::byte*)&recovered_iv,
                    sizeof(recovered_iv)));
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    try
    {
        CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption e;
        e.SetKeyWithIV(recovered_key, sizeof(recovered_key), recovered_iv);

        CryptoPP::StringSource s(password, true,
            new CryptoPP::StreamTransformationFilter(e,
                new CryptoPP::StringSink(encodedPassword)));
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    // std::cout << "Encoded password: " << encodedPassword << std::endl;

    return encodedPassword;
}

void decode(std::string path)
{
    std::string recoveredPassword, encodedPassword;
    CryptoPP::byte recovered_key[CryptoPP::AES::DEFAULT_KEYLENGTH];
    CryptoPP::byte recovered_iv[CryptoPP::AES::BLOCKSIZE];

    try
    {
        CryptoPP::FileSource keySource("./temp/.key.aes", true,
                new CryptoPP::ArraySink((CryptoPP::byte*)&recovered_key,
                    sizeof(recovered_key)));

        CryptoPP::FileSource ivSource("./temp/.iv.aes", true,
                new CryptoPP::ArraySink((CryptoPP::byte*)&recovered_iv,
                    sizeof(recovered_iv)));

        CryptoPP::FileSource passwordSource(path.c_str(), true,
                new CryptoPP::StringSink(encodedPassword));
    }
    catch(CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    try
    {
        CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption d;
        d.SetKeyWithIV(recovered_key, sizeof(recovered_key), recovered_iv);

        CryptoPP::StringSource s(encodedPassword, true,
            new CryptoPP::StreamTransformationFilter(d,
                new CryptoPP::StringSink(recoveredPassword)));

        std::cout << "Recovered password: " << recoveredPassword << std::endl;
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}
