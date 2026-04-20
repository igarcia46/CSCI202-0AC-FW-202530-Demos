#ifndef STACKADT_H
#define STACKADT_H

template <class t>
class stackADT
{
public:
    const static int DEFAULT_STACK_SIZE = 100;
    virtual void initializeStack() = 0;
    virtual bool isFullStack() const = 0;
    virtual bool isEmptyStack() const = 0;
    virtual void push(const t &) = 0;
    virtual t peek() const = 0;
    virtual t &top() = 0;
    virtual t pop() = 0;
};
#endif