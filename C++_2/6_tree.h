#pragma once

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
    // priklad pouziti using
    //using interval = Interval<T>;

    // definice typu, ktery je ukazatel na funkci
    //using Function = void (*)(Interval<T>);

    Node<T>* root;

    Node<T>* newNode(Interval<T> i);
    Node<T>* insertNode(Node<T>* node, Interval<T> i);
    Interval<T>* overlapSearch(Node<T>* node, Interval<T> i);
    void inorder(Node<T>* node);
    //void inorder(Node<T>* node, void (*f)(Interval<T>));
    template <typename Function>
    void inorder(Node<T>* node, Function f);  // zobecneni pomoci parametru funkce
    
    void deleteTree(Node<T>* node);

public:
    IntervalTree();  // constructor

    void insert(Interval<T> i);
    Interval<T> *overlapSearch(Interval<T> i);
    void inorder();
    template <typename Function>
    void inorder(Function f);  // zobecneni pomoci parametru funkce

    // zobecneni metody inorder pomoci iteratoru
    //... begin();
    //... end();

    ~IntervalTree();  // destructor
};

//#include "tree.hpp"

/*
Pouziti metod begin a end:

for (... i = tree.begin(); i != tree.end(); i++)
{
   ...
}

*/