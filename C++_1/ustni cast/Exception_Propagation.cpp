#include <iostream>
#include <stdexcept>
using namespace std;
/*
Stack Unwinding
Exceptions propagate up the call stack until caught
*/
void function_A() {throw runtime_error("Error from function A");}
void function_B() {function_A();} // Exception propagates from here
void function_C() {function_B();} // Exception propagates through here

/*
void innerFunction() {throw runtime_error("Original error");}
void middleFunction() {
    try {innerFunction();}
    catch (const runtime_error& e) {
        cout << "Middle function caught: " << e.what() << endl;
        cout << "Middle function doing some cleanup..." << endl;
        throw;  // Re-throw the same exception
    }
}
*/

int main() {
    try {function_C();}
    catch (const runtime_error& e) {cout << "Main: Caught exception: " << e.what() << endl;}
/*  
    // Main: Program continues after exception handling
    try {middleFunction();}
    catch (const runtime_error& e) {cout << "Main caught re-thrown exception: " << e.what() << endl;}
*/
    return 0;
}
