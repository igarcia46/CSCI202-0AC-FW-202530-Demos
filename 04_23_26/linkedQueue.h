#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H
#include "queueADT.h"
#include "node.h"

template <class t>
class linkedQueue : public queueADT<t>
{
public:
    linkedQueue();
    linkedQueue(const linkedQueue<t> &);
    const linkedQueue<t> &operator=(const linkedQueue<t> &);
    ~linkedQueue();
    bool isEmptyQueue() const;
    bool isFullQueue() const;
    void initializeQueue();
    t front() const;
    t back() const;
    void enqueue(const t &queueElement);
    t dequeue();

private:
    node<t> *queueFront;
    node<t> *queueRear;
    void copyQueue(const linkedQueue<t> &);
};

template <class t>
linkedQueue<t>::linkedQueue()
{
    queueFront = nullptr;
    queueRear = nullptr;
}

template <class t>
linkedQueue<t>::linkedQueue(const linkedQueue<t> &otherQueue)
{
    queueFront = nullptr;
    queueRear = nullptr;
    copyQueue(otherQueue);
}

template <class t>
const linkedQueue<t> &linkedQueue<t>::operator=(const linkedQueue<t> &otherQueue)
{
    if (this != &otherQueue)
    {
        copyQueue(otherQueue);
    }
    return *this;
}

template <class t>
linkedQueue<t>::~linkedQueue()
{
    initializeQueue();
}

template <class t>
bool linkedQueue<t>::isEmptyQueue() const
{
    return queueFront == nullptr;
}

template <class t>
bool linkedQueue<t>::isFullQueue() const
{
    return false;
}

template <class t>
void linkedQueue<t>::initializeQueue()
{
    if (!isEmptyQueue())
    {
        node<t> *temp;
        while (this->queueFront != nullptr)
        {
            temp = queueFront;
            queueFront = queueFront->link;
            delete temp;
        }
        queueRear = nullptr;
    }
}

template <class t>
t linkedQueue<t>::front() const
{
    if (isEmptyQueue())
    {
        throw std::out_of_range("Cannot get first item of an empty queue");
    }
    return *(queueFront->data);
}

template <class t>
t linkedQueue<t>::back() const
{
    if (isEmptyQueue())
    {
        throw std::out_of_range("Cannot get last item of an empty queue");
    }
    return *(queueRear->data);
}

template <class t>
void linkedQueue<t>::enqueue(const t &queueElement)
{
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(queueElement);
    newNode->link = nullptr;
    if (this->isEmptyQueue())
    {
        this->queueFront = newNode;
        this->queueRear = newNode;
    }
    else
    {
        this->queueRear->link = newNode;
        this->queueRear = newNode;
    }
}
template <class t>
t linkedQueue<t>::dequeue()
{
    if (isEmptyQueue())
    {
        throw std::out_of_range("Cannot delete from an empty queue.");
    }
    node<t> *temp;
    temp = this->queueFront;
    this->queueFront = this->queueFront->link;
    t ret(*(temp->data));
    delete temp;

    return ret;
}
template <class t>
void linkedQueue<t>::copyQueue(const linkedQueue<t> &otherQueue)
{
    node<t> *newNode;
    node<t> *current;
    if (!isEmptyQueue())
    {
        initializeQueue();
    }
    if (otherQueue.isEmptyQueue())
    {
        queueFront = nullptr;
        queueRear = nullptr;
    }
    else
    {
        current = otherQueue.queueFront;

        this->queueFront = new node<t>;
        // dont do this->queueFront->data = otherQueue.queueFront->data;
        this->queueFront->data = new t(*(otherQueue.queueFront->data));
        this->queueFront->link = nullptr;
        this->queueRear = this->queueFront;
        current = current->link;
        while (current != nullptr)
        {
            newNode = new node<t>;
            newNode->data = new t(*(current->data));
            newNode->link = nullptr;
            queueRear->link = newNode;
            queueRear = queueRear->link;
            current = current->link;
        }
    }
}
#endif