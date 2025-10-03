#include <iostream>

int main()
{
    int a = 0;
    int b = 1;
    const int c = 2;

    // lambda vyrazy
    auto f = [&a, b, c] // capture list
            (int x) // parametry
            {
                // telo lambda vyrazu
                std::cout << "hello world" << std::endl;

                std::cout << a + x << std::endl;
                a = 10;
            };

    a += b;
    f(42);  // volani lambda funkce/vyrazu
    
    a += b;
    f(42);  // volani lambda funkce/vyrazu
    
    a += b;
    f(42);  // volani lambda funkce/vyrazu
}