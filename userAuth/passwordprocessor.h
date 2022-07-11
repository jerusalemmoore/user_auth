#pragma once
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <string.h>
class PasswordProcessor {
public:
	PasswordProcessor();
	~PasswordProcessor();
private:
	EVP_MD_CTX* mdctx;
};