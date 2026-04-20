#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "stackADT.h"
#include "node.h"
#include <stdexcept>

template <class t>
class linkedStack : public stackADT<t>
{
public:
    linkedStack(int = stackADT<t>::DEFAULT_STACK_SIZE);
    linkedStack(const linkedStack<t> &);
    const linkedStack<t> &operator=(const linkedStack<t> &);
    void initializeStack();
    bool isFullStack() const;
    bool isEmptyStack() const;
    void push(const t &);
    t peek() const;
    t &top();
    t pop();
    ~linkedStack();

private:
    void copyStack(const linkedStack<t> &);

    node<t> *stackTop;
    int count;
};

template <class t>
linkedStack<t>::linkedStack(int)
{
    stackTop = nullptr;
    count = 0;
}
template <class t>
linkedStack<t>::linkedStack(const linkedStack<t> &stackToCopy)
{
    stackTop = nullptr;
    count = 0;
    copyStack(stackToCopy);
}

template <class t>
inline const linkedStack<t> &linkedStack<t>::operator=(const linkedStack<t> &stackToCopy)
{
    if (this != &stackToCopy)
    {
        copyStack(stackToCopy);
    }
    return *this;
}

template <class t>
void linkedStack<t>::initializeStack()
{
    node<t> *temp;
    while (stackTop != nullptr)
    {
        temp = stackTop;
        stackTop = stackTop->link;
        delete temp;
    }
    count = 0;
}

template <class t>
inline bool linkedStack<t>::isFullStack() const
{
    return false;
}

template <class t>
bool linkedStack<t>::isEmptyStack() const
{
    return stackTop == nullptr;
}

template <class t>
void linkedStack<t>::push(const t &newItem)
{
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(newItem);
    newNode->link = stackTop;
    stackTop = newNode;
    count++;
}

template <class t>
t linkedStack<t>::peek() const
{
    if (isEmptyStack())
    {
        throw std::out_of_range("Empty Stack");
    }
    return *stackTop->data;
}

template <class t>
t &linkedStack<t>::top()
{
    if (isEmptyStack())
    {
        throw std::out_of_range("Empty Stack");
    }
    return *stackTop->data;
}

template <class t>
t linkedStack<t>::pop()
{
    if (isEmptyStack())
    {
        throw std::underflow_error("Stack underfow. Cannot remove from an empty stack.");
    }
    t copy = *(stackTop->data);
    node<t> *temp = stackTop;
    stackTop = stackTop->link;
    delete temp;
    count--;
    return copy;
}

template <class t>
linkedStack<t>::~linkedStack()
{
    initializeStack();
}

template <class t>
void linkedStack<t>::copyStack(const linkedStack<t> &stackToCopy)
{
    node<t> *newNode;
    node<t> *current;
    node<t> *last;
    if (!isEmptyStack())
    {
        initializeStack();
    }
    if (stackToCopy.isEmptyStack())
    {
        this->stackTop = nullptr;
        count = 0;
    }
    else
    {
        current = stackToCopy.stackTop;
        this->stackTop = new node<t>;
        this->stackTop->data = new t(*(current->data));
        this->stackTop->link = nullptr;
        last = this->stackTop;
        current = current->link;
        while (current != nullptr)
        {
            newNode = new node<t>;
            newNode->data = new t(*(current->data));
            newNode->link = nullptr;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }
        this->count = stackToCopy.count;
    }
}
#endif