#include "passwordprocessor.h"

PasswordProcessor::PasswordProcessor() {
    //const EVP_MD* md;
    char mess1[] = "Test Message\n";
    char mess2[] = "Hello World\n";
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len, i;

    //if (argv[1] == NULL) {
    //    printf("Usage: mdtest digestname\n");
    //    exit(1);
    //}

    //md = EVP_get_digestbyname(argv[1]);
    /*if (md == NULL) {
        printf("Unknown message digest %s\n", argv[1]);
        exit(1);
    }*/

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex2(mdctx, EVP_sha256(), NULL);
 /*   EVP_DigestUpdate(mdctx, mess1, strlen(mess1));
    EVP_DigestUpdate(mdctx, mess2, strlen(mess2));
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);*/

    //printf("Digest is: ");
    //for (i = 0; i < md_len; i++)
    //    printf("%02x", md_value[i]);
    //printf("\n");


}
PasswordProcessor::~PasswordProcessor() {
    EVP_MD_CTX_free(mdctx);

    //this is required to avoid library leaks, not sure why it doesn't
    //run automatically as the documentation describes
    //OPENSSL_cleanup();

}
