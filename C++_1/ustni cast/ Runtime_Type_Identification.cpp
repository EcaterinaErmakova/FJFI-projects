#include <iostream>
#include <typeinfo>
using namespace std;

class Animal {public: virtual ~Animal() {}}; // Make class polymorphic
class Dog : public Animal {};
class Cat : public Animal {};


/* Type_info class */
class Vehicle {public: virtual ~Vehicle() {}};
class Car : public Vehicle {};
void examineType(const type_info& ti) {
    cout << "Type name: " << ti.name() << endl;
    cout << "Hash code: " << ti.hash_code() << endl;
}

int main() {
    // Basic type identification
    int x = 42;
    std::cout << "Type of x: " << typeid(x).name() << std::endl;
    // Polymorphic type identification
    Animal* animal1 = new Dog();
    Animal* animal2 = new Cat();
    std::cout << "animal1 type: " << typeid(*animal1).name() << std::endl;
    std::cout << "animal2 type: " << typeid(*animal2).name() << std::endl;
    // Non-polymorphic example
    Animal animal3;
    std::cout << "animal3 type: " << typeid(animal3).name() << std::endl;
    delete animal1;
    delete animal2;


    Car car;
    Vehicle* vPtr = &car;
    const type_info& carType = typeid(car);
    const type_info& ptrType = typeid(*vPtr);
    examineType(carType);
    examineType(ptrType);
    return 0;
}
