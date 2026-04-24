#ifndef LINKEDI_H
#define LINKEDI_H
#include "node.h"

template <class t>
class linkedListIterator
{
public:
    linkedListIterator();
    linkedListIterator(node<t> *);
    t *operator*();
    linkedListIterator<t> operator++();
    bool operator==(const linkedListIterator<t> &) const;
    bool operator!=(const linkedListIterator<t> &) const;

private:
    node<t> *current;
};

template <class t>
linkedListIterator<t>::linkedListIterator()
{
    current = nullptr;
}
template <class t>
linkedListIterator<t>::linkedListIterator(node<t> *current)
{
    this->current = current;
}

template <class t>
t *linkedListIterator<t>::operator*()
{
    if (current != nullptr)
    {
        return current->data;
    }
    return nullptr;
}

template <class t>
linkedListIterator<t> linkedListIterator<t>::operator++()
{
    if (current != nullptr)
        current = current->link;
    return *this;
}

template <class t>
inline bool linkedListIterator<t>::operator==(const linkedListIterator<t> &otherItr) const
{
    return this->current == otherItr.current;
}

template <class t>
inline bool linkedListIterator<t>::operator!=(const linkedListIterator<t> &otherItr) const
{
    return !(*this == otherItr);
}

#endif