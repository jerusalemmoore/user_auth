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