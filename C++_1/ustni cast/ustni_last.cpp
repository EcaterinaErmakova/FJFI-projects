#include <iostream>
#include <string>
using namespace std;

class Animal{
    protected:
        string type;
        string name;
        int age;
        string food;
    public:
        Animal(const string& type, const string& name, int age, const string& food) 
            : type(type), name(name), age(age), food(food){}
        virtual ~Animal(){};
        Animal(Animal animal){

        }
        virtual void feed() const {cout << name <<" (which is "<< type << ")" << " eats " << food << ".\n"<< endl;}
        virtual void info() const {cout << name << " is "<< type << " and he/she is "<<age<< " years old."<<endl;}
};

class Lion : public Animal {
    public:
        Lion(const string& name, int age) : Animal("Lion", name, age, "meat") {}
        virtual ~Lion(){};
        void info() const override {Animal::info();}
        void feed() const override {Animal::feed();}
};

class Monkey : public Animal {
    public:
        Monkey(const string& name, int age) : Animal("Monkey", name, age, "bananas") {}
        virtual ~Monkey(){};
        void info() const override {Animal::info();}
        void feed() const override {Animal::feed();}
};

class Zebra : public Animal {
    public:
        Zebra(const string& name, int age) : Animal("Zebra", name, age, "grass") {}
        virtual ~Zebra(){};
        void info() const override {Animal::info();}
        void feed() const override {Animal::feed();}
};


int main(){
    int x;
    int* uk_x= &x;
    * uk_x=10;
    cout << uk_x; //adresa x
    cout << *uk_x; // value x
    Animal* animals[]={
        new Lion("Simba", 3), 
        new Lion("Mufasa", 4), 
        new Monkey("Godzila", 6),
        new Zebra("Marty", 4)
    };
    for (int i = 0; i <= 3; i++){
        animals[i]->info();
        animals[i]->feed();
        delete animals[i];
    }
    // Animal tigr;
    // Animal tigr 2= tigr;

    return 0;
}