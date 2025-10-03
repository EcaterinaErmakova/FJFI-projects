#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

void Demonstrate_Standard_Exceptions() {
    // logic_error family
    try {throw invalid_argument("Invalid argument provided");}
    catch (const invalid_argument& e) {cout << "Caught invalid_argument: " << e.what() << endl;}
    
    try {throw out_of_range("Index out of range");}
    catch (const out_of_range& e) {cout << "Caught out_of_range: " << e.what() << endl;}
    
    // runtime_error family
    try {throw runtime_error("Runtime error occurred");}
    catch (const runtime_error& e) {cout << "Caught runtime_error: " << e.what() << endl;}
    
    try {throw overflow_error("Arithmetic overflow");}
    catch (const overflow_error& e) {cout << "Caught overflow_error: " << e.what() << endl;}
    
    // bad_alloc
    try {throw bad_alloc();} // Simulate memory allocation failure
    catch (const bad_alloc& e) {cout << "Caught bad_alloc: " << e.what() << endl;}
}

int main() {
    Demonstrate_Standard_Exceptions();
    // Real-world example with vector
    try {
        vector<int> vec = {1, 2, 3};
        cout << vec.at(5);  // Throws out_of_range
    }
    catch (const out_of_range& e) {cout << "Vector access error: " << e.what() << endl;}
    return 0;
}
