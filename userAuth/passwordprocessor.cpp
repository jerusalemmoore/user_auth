/*
    Programmer: Jerusalem Moore
    Class: PasswordProcessor
    Data: 7/13/2022
    Description:
        Class for providing password salting/hashing and evaluation functions, currently the 
        relationship to class and EVP context is 1 to 1
*/
#include "passwordprocessor.h"
#include <iostream>
#include <format>
#include <chrono>
#include <ctime>
using std::cout; using std::endl;
using std::string; using std::hex;
using std::stringstream;
PasswordProcessor::PasswordProcessor() {
    mdctx = EVP_MD_CTX_new();
 /*   std::string mess1 = "Test Message";
    std::string mess2 = "Test Message";
    std::string salt = "Wed Jul 13 11:43:43 2022";
    std::string hash1 = hash(mess1, salt);
    std::cout << hash1 << std::endl;
    std::string hash2 = hash(mess2, salt);
    if (hash1 == hash2) {
        std::cout << "success" << std::endl;
    }*/
    
}
PasswordProcessor::~PasswordProcessor() {
    EVP_MD_CTX_free(mdctx);
    //this is required to avoid library leaks, not sure why it doesn't
    //run automatically as the documentation describes
    OPENSSL_cleanup();

}
/*
    hash given password and salt with sha256 for db queries
*/
std::string PasswordProcessor::hash(std::string password, std::string salt) {
    unsigned int mdlen;
    
    EVP_DigestInit_ex2(mdctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(mdctx, password.c_str(), strlen(password.c_str()));//process password
    EVP_DigestUpdate(mdctx, salt.c_str(), strlen(salt.c_str()));
    unsigned char md[EVP_MAX_MD_SIZE];//buffer for message digest
    EVP_DigestFinal_ex(mdctx, md, &mdlen);//store result and size of processed message digest
    std::stringstream stream;//stream for translating processed md to hexadecimal
    for (int i = 0; i < mdlen; i++) {
        stream <<  std::hex << int(md[i]);//convert to hexadecimal
    }
    
    std::string hashVal = stream.str();
    //std::cout << "Hex: " << hexVal << std::endl;
    //EVP_MD_CTX_free(mdctx);
    return hashVal;
}
/*
    produce unique salt for password
*/
std::string PasswordProcessor::produceSalt() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(now);
    char date[26];
    ctime_s(date, sizeof date, (&tt));
    //std::cout << std::string(salt) << std::endl;
    unsigned int mdlen;
    EVP_DigestInit_ex2(mdctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(mdctx, date, strlen(date)); 
    unsigned char md[EVP_MAX_MD_SIZE];//buffer for message digest
    EVP_DigestFinal_ex(mdctx, md, &mdlen);//process salt
    std::stringstream stream;//stream for translating processed md to hexadecimal
    for (int i = 0; i < mdlen; i++) {
        stream << std::hex << int(md[i]);
    }
    std::string salt = stream.str();
    return std::string(salt);
}

