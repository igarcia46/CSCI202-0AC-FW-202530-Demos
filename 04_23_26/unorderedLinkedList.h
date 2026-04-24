#ifndef UNORDERED_H
#define UNORDERED_H
#include <stdexcept>
#include "linkedlist.h"

template <class t>
class unorderedLinkedList : public linkedListType<t>
{
public:
    enum directionType
    {
        FORWARD,
        BACKWARD
    };
    unorderedLinkedList(directionType = FORWARD);
    void insert(const t &newInfo);
    void deleteNode(const t &deleteItem);
    bool search(const t &searchItem) const;

private:
    directionType direction;
    void insertFirst(node<t> *newNode);
    void insertLast(node<t> *newNode);
};

template <class t>
unorderedLinkedList<t>::unorderedLinkedList(directionType d) : direction(d)
{
}
template <class t>
void unorderedLinkedList<t>::insert(const t &newInfo)
{

    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(newInfo);
    newNode->link = nullptr;
    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else if (direction == FORWARD)
    {
        insertLast(newNode);
    }
    else
    {
        insertFirst(newNode);
    }
    this->count++;
}
template <class t>
void unorderedLinkedList<t>::deleteNode(const t &deleteItem)
{
    node<t> *current;
    node<t> *trailCurrent;
    bool found;
    if (this->isEmptyList())
    {
        throw std::out_of_range("Cannot delete from an empty list");
    }
    if (*(this->head->data) == deleteItem)
    {
        current = this->head;
        this->head = this->head->link;
        if (this->head == nullptr)
        {
            this->tail = nullptr;
        }
    }
    else
    {
        found = false;
        trailCurrent = this->head;
        current = this->head->link;
        while (current != nullptr && !found)
        {
            if (*(current->data) != deleteItem)
            {
                trailCurrent = current;
                current = current->link;
            }
            else
            {
                found = true;
            }
        }
        if (found)
        {
            trailCurrent->link = current->link;
            if (this->tail == current)
            {
                this->tail = trailCurrent;
            }
        }
        else
        {
            throw std::out_of_range("Item not found in list. Cannot delete.");
        }
    }
    delete current;
    this->count--;
}
template <class t>
bool unorderedLinkedList<t>::search(const t &searchItem) const
{
    node<t> *current;
    bool found = false;
    current = this->head;
    while (current != nullptr && !found)
    {
        if (*(current->data) == searchItem)
        {
            found = true;
        }
        else
        {
            current = current->link;
        }
    }
    return found;
}
template <class t>
void unorderedLinkedList<t>::insertFirst(node<t> *newNode)
{
    newNode->link = this->head;
    this->head = newNode;
}
template <class t>
void unorderedLinkedList<t>::insertLast(node<t> *newNode)
{
    this->tail->link = newNode;
    this->tail = newNode;
}
#endif