#include <string>
#include <iostream>

/* Polymorphism allows different classes to be treated through a common interface */
// Abstract base class
class Shape {
protected:
    std::string color;
public:
    Shape(std::string c) : color(c) {}
    /* 
    A virtual function (also known as virtual methods) is a member function 
    that is declared within a base class and is re-defined (overridden) by a derived class. 
    When you refer to a derived class object using a pointer or a reference to the base class, 
    you can call a virtual function for that object and execute the derived class's version of the method.
    */
    virtual double calculateArea() = 0; // Pure virtual function makes this an abstract class    
    virtual void display() {} // Virtual function with implementation
    virtual ~Shape() {} // Virtual destructor for proper cleanup
};

// Concrete derived classes
class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(std::string c, double w, double h) : Shape(c), width(w), height(h) {}
    double calculateArea() override {return width * height;}
    void display() override {}
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(std::string c, double r) : Shape(c), radius(r) {}
    double calculateArea() override {return 3.14159 * radius * radius;}
    void display() override {}
};
// Polymorphic function
void printShapeInfo(Shape* shape) {shape->display();}  // Calls appropriate derived class method

/*
Early Binding (compile-time): Function calls resolved at compile time
Late Binding (runtime): Function calls resolved at runtime using virtual functions
*/
class Base {
public:
    void nonVirtualFunc() {std::cout << "Base non-virtual" << std::endl;}// Early binding
    virtual void virtualFunc() {std::cout << "Base virtual" << std::endl;}// Late binding
};
class Derived : public Base {
public:
    void nonVirtualFunc() {std::cout << "Derived non-virtual" << std::endl;}
    void virtualFunc() override {std::cout << "Derived virtual" << std::endl;}
};

int main() {
    // Shape shape;  // ERROR: Cannot instantiate abstract class
    Shape* shapes[] = {new Rectangle("Red", 5.0, 3.0), new Circle("Blue", 4.0), new Rectangle("Green", 2.0, 8.0)};
    for (int i = 0; i < 3; i++) {
        printShapeInfo(shapes[i]);  // Polymorphic behavior
        delete shapes[i];
    }
    
    Base* ptr = new Derived();
    ptr->nonVirtualFunc();  // Prints: "Base non-virtual" (early binding)
    ptr->virtualFunc();     // Prints: "Derived virtual" (late binding)
    delete ptr;
    return 0;
}
