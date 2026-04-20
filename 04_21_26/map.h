#ifndef MAP_H
#define MAP_H
#include "pair.h"
#include "AVLTree.h"

template <class k, class v>
class map
{
public:
    map();

    v at(const k &) const;
    v &operator[](const k &);
    class Iterator
    {
    public:
        Iterator(AVLTree<pair<k, v>>::Iterator it);
        Iterator operator++();
        pair<k, v> operator*();
        bool operator==(const Iterator oth) const;
        bool operator!=(const Iterator oth) const;

    private:
        AVLTree<pair<k, v>>::Iterator it;
    };
    pair<bool, Iterator> insert(const k &, const v &);
    Iterator begin() { return Iterator(tree.begin()); };
    Iterator end() const { return Iterator(tree.end()); };
    bool deleteItem(const k &key);
    std::string preorder();

protected:
    AVLTree<pair<k, v>> tree;
};

template <class k, class v>
inline map<k, v>::map()
{
}

template <class k, class v>
pair<bool, typename map<k, v>::Iterator> map<k, v>::insert(const k &key, const v &value)
{
    bool insert = true;
    Iterator it(tree.end());
    pair<k, v> p(key, value);
    try
    {
        it = Iterator(tree.insert(p));
    }
    catch (std::invalid_argument e)
    {
        insert = false;
        it = Iterator(tree.find(p));
    }
    return pair<bool, Iterator>(insert, it);
}

template <class k, class v>
inline v map<k, v>::at(const k &key) const
{
    pair<k, v> pairForComp(key);
    typename AVLTree<pair<k, v>>::Iterator item = tree.find(pairForComp);
    if (item == tree.end())
    {
        throw std::out_of_range("The item is not in the map.");
    }

    return (*item).getValue();
}

template <class k, class v>
inline v &map<k, v>::operator[](const k &key)
{
    pair<k, v> pairForComp(key);
    typename AVLTree<pair<k, v>>::Iterator item = tree.find(pairForComp);
    if (item == tree.end())
    {
        v value;
        pairForComp.setValue(value);
        typename AVLTree<pair<k, v>>::Iterator it = tree.insert(pairForComp);
        return (*it).getValue();
    }
    return (*item).getValue();
}

template <class k, class v>
inline bool map<k, v>::deleteItem(const k &key)
{
    pair<k, v> deleteItem(key);
    tree.deleteNode(deleteItem);

    return tree.isBalanced();
}

template <class k, class v>
inline map<k, v>::Iterator::Iterator(AVLTree<pair<k, v>>::Iterator it)
{
    this->it = it;
}

template <class k, class v>
inline bool map<k, v>::Iterator::operator==(const map<k, v>::Iterator oth) const
{
    return this->it == oth.it;
}
template <class k, class v>
inline bool map<k, v>::Iterator::operator!=(const map<k, v>::Iterator oth) const
{
    return this->it != oth.it;
}

template <class k, class v>
map<k, v>::Iterator map<k, v>::Iterator::operator++()
{
    ++it;
    return *this;
}
template <class k, class v>
pair<k, v> map<k, v>::Iterator::operator*()
{
    return *it;
}
#endif