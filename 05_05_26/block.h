#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <ctime>
#include <functional>

class block
{
public:
    block(int, std::string, size_t = 0);
    std::string getData() const { return data; };
    bool validateHash();
    size_t getHash() const { return currentHash; };
    size_t getPrevHash() const { return prevHash; };

private:
    std::string data;
    time_t nonce;
    size_t prevHash;
    size_t currentHash;
    int blockNum;
    size_t calculateHash();
};
#endif