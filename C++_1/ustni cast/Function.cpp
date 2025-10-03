// Function prototype (declaration)
#include <iostream>
int function(int x);
void modifyValue(int y);
void modifyReference(int & y);
void modifyPointer(int* x);
void default_parameters (int x=0, int y=1); // default parameters: must be declared in the prototype, not definition
// Function definition
int function(int x) {return x;}
void modifyValue(int y) {y = 100;} // Modifies only the copy
void modifyReference(int & y) {y = 100;} // Modifies the original variable
void modifyPointer(int* y) {*y = 100;} // Modifies value at the address
void default_parameters (int x, int y) {std::cout << x << "," << y;}

int main(){
    int y=0;
    modifyValue(y);
    std::cout << y; // output: 0
    modifyReference(y);
    std::cout << y; // output: 100
    modifyPointer(&y);
    std::cout << y; // output: 100
    default_parameters(); // output: 0,1
    default_parameters(10, 20); // output: 10,20
}