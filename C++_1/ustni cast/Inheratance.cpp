#include <string>

// Base class
class Animal {
protected:
    std::string name;
    int age;
public:
    Animal(std::string n, int a) : name(n), age(a) {}
    void eat() {return;}
    void sleep() {return;}   
    virtual void makeSound() {return;}
};

// Derived class
class Dog : public Animal {
private:
    std::string breed;
public:
    Dog(std::string n, int a, std::string b) : Animal(n, a), breed(b) {}
    void makeSound() override {return;}
    void wagTail() {return;}
};
// Derived class
class Cat : public Animal {
public:
    Cat(std::string n, int a) : Animal(n, a) {}
    void makeSound() override {return;}
    void purr() {return;}
};

/*----------------------------------------------*/
class Base {
public:
    int public_var;
protected:
    int protected_var;
private:
    int private_var;
};

// Public inheritance
class PublicDerived : public Base {
    // public_var remains public
    // protected_var remains protected
    // private_var is not accessible
};
// Protected inheritance
class ProtectedDerived : protected Base {
    // public_var becomes protected
    // protected_var remains protected
    // private_var is not accessible
};
// Private inheritance
class PrivateDerived : private Base {
    // public_var becomes private
    // protected_var becomes private
    // private_var is not accessible
};
