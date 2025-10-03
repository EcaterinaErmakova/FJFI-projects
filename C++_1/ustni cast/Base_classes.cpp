
#include <string>

// Class definition
class Student {
public:
    // Attributes (data members)
    // Variables that store the state of an object
    std::string name;
    int age;
    double gpa;

    // Methods (member functions)
    // Functions that define the behavior of an object
    void displayInfo() {return;}
    void study() {return;}
};


int main() {
    // Object creation
    Student student1;              
    // Setting attributes
    student1.name = "Alice";       
    student1.age = 20;
    student1.gpa = 3.8;
    // Calling method
    student1.displayInfo();        
    student1.study();
    return 0;
}