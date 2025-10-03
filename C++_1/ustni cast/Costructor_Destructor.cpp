#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int* ratings;
    int ratingCount;
public:
    // Constructor
    Book(std::string t, std::string a, int rCount) {
        title = t;
        author = a;
        ratingCount = rCount;
        ratings = new int[ratingCount];
    }
    // Copy constructor (deep copy)
    Book(const Book& copy) {
        // Copy data
        title = copy.title;
        author = copy.author;
        ratingCount = copy.ratingCount;
        // Deep copy of dynamic array
        ratings = new int[ratingCount];
        for (int i = 0; i < ratingCount; i++) {ratings[i] = copy.ratings[i];}
        //std::cout << "Copy constructor called" << std::endl;
    }
    // Destructor
    ~Book() {
        delete[] ratings;
        //std::cout << "Destructor called for " << title << std::endl;
    }
};


// Creating objects
int main() {
    Book book1 ("1984", "George Orwell", 3);
    Book book2 = book1;  // Copy constructor called
    return 0; // Destructors called automaticaly
}