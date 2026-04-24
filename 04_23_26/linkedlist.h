#ifndef LINKED_H
#define LINKED_H
#include "node.h"
#include "linkedListIterator.h"
#include <iostream>
#include <string>

template <class t>
class linkedListType
{
public:
    linkedListType();
    linkedListType(const linkedListType<t> &otherList);
    const linkedListType<t> &operator=(const linkedListType<t> &);
    ~linkedListType();
    void destroyList();
    bool isEmptyList() const;
    int length() const;
    t front() const;
    t back() const;
    virtual void insert(const t &newInfo) = 0;
    virtual void deleteNode(const t &deleteItem) = 0;
    virtual bool search(const t &searchItem) const = 0;
    void print(std::ostream &, std::string = " ") const;
    linkedListIterator<t> begin();
    linkedListIterator<t> end();

protected:
    node<t> *head;
    node<t> *tail;
    int count;

private:
    void copyList(const linkedListType<t> &otherList);
};

template <class t>
linkedListType<t>::linkedListType()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template <class t>
linkedListType<t>::linkedListType(const linkedListType<t> &otherList)
{
    head = nullptr;
    tail = nullptr;
    count = 0;
    copyList(otherList);
}

template <class t>
const linkedListType<t> &linkedListType<t>::operator=(const linkedListType<t> &otherList)
{
    if (this != &otherList) // avoid self copy our address must be different from the address of other list
    {
        copyList(otherList);
    }
    return *this;
}

template <class t>
linkedListType<t>::~linkedListType()
{
    destroyList();
}

template <class t>
void linkedListType<t>::copyList(const linkedListType<t> &otherList)
{
    node<t> *newNode;
    node<t> *current;
    if (!isEmptyList())
    {
        destroyList();
    }
    if (otherList.isEmptyList())
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }
    else
    {
        current = otherList.head;
        count = otherList.count;
        this->head = new node<t>;
        // dont do this->head->data = otherList.head->data;
        this->head->data = new t(*(otherList.head->data));
        this->head->link = nullptr;
        this->tail = this->head;
        current = current->link;
        while (current != nullptr)
        {
            newNode = new node<t>;
            newNode->data = new t(*(current->data));
            newNode->link = nullptr;
            tail->link = newNode;
            tail = tail->link;
            current = current->link;
        }
    }
}

template <class t>
void linkedListType<t>::destroyList()
{
    if (!isEmptyList())
    {
        node<t> *temp;
        while (head != nullptr)
        {
            temp = head;
            head = head->link;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }
}

template <class t>
bool linkedListType<t>::isEmptyList() const
{
    return head == nullptr;
}
template <class t>
inline int linkedListType<t>::length() const
{
    return count;
}
template <class t>
t linkedListType<t>::front() const
{
    return *(head->data);
}
template <class t>
t linkedListType<t>::back() const
{
    return *(tail->data);
}
template <class t>
void linkedListType<t>::print(std::ostream &out, std::string separator) const
{
    if (!isEmptyList())
    {
        node<t> *current;
        current = head;
        while (current != nullptr)
        {
            out << *(current->data) << separator;
            current = current->link;
        }
    }
}
template <class t>
inline linkedListIterator<t> linkedListType<t>::begin()
{
    return linkedListIterator<t>(head);
}
template <class t>
inline linkedListIterator<t> linkedListType<t>::end()
{
    return linkedListIterator<t>();
}
#endif