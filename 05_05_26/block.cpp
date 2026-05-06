#include "block.h"

/* block::block(int blockNum, std::string data, size_t prevHash) : blockNum(blockNum), prevHash(prevHash), data(data)
{
    this->nonce = time(NULL);
    currentHash = calculateHash();
} */

block::block(int blockNum, std::string data, const unsigned char *prevHash) : blockNum(blockNum), data(data)
{
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        this->prevHash[i] = prevHash[i];
    }
    this->nonce = time(NULL);
    currentHash = calculateHash();
}

block::block(const block &other)
{
    copyblock(other);
}

bool block::validateHash()
{
    bool valid = true;
    unsigned char *hash = calculateHash();
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        if (currentHash[i] != hash[i])
        {
            valid = false;
            break;
        }
    }
    delete[] hash;
    return valid;
}

block::~block()
{
    delete[] currentHash;
}

/* size_t block::calculateHash()
{
    std::hash<std::string> str_hash;
    std::string hashString = std::to_string(blockNum) + std::to_string(nonce) + data + std::to_string(prevHash);
    return str_hash(hashString);
} */

unsigned char *block::calculateHash()
{
    std::string phash(prevHash, prevHash + sizeof(prevHash) / sizeof(prevHash[0]));
    std::string hashString = std::to_string(blockNum) + std::to_string(nonce) + data + phash;
    unsigned char *hash = new unsigned char[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)hashString.c_str(), hashString.length(), hash);
    return hash;
}

void block::copyblock(const block &other)
{
    this->blockNum = other.blockNum;
    this->nonce = other.nonce;
    this->data = other.data;
    currentHash = new unsigned char[SHA256_DIGEST_LENGTH];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        this->prevHash[i] = other.prevHash[i];
        this->currentHash[i] = other.currentHash[i];
    }
}
