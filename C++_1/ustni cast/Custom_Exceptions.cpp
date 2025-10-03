#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// Custom exception inheriting from std::exception
class FileNotFoundException : public exception {
private:
    string message;
public:
    FileNotFoundException(const string& filename) {message = "File not found: " + filename;}
    const char* what() const noexcept override {return message.c_str();}
};
// Custom exception with additional data
class ValidationException : public runtime_error {
private:
    int errorCode;
    string fieldName;
public:
    ValidationException(const string& field, int code, const string& msg) : runtime_error(msg), fieldName(field), errorCode(code) {}
    int getErrorCode() const { return errorCode; }
    const string& getFieldName() const { return fieldName; }
};
// Exception hierarchy
class ApplicationException : public exception {
protected:
    string message;
public:
    ApplicationException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {return message.c_str();}
};

class DatabaseException : public ApplicationException {
public:
    DatabaseException(const string& msg) : ApplicationException("Database Error: " + msg) {}
};

class NetworkException : public ApplicationException {
public:
    NetworkException(const string& msg) : ApplicationException("Network Error: " + msg) {}
};

// Functions that use custom exceptions
void openFile(const string& filename) {
    if (filename.empty()) {throw FileNotFoundException(filename);}
    //File opened successfully
}
void validateAge(int age) {
    if (age < 0) {throw ValidationException("age", 1001, "Age cannot be negative");}
    if (age > 150) {throw ValidationException("age", 1002, "Age cannot exceed 150");}
    // Age validation passed
}
void connectToDatabase() {throw DatabaseException("Connection timeout");}

int main() {
    // Test FileNotFoundException
    try {openFile("");}
    catch (const FileNotFoundException& e) {cout << "Caught: " << e.what() << endl;}
    // Test ValidationException
    try {validateAge(-5);}
    catch (const ValidationException& e) {cout << "Validation Error in field '" << e.getFieldName() << "' (Code: " << e.getErrorCode() << "): " << e.what() << endl;}
    // Test exception hierarchy
    try {connectToDatabase();}
    catch (const DatabaseException& e) {cout << "Database specific handling: " << e.what() << endl;}
    catch (const ApplicationException& e) {cout << "Application level handling: " << e.what() << endl;}
    // Demonstrating catching by base class
    try {throw NetworkException("Host unreachable");}
    catch (const ApplicationException& e) {cout << "Caught via base class: " << e.what() << endl;}// Catches derived NetworkException
    
    return 0;
}
