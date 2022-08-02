/*
    Programmer: Jerusalem Moore
    Class: PasswordProcessor
    Data: 7/13/2022
    Description:
        Class for providing password salting/hashing and evaluation functions, currently the
        relationship to class and openssl EVP context is 1 to 1(1 context per passwrod proccessor)
*/
#pragma once
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <string>
#include <sstream>
#pragma comment(lib, "crypt32")
#pragma comment(lib, "ws2_32.lib")
class PasswordProcessor {
public:
	PasswordProcessor();
	~PasswordProcessor();
	std::string produceSalt();
	std::string hash(std::string input, std::string salt);

private:
	EVP_MD_CTX* mdctx;

};