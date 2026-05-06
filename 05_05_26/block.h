#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <ctime>
#include <functional>
#include <openssl/sha.h>

class block
{
public:
    // block(int, std::string, size_t = 0);
    block(int, std::string, const unsigned char *);
    block(const block &);
    // const block &operator=(const block &);
    std::string getData() const { return data; };
    bool validateHash();
    // size_t getHash() const { return currentHash; };
    // size_t getPrevHash() const { return prevHash; };
    const unsigned char *getHash() { return currentHash; };
    const unsigned char *getPrevHash() { return prevHash; };
    ~block();

private:
    std::string data;
    time_t nonce;
    unsigned char prevHash[SHA256_DIGEST_LENGTH];
    unsigned char *currentHash;
    // size_t prevHash;
    // size_t currentHash;
    int blockNum;
    // size_t calculateHash();
    unsigned char *calculateHash();
    void copyblock(const block &);
};
#endif