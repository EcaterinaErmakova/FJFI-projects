// C++ Program to implement Interval Tree
#include <iostream>
using namespace std;

//#include "6_tree.hpp"
//#include "6_tree.hpp"
//#include "6_tree.hpp"
#include "6_tree.h"

/*
// A function to remove given interval from the tree.
void remove(Node* root, Interval i)
{
    // TODO:
    // 1. najit node ktery ma zadany interval
    // 2. pokud existuje, tak ho smazat (zavolat nasledujici funkci dole...)
}

// A function to remove given node from the tree.
void remove(Node* root, Node* node)
{
    // TODO: algoritmus viz ZALG
}
*/

void do_something(Interval<int> i)
{
    std::cout << "[" << i.low << ", " << i.high << "]" << std::endl;
}

void do_something_different(const Interval<int>& i)
{
    // const referenci nelze menit
    //i.low = 0;
    //i.high = 100;
    std::cout << "(" << i.low << ", " << i.high << ")" << std::endl;
}

int main() {
    Interval<int> ints[] = {{15, 20}, {10, 30}, {17, 19},
        {5, 20}, {12, 15}, {30, 40}
    };
    int n = sizeof(ints)/sizeof(ints[0]);
    
    IntervalTree<int> tree;
    for (int i = 0; i < n; i++)
        tree.insert(ints[i]);

    cout << "Inorder traversal of constructed Interval Tree is\n";
    tree.inorder();

    // ukazatel na funkci
    void (*f)(Interval<int>) = do_something;

    cout << "Generalized inorder variant:" << endl;
    tree.inorder(f);
    tree.inorder(do_something);
    tree.inorder(do_something_different);

    Interval<int> x = {6, 7};

    cout << "\nSearching for interval [" << x.low << "," << x.high << "]";
    Interval<int> *res = tree.overlapSearch(x);
    if (res == nullptr)
        cout << "\nNo Overlapping Interval";
    else
        cout << "\nOverlaps with [" << res->low << ", " << res->high << "]";
    
    return 0;
}
