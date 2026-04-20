#ifndef BINARY_H
#define BINARY_H

#include <sstream>

template <class t>
struct binaryNode
{
    t *data;
    binaryNode<t> *lLink;
    binaryNode<t> *rLink;
    ~binaryNode() { delete data; };
    int bfactor;
    t &operator*()
    {
        return *data;
    };
};

template <class t>
class binaryTreeType
{
public:
    binaryTreeType();
    binaryTreeType(const binaryTreeType<t> &treeToCopy);
    const binaryTreeType<t> &operator=(const binaryTreeType<t> &treeToCopy);
    ~binaryTreeType();
    bool isEmpty() const;
    int treeHeight() const;
    int treeNodeCount() const;
    int treeLeavesCount() const;
    std::string inorderTraversal() const;
    std::string preorderTraversal() const;
    std::string postorderTraversal() const;
    // virtual void insert(const t &insertItem) = 0;
    virtual bool search(const t &searchItem) = 0;
    virtual void deleteNode(const t &deleteItem) = 0;

protected:
    binaryNode<t> *root;
    int height(binaryNode<t> *p) const;

private:
    void copyTree(binaryNode<t> *&myTreeNode, binaryNode<t> *treeToCopyNode);
    void destroy(binaryNode<t> *&p);
    void inorder(binaryNode<t> *, std::ostringstream &out) const;
    void preorder(binaryNode<t> *, std::ostringstream &out) const;
    void postorder(binaryNode<t> *, std::ostringstream &out) const;
    int nodeCount(binaryNode<t> *currentNode) const;
    int leavesCount(binaryNode<t> *currentNode) const;

    int max(int x, int y) const;
};

template <class t>
int binaryTreeType<t>::max(int x, int y) const
{
    if (x >= y)
    {
        return x;
    }
    return y;
}

template <class t>
binaryTreeType<t>::binaryTreeType()
{
    this->root = nullptr;
}

template <class t>
binaryTreeType<t>::binaryTreeType(const binaryTreeType<t> &treeToCopy)
{
    this->root = nullptr;
    copyTree(this->root, treeToCopy.root);
}

template <class t>
const binaryTreeType<t> &binaryTreeType<t>::operator=(const binaryTreeType<t> &treeToCopy)
{
    if (this != &treeToCopy)
    {
        if (!this->isEmpty())
        {
            destroy(root);
        }
        /* if (treeToCopy.isEmpty())
        {
            root = nullptr;
        }
        else
        { */
        copyTree(root, treeToCopy.root);
        // }
    }
}

template <class t>
binaryTreeType<t>::~binaryTreeType()
{
    destroy(this->root);
}

template <class t>
bool binaryTreeType<t>::isEmpty() const
{
    return root == nullptr;
}

template <class t>
int binaryTreeType<t>::treeHeight() const
{
    return height(root);
}

template <class t>
int binaryTreeType<t>::treeNodeCount() const
{
    return nodeCount(root);
}

template <class t>
int binaryTreeType<t>::treeLeavesCount() const
{
    return leavesCount(root);
}

template <class t>
void binaryTreeType<t>::copyTree(binaryNode<t> *&myTreeNode, binaryNode<t> *treeToCopyNode)
{
    if (treeToCopyNode == nullptr)
    {
        myTreeNode = nullptr;
    }
    else
    {
        myTreeNode = new binaryNode<t>;
        myTreeNode->data = new t(*treeToCopyNode->data);
        copyTree(myTreeNode->lLink, treeToCopyNode->lLink);
        copyTree(myTreeNode->rLink, treeToCopyNode->rLink);
    }
}
template <class t>
void binaryTreeType<t>::destroy(binaryNode<t> *&currentNode)
{
    if (currentNode != nullptr)
    {
        destroy(currentNode->lLink);
        destroy(currentNode->rLink);
        delete currentNode;
        currentNode = nullptr;
    }
}

template <class t>
void binaryTreeType<t>::inorder(binaryNode<t> *currentNode, std::ostringstream &out) const
{
    if (currentNode != nullptr)
    {
        inorder(currentNode->lLink, out);
        out << *currentNode->data << " ";
        inorder(currentNode->rLink, out);
    }
}

template <class t>
void binaryTreeType<t>::preorder(binaryNode<t> *currentNode, std::ostringstream &out) const
{
    if (currentNode != nullptr)
    {
        out << *currentNode->data << " ";
        preorder(currentNode->lLink, out);
        preorder(currentNode->rLink, out);
    }
}

template <class t>
void binaryTreeType<t>::postorder(binaryNode<t> *currentNode, std::ostringstream &out) const
{
    if (currentNode != nullptr)
    {
        postorder(currentNode->lLink, out);
        postorder(currentNode->rLink, out);
        out << *currentNode->data << " ";
    }
}

template <class t>
int binaryTreeType<t>::nodeCount(binaryNode<t> *currentNode) const
{
    if (currentNode == nullptr)
    {
        return 0;
    }
    return nodeCount(currentNode->lLink) + nodeCount(currentNode->rLink) + 1;
}

template <class t>
int binaryTreeType<t>::leavesCount(binaryNode<t> *currentNode) const
{
    if (currentNode == nullptr)
    {
        return 0;
    }
    if (currentNode->lLink == nullptr && currentNode->rLink == nullptr)
    {
        return 1;
    }
    return leavesCount(currentNode->lLink) + leavesCount(currentNode->rLink);
}

template <class t>
int binaryTreeType<t>::height(binaryNode<t> *currentNode) const
{
    if (currentNode == nullptr)
    {
        return 0;
    }
    return max(height(currentNode->lLink), height(currentNode->rLink)) + 1;
}

template <class t>
std::string binaryTreeType<t>::inorderTraversal() const
{
    std::ostringstream out;
    inorder(this->root, out);
    return out.str();
}

template <class t>
std::string binaryTreeType<t>::preorderTraversal() const
{
    std::ostringstream out;
    preorder(this->root, out);
    return out.str();
}

template <class t>
std::string binaryTreeType<t>::postorderTraversal() const
{
    std::ostringstream out;
    postorder(this->root, out);
    return out.str();
}
#endif