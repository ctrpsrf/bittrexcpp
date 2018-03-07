//---------------------------------------------------------------------------


#include "hmac_sha512.h"
//---------------------------------------------------------------------------

HMAC_SHA512::HMAC_SHA512(QString key1, QString msg) {

    unsigned char* digest;
    digest_.clear();
    char *key = key1.toLatin1().data();
    char *data = msg.toLatin1().data();
    digest = HMAC(EVP_sha512(), key, strlen(key), (unsigned char*)data,
                  strlen(data), NULL, NULL);
    for (int i = 0; digest[i] != '\0'; i++) {
        digest_.push_back(digest[i]);
    }
}


std::string HMAC_SHA512::hex_digest() {
    std::string str;
    str.clear();
    const char hex_chars[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c',
        'd', 'e', 'f'};
    for (int i = 0; i < digest_.size(); i++) {
        const char byte = digest_[i];
        str.push_back(hex_chars[(byte & 0xF0) >> 4]);
        str.push_back(hex_chars[(byte & 0x0F) >> 0]);
    }
    return str;
}
