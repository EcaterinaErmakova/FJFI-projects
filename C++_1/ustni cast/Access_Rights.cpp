#include <iostream>
#include <string>

/* 
public: Accessible from anywhere
private: Only accessible within the same class
protected: Accessible within the class and its derived classes
*/

class BankAccount {
// Private - cannot be accessed directly
private:
    double balance;      
    std::string accountNumber;
// Protected - accessible to derived classes
protected:
    double interestRate;    
public:
    // Constructor
    BankAccount(std::string accNum, double initialBalance) {
        accountNumber = accNum;
        balance = initialBalance;
        interestRate = 0.03;
    }
    // Public getter methods
    double getBalance() const {return balance;}
    std::string getAccountNumber() const {return accountNumber;}
    // Public setter methods with validation
    void deposit(double amount) {return;}
    bool withdraw(double amount) {return true;}
};


/* Friend function definition */

class Circle {
private:
    double radius; 
public:
    Circle(double r) : radius(r) {}   
    friend double calculateArea(const Circle& c); // Friend function declaration
    friend class GeometryCalculator;  // Friend class
};

// Friend functions can access private and protected members
double calculateArea(const Circle& c) {return 3.14159 * c.radius * c.radius;} // Can access private radius

// Friend class
class GeometryCalculator {
public:
    double getRadius(const Circle& c) {return c.radius;} // Can access private member
};


int main() {
    BankAccount account("123456", 1000.0);
    // account.balance = 5000;  // ERROR: balance is private
    // Use public methods instead
    //std::cout << "Balance: $" << account.getBalance() << std::endl;   
    Circle circle(5.0);
    std::cout << "Area: " << calculateArea(circle) << std::endl;
    GeometryCalculator calc;
    std::cout << "Radius: " << calc.getRadius(circle) << std::endl;
    return 0;
}
