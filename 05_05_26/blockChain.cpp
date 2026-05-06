#include "blockChain.h"

blockChain::blockChain()
{
    numBlocks = 0;
    block genesis(numBlocks++, "Genesis Block");
    chain.enqueue(genesis);
}

void blockChain::insert(std::string msg)
{
    block newBlock(numBlocks++, msg, chain.back().getHash());
    chain.enqueue(newBlock);
}

void blockChain::verify()
{
    linkedQueue<block> cpy(chain);
    size_t prevHash = 0;
    while (!cpy.isEmptyQueue())
    {
        block current(cpy.dequeue());
        if (!current.validateHash())
        {
            throw std::runtime_error("Block has been changed");
        }
        size_t currentPrevHash = current.getPrevHash();
        if (prevHash != 0)
        {
            if (prevHash != currentPrevHash)
            {
                throw std::runtime_error("Chain has been changed");
            }
        }
        prevHash = current.getHash();
    }
}
