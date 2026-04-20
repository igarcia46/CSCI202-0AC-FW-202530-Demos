#ifndef AVLTREE_H
#define AVLTREE_H
#include "binarySearchTree.h"
#include "linkedStack.h"
#include <sstream>
#include <iostream>
#include "map.h"

template <class t>
class AVLTree : public binarySearchTree<t>
{
public:
    AVLTree(int (*comp)(const t &, const t &) = cmp);

    void deleteNode(const t &deleteItem);
    class Iterator
    {
    public:
        Iterator(binaryNode<t> *currentNode = nullptr, bool pushSmaller = true);
        bool hasNext();

        Iterator operator++();
        t &operator*();
        bool operator==(const Iterator &other) const;
        bool operator!=(const Iterator &other) const;

    private:
        linkedStack<binaryNode<t> *> nodeStack;
        void pushLeftNodes(binaryNode<t> *node, bool pushSmaller);
    };
    Iterator insert(const t &insertItem);
    Iterator begin() { return Iterator(this->root); };
    Iterator end() const { return Iterator(nullptr); };
    Iterator find(const t &searchItem) const;
    bool isBalanced();

private:
    void balanceFromLeft(binaryNode<t> *&currentNode);
    void balanceFromRight(binaryNode<t> *&currentNode);
    void rotateToLeft(binaryNode<t> *&currentNode);
    void rotateToRight(binaryNode<t> *&currentNode);
    void insertIntoAVL(binaryNode<t> *&currentNode, binaryNode<t> *newNode, bool &isTaller, Iterator &it);
    Iterator find(const t &searchItem, binaryNode<t> *currentNode) const;
    int calculateBalance(binaryNode<t> *currentNode);
    bool isBalanced(binaryNode<t> *currentNode);
    void balanceTree(binaryNode<t> *&currentNode);
    void deleteFromTree(binaryNode<t> *&currentNode, const t &key);
    binaryNode<t> *findMin(binaryNode<t> *node) const;
};

template <class t>
AVLTree<t>::AVLTree(int (*comp)(const t &, const t &)) : binarySearchTree<t>(comp)
{
}

template <class t>
AVLTree<t>::Iterator AVLTree<t>::insert(const t &insertItem)
{
    bool isTaller = false;
    binaryNode<t> *newNode = new binaryNode<t>;
    newNode->data = new t(insertItem);
    newNode->bfactor = 0;
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;
    Iterator it;
    insertIntoAVL(this->root, newNode, isTaller, it);
    return it;
}

template <class t>
void AVLTree<t>::deleteNode(const t &deleteItem)
{
    try
    {
        deleteFromTree(this->root, deleteItem);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

template <class t>
bool AVLTree<t>::isBalanced()
{
    return isBalanced(this->root);
}

template <class t>
void AVLTree<t>::balanceFromLeft(binaryNode<t> *&currentNode)
{
    binaryNode<t> *lChild;
    binaryNode<t> *lChild_RChild;
    lChild = currentNode->lLink;
    switch (lChild->bfactor)
    {
    case 0:
    case -1: // case 1 left child of current node is left high
        currentNode->bfactor = 0;
        lChild->bfactor = 0;
        rotateToRight(currentNode);
        break;
    case 1:
        lChild_RChild = lChild->rLink;
        switch (lChild_RChild->bfactor)
        {
        case -1:
            currentNode->bfactor = 1;
            lChild->bfactor = 0;
            break;
        case 0:
            currentNode->bfactor = 0;
            lChild->bfactor = 0;
            break;
        case 1:
            currentNode->bfactor = 0;
            lChild->bfactor = -1;
            break;
        }
        lChild_RChild->bfactor = 0;
        rotateToLeft(currentNode->lLink);
        rotateToRight(currentNode);
        break;
    }
}

template <class t>
void AVLTree<t>::balanceFromRight(binaryNode<t> *&currentNode)
{
    binaryNode<t> *rChild;
    binaryNode<t> *rChild_LChild;
    rChild = currentNode->rLink;
    switch (rChild->bfactor)
    {

    case -1: // case 1 left child of current node is left high
        rChild_LChild = rChild->lLink;
        switch (rChild_LChild->bfactor)
        {
        case -1:
            currentNode->bfactor = 0;
            rChild->bfactor = 1;
            break;
        case 0:
            currentNode->bfactor = 0;
            rChild->bfactor = 0;
            break;
        case 1:
            currentNode->bfactor = -1;
            rChild->bfactor = 0;
            break;
        }
        rChild_LChild->bfactor = 0;
        rotateToRight(currentNode->rLink);
        rotateToLeft(currentNode);
        break;

    case 0:
    case 1:
        currentNode->bfactor = 0;
        rChild->bfactor = 0;
        rotateToLeft(currentNode);
        break;
    }
}

template <class t>
void AVLTree<t>::rotateToLeft(binaryNode<t> *&currentNode)
{
    binaryNode<t> *newRootNode;
    if (currentNode == nullptr || currentNode->rLink == nullptr)
    {
        throw std::out_of_range("Cannot rotate empty node.");
    }
    newRootNode = currentNode->rLink;
    currentNode->rLink = newRootNode->lLink;
    newRootNode->lLink = currentNode;
    currentNode = newRootNode;
}

template <class t>
void AVLTree<t>::rotateToRight(binaryNode<t> *&currentNode)
{
    binaryNode<t> *newRootNode;
    if (currentNode == nullptr || currentNode->lLink == nullptr)
    {
        throw std::out_of_range("Cannot rotate empty node.");
    }
    newRootNode = currentNode->lLink;
    currentNode->lLink = newRootNode->rLink;
    newRootNode->rLink = currentNode;
    currentNode = newRootNode;
}

template <class t>
void AVLTree<t>::insertIntoAVL(binaryNode<t> *&currentNode, binaryNode<t> *newNode, bool &isTaller, Iterator &it)
{
    if (currentNode == nullptr)
    {
        currentNode = newNode;
        isTaller = true;
        it = Iterator(currentNode, false);
    }
    else
    {
        int compareValue = this->compare(**newNode, **currentNode); // ** dereferences the node pointer and with the * operator overload gives us the data.
        if (compareValue == 0)
        {
            throw std::invalid_argument("No Duplicates Allowed");
        }
        else if (compareValue == -1)
        {
            insertIntoAVL(currentNode->lLink, newNode, isTaller, it);
            if (isTaller)
            {
                switch (currentNode->bfactor)
                {
                case -1:
                    balanceFromLeft(currentNode);
                    isTaller = false;
                    break;
                case 0:
                    currentNode->bfactor = -1;
                    isTaller = true;
                    break;
                case 1:
                    currentNode->bfactor = 0;
                    isTaller = false;
                }
            }
        }
        else
        {
            insertIntoAVL(currentNode->rLink, newNode, isTaller, it);
            if (isTaller)
            {
                switch (currentNode->bfactor)
                {
                case -1:
                    currentNode->bfactor = 0;
                    isTaller = false;
                    break;
                case 0:
                    currentNode->bfactor = 1;
                    isTaller = true;
                    break;
                case 1:
                    balanceFromRight(currentNode);
                    isTaller = false;
                }
            }
        }
    }
}

template <class t>
int AVLTree<t>::calculateBalance(binaryNode<t> *currentNode)
{
    if (currentNode == nullptr)
    {
        return 0;
    }
    calculateBalance(currentNode->lLink);
    calculateBalance(currentNode->rLink);
    currentNode->bfactor = this->height(currentNode->rLink) - this->height(currentNode->lLink);
    return currentNode->bfactor;
}

template <class t>
bool AVLTree<t>::isBalanced(binaryNode<t> *currentNode)
{
    if (currentNode == nullptr)
    {
        return true;
    }
    bool balance = !(currentNode->bfactor > 1 || currentNode->bfactor < -1);
    return balance && isBalanced(currentNode->lLink) && isBalanced(currentNode->rLink);
}

template <class t>
void AVLTree<t>::balanceTree(binaryNode<t> *&currentNode)
{
    if (currentNode != nullptr)
    {
        int balance = this->height(currentNode->rLink) - this->height(currentNode->lLink);
        if (balance > 1)
        {
            balanceFromRight(currentNode);
        }
        else if (balance < -1)
        {
            balanceFromLeft(currentNode);
        }
    }
}

template <class t>
void AVLTree<t>::deleteFromTree(binaryNode<t> *&currentNode, const t &key)
{
    binaryNode<t> *temp;
    binaryNode<t> *replace;
    if (currentNode == nullptr)
    {
        throw std::invalid_argument("The item to be deleted is not in the tree");
    }
    int compareValue = this->compare(key, **currentNode);
    if (compareValue == -1)
    {
        deleteFromTree(currentNode->lLink, key);
    }
    else if (compareValue == 1)
    {
        deleteFromTree(currentNode->rLink, key);
    }
    else
    {
        temp = currentNode;
        if (currentNode->lLink == nullptr && currentNode->rLink == nullptr)
        {
            currentNode = nullptr;
            delete temp;
        }
        else if (currentNode->lLink == nullptr)
        {
            currentNode = currentNode->rLink;
            delete temp;
        }
        else if (currentNode->rLink == nullptr)
        {
            currentNode = currentNode->lLink;
            delete temp;
        }
        else
        {
            temp = findMin(currentNode->rLink);
            t *tmp = currentNode->data;
            currentNode->data = temp->data;
            temp->data = tmp;

            deleteFromTree(currentNode->rLink, key);
        }
    }
    balanceTree(currentNode);
    calculateBalance(currentNode);
}

template <class t>
binaryNode<t> *AVLTree<t>::findMin(binaryNode<t> *currentNode) const
{
    binaryNode<t> *min = currentNode;
    while (min && min->lLink != nullptr)
    {
        min = min->lLink;
    }
    return min;
}

template <class t>
AVLTree<t>::Iterator::Iterator(binaryNode<t> *currentNode, bool pushSmaller)
{
    pushLeftNodes(currentNode, pushSmaller);
}
template <class t>
bool AVLTree<t>::Iterator::hasNext()
{
    return !nodeStack.isEmptyStack();
}

template <class t>
AVLTree<t>::Iterator AVLTree<t>::Iterator::operator++()
{
    if (nodeStack.isEmptyStack())
    {
        return *this;
    }
    binaryNode<t> *node = nodeStack.pop();
    if (node->rLink != nullptr)
    {
        pushLeftNodes(node->rLink, true);
    }
    return *this;
}

template <class t>
t &AVLTree<t>::Iterator::operator*()
{
    if (nodeStack.isEmptyStack())
    {
        throw std::out_of_range("No more elements");
    }
    binaryNode<t> *node = nodeStack.top();
    return **node;
}

template <class t>
bool AVLTree<t>::Iterator::operator==(const Iterator &other) const
{
    if (nodeStack.isEmptyStack() && other.nodeStack.isEmptyStack())
    {
        return true;
    }
    else if (nodeStack.isEmptyStack() || other.nodeStack.isEmptyStack())
    {
        return false;
    }
    binaryNode<t> *myNode = nodeStack.peek();
    binaryNode<t> *theirNode = other.nodeStack.peek();

    return myNode == theirNode;
}

template <class t>
bool AVLTree<t>::Iterator::operator!=(const Iterator &other) const
{
    return !(*this == other);
}

template <class t>
void AVLTree<t>::Iterator::pushLeftNodes(binaryNode<t> *node, bool pushSmaller)
{
    if (node != nullptr)
    {
        nodeStack.push(node);
        node = node->lLink;
    }
    if (pushSmaller)
    {
        while (node != nullptr)
        {
            nodeStack.push(node);
            node = node->lLink;
        }
    }
}

template <class t>
AVLTree<t>::Iterator AVLTree<t>::find(const t &searchItem, binaryNode<t> *currentNode) const
{
    if (currentNode == nullptr)
    {
        return AVLTree<t>::Iterator();
    }
    int compareValue = this->compare(searchItem, **currentNode);
    if (compareValue == 0)
    {
        return AVLTree<t>::Iterator(currentNode, false);
    }
    else if (compareValue == 1)
    {
        return find(searchItem, currentNode->rLink);
    }
    else
    {
        return find(searchItem, currentNode->lLink);
    }
}

template <class t>
AVLTree<t>::Iterator AVLTree<t>::find(const t &searchItem) const
{
    Iterator it = find(searchItem, this->root);

    return it;
}
#endif