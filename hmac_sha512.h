#ifndef hmac_sha512H
#define hmac_sha512H
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <string>
#include <vector>
#include <QString>

class HMAC_SHA512 {
public:

    HMAC_SHA512(QString key1, QString msg);

    std::string hex_digest();
	std::vector<unsigned char>digest_;

};

#endif // HMAC_SHA512_HPP
