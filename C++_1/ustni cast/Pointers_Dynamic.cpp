#include <iostream>

void Pointer_Basics(){
    int x_value = 1000;
    std::cout << x_value; // output: 1000
    std::cout << &x_value; // output: address (e.g., 0x7fff5fbff6ac)

    int* x_ptr = &x_value; // stores address of x_value
    std::cout << x_ptr; // output: address of x_value
    std::cout << *x_ptr; // output: 1000 (dereferencing)
    return;
}

void Dynamic_Memory_Allocation(){
    // Allocating single variable
    // Allocate and initialize
    int* x_ptr = new int(101);   
    std::cout << *x_ptr; // output: 101
    delete x_ptr; // Free memory
    x_ptr = nullptr;       

    // Allocating arrays
    int x_size = 2;
    int* arr = new int[x_size]; // Allocate array
    arr[0]=1;
    arr[1]=1;
    delete[] arr;
    arr = nullptr;
    return;
}