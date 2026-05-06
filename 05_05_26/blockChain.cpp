#include "blockChain.h"

blockChain::blockChain()
{
    numBlocks = 0;
    // block genesis(numBlocks++, "Genesis Block");
    unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
    block genesis(numBlocks++, "Genesis Block", hash);
    chain.enqueue(genesis);
}

void blockChain::insert(std::string msg)
{
    block newBlock(numBlocks++, msg, chain.back().getHash());
    std::cout << newBlock.getHash() << std::endl;
    chain.enqueue(newBlock);
}

void blockChain::verify()
{
    linkedQueue<block> cpy(chain);
    // size_t prevHash = 0;
    unsigned char *prevHash = nullptr;
    while (!cpy.isEmptyQueue())
    {
        block current(cpy.dequeue());
        if (!current.validateHash())
        {
            throw std::runtime_error("Block has been changed");
        }
        // size_t currentPrevHash = current.getPrevHash();
        const unsigned char *currentPrevHash = current.getPrevHash();
        // if (prevHash != 0)
        if (prevHash != nullptr)
        {
            // if (prevHash != currentPrevHash)
            for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
            {
                if (prevHash[i] != currentPrevHash[i])
                {
                    throw std::runtime_error("Chain has been changed");
                }
            }
        }
        delete prevHash;
        prevHash = nullptr;
        // prevHash = current.getHash();
        const unsigned char *currentHash = current.getHash();
        prevHash = new unsigned char[SHA256_DIGEST_LENGTH];
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        {
            prevHash[i] = currentHash[i];
        }
    }
}
