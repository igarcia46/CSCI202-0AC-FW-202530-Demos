#ifndef SEARCH_H
#define SEARCH_H
#include "binaryTree.h"
#include <stdexcept>

template <class t>
int cmp(const t &item1, const t &item2)
{
    if (item1 > item2)
    {
        return 1;
    }
    if (item1 == item2)
    {
        return 0;
    }
    if (item1 < item2)
    {
        return -1;
    }
    return 0;
}

template <class t>
class binarySearchTree : public binaryTreeType<t>
{
public:
    binarySearchTree(int (*comp)(const t &, const t &) = cmp);
    void insertBST(const t &insertItem);
    bool search(const t &searchItem);
    void deleteNode(const t &deleteItem);

protected:
    int (*compare)(const t &item1, const t &item2);

private:
    void deleteFromTree(binaryNode<t> *&currentNode);
    bool search(const t &searchItem, binaryNode<t> *currentNode);
    void insertBST(binaryNode<t> *&insertItem, binaryNode<t> *&currentNode);
};

template <class t>
binarySearchTree<t>::binarySearchTree(int (*comp)(const t &, const t &))
{
    this->compare = comp;
}
template <class t>
void binarySearchTree<t>::insertBST(const t &insertItem)
{
    binaryNode<t> *newNode = new binaryNode<t>;
    newNode->data = new t(insertItem);
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;
    insertBST(newNode, this->root);
}
template <class t>
bool binarySearchTree<t>::search(const t &searchItem)
{
    return search(searchItem, this->root);
}
template <class t>
void binarySearchTree<t>::deleteNode(const t &deleteItem)
{
    binaryNode<t> *current;
    binaryNode<t> *currentParent;
    bool found = false;
    if (this->isEmpty())
    {
        throw std::invalid_argument("Cannot delete from an empty tree");
    }
    current = this->root;
    currentParent = current;
    int compareValue;
    while (current != nullptr && !found)
    {
        compareValue = compare(deleteItem, *current->data);
        if (compareValue == 0)
        {
            found = true;
        }
        else
        {
            currentParent = current;
            if (compareValue == -1)
            {
                current = current->lLink;
            }
            else
            {
                current = current->rLink;
            }
        }
    }
    if (!found)
    {
        throw std::invalid_argument("The item to be deleted is not in the tree");
    }
    else
    {
        if (current == this->root)
        {
            deleteFromTree(this->root);
        }
        else if (compare(deleteItem, *currentParent->data) == -1)
        {
            deleteFromTree(currentParent->lLink);
        }
        else
        {
            deleteFromTree(currentParent->rLink);
        }
    }
}
template <class t>
void binarySearchTree<t>::deleteFromTree(binaryNode<t> *&currentNode)
{
    binaryNode<t> *replace;
    binaryNode<t> *replaceParent;
    binaryNode<t> *temp;
    if (currentNode == nullptr)
    {
        throw std::invalid_argument("The item to be deleted is not in the tree.");
    }
    if (currentNode->lLink == nullptr && currentNode->rLink == nullptr)
    {
        temp = currentNode;
        currentNode = nullptr;
        delete temp;
    }
    else if (currentNode->lLink == nullptr)
    {
        temp = currentNode;
        currentNode = temp->rLink;
        delete temp;
    }
    else if (currentNode->rLink == nullptr)
    {
        temp = currentNode;
        currentNode = temp->lLink;
        delete temp;
    }
    else
    {
        replace = currentNode->lLink;
        replaceParent = nullptr;
        while (replace->rLink != nullptr)
        {
            replaceParent = replace;
            replace = replace->rLink;
        }
        t *tempData;
        tempData = currentNode->data;
        currentNode->data = replace->data;
        replace->data = tempData;
        if (replaceParent == nullptr)
        {
            currentNode->lLink = replace->lLink;
        }
        else
        {
            replaceParent->rLink = replace->lLink;
        }
        delete replace;
        replace = nullptr;
    }
}
template <class t>
bool binarySearchTree<t>::search(const t &searchItem, binaryNode<t> *currentNode)
{
    if (currentNode == nullptr)
    {
        return false;
    }
    int compareValue = compare(searchItem, *currentNode->data);
    if (compareValue == 0)
    {
        return true;
    }
    if (compareValue == -1)
    {
        return search(searchItem, currentNode->lLink);
    }
    else
    {
        return search(searchItem, currentNode->rLink);
    }
}
template <class t>
void binarySearchTree<t>::insertBST(binaryNode<t> *&insertItem, binaryNode<t> *&currentNode)
{
    if (currentNode == nullptr)
    {
        currentNode = insertItem;
    }
    else
    {
        int compareValue = compare(*insertItem->data, *currentNode->data);
        if (compareValue == 0)
        {
            throw std::invalid_argument("The item to be inserted is already in the tree -- duplicates are not allowed");
        }
        if (compareValue == -1)
        {
            insertBST(insertItem, currentNode->lLink);
        }
        else
        {
            insertBST(insertItem, currentNode->rLink);
        }
    }
}
#endif