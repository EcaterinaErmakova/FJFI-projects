#include <iostream>

// Structure to represent an interval
template <typename T>
struct Interval {
    T low, high;
};

// Structure to represent a node in Interval Search Tree
template <typename T>
struct Node {
    Interval<T> *i;  
    T max;
    Node<T> *left, *right;
};

template <typename T>
class IntervalTree
{
private:
    Node<T>* root;

    Node<T>* newNode(Interval<T> i);
    Node<T>* insertNode(Node<T>* node, Interval<T> i);
    Interval<T>* overlapSearch(Node<T>* node, Interval<T> i);
    void inorder(Node<T>* node);
    void deleteTree(Node<T>* node);

public:
    IntervalTree();  // constructor

    void insert(Interval<T> i);
    Interval<T> *overlapSearch(Interval<T> i);
    void inorder();

    ~IntervalTree();  // destructor
};


// A utility function to create a new Interval Search Tree Node
template <typename T>
Node<T>* IntervalTree<T>::newNode(Interval<T> i) {
    Node<T> *temp = new Node<T>;
    temp->i = new Interval<T>(i);
    temp->max = i.high;
    temp->left = temp->right = nullptr;
    return temp;
};

template <typename T>
IntervalTree<T>::IntervalTree()
{
    root = nullptr;
}

// A utility function to insert a new Interval Search Tree Node
// This is similar to BST Insert.  Here the low value of interval
// is used tomaintain BST property
template <typename T>
Node<T>* IntervalTree<T>::insertNode(Node<T>* node, Interval<T> i)
{
    // Base case: Tree is empty, new node becomes root
    if (node == nullptr)
        return newNode(i);

    // Get low value of interval at root
    int l = node->i->low;

    // If root's low value is smaller, 
    // then new interval goes to left subtree
    if (i.low < l)
        node->left = insertNode(node->left, i);

    // Else, new node goes to right subtree.
    else
        node->right = insertNode(node->right, i);

    // Update the max value of this ancestor if needed
    if (node->max < i.high)
        node->max = i.high;

    return node;
}

template <typename T>
void IntervalTree<T>::insert(Interval<T> i)
{
    if (root == nullptr)
        root = insertNode(nullptr, i);
    else
        insertNode(root, i);
}


// A utility function to check if given two intervals overlap
template <typename T>
bool isOverlapping(Interval<T> i1, Interval<T> i2) {
    if (i1.low <= i2.high && i2.low <= i1.high)
        return true;
    return false;
}

// The main function that searches a given 
// interval i in a given Interval Tree.
template <typename T>
Interval<T>* IntervalTree<T>::overlapSearch(Node<T>* node, Interval<T> i) {

    // Base Case, tree is empty
    if (node == nullptr) return nullptr;

    // If given interval overlaps with root
    if (isOverlapping(*(node->i), i))
        return node->i;

    // If left child of root is present and max of left child is
    // greater than or equal to given interval, then i may
    // overlap with an interval is left subtree
    if (node->left != nullptr && node->left->max >= i.low)
        return overlapSearch(node->left, i);

    // Else interval can only overlap with right subtree
    return overlapSearch(node->right, i);
}

template <typename T>
Interval<T>* IntervalTree<T>::overlapSearch(Interval<T> i)
{
    return overlapSearch(root, i);
}

template <typename T>
void IntervalTree<T>::inorder(Node<T>* node) {
    if (node == nullptr) return;
    inorder(node->left);
    std::cout << "[" << node->i->low << ", " << node->i->high << "]"
              << " max = " << node->max << std::endl;
    inorder(node->right);
}

template <typename T>
void IntervalTree<T>::inorder()
{
    inorder(root);
}

// A function to delete the whole tree.
template <typename T>
void IntervalTree<T>::deleteTree(Node<T>* node)
{
    if (node == nullptr)
        return;

    // first delete the children
    deleteTree(node->left);
    deleteTree(node->right);

    // delete the current node
    delete node->i;
    delete node;
}

template <typename T>
IntervalTree<T>::~IntervalTree()
{
    deleteTree(root);
}