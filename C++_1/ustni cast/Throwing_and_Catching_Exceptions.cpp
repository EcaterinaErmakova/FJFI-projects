#include <iostream>
#include <stdexcept>
using namespace std;

// C++ uses try, catch, and throw for exception handling
double divide(double numerator, double denominator) {
    if (denominator == 0) {throw runtime_error("Division by zero error!");}
    return numerator / denominator;
}

void processNumber(int num) {
    if (num < 0) {throw invalid_argument("Number cannot be negative");}
    if (num > 100) {throw out_of_range("Number exceeds maximum value");}
    if (num == 0) {throw runtime_error("Zero is not allowed");}
}

int main() {
    /* Basic Exception Handling */
    double num=1.0, den=3.0;
    try {divide(num, den);}
    catch (const runtime_error& e) {cout << "Error caught: " << e.what() << endl;}
    
    /* Multiple Catch Blocks */
    int number=1;
    try {processNumber(number);}
    catch (const invalid_argument& e) {cout << "Invalid argument: " << e.what() << endl;}
    catch (const out_of_range& e) {cout << "Out of range: " << e.what() << endl;}    
    catch (const runtime_error& e) {cout << "Runtime error: " << e.what() << endl;}
    catch (...) {cout << "Unknown exception caught" << endl;} // Catch all other exceptions

    return 0;
}
