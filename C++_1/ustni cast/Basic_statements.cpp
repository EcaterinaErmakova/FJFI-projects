
#include <iostream>
int main(){
    int x = 1;

    // if statement executes code based on conditions
    if (x==0) {std::cout << 0;}
    else if (x==1) {std::cout << 1;}
    else {std::cout << -1;}
    // switch statement executes code based on conditions
    switch (x) {
        case 0:
            std::cout << 0;
            break;
        case 1:
            std::cout << 1;
            break;
        default:
            std::cout << -1;
    }
    
    // while loop: repeats while condition is true
    while (x <= 3) {
        std::cout << x << ", ";
        x++;
    }// output: 1, 2, 3
    // for loop: best for known number of iterations
    for (int i = 1; i <= 5; i++) {std::cout << i << " ";}
    // do-while loop: executes at least once
    do {x+=1;} while (x == 1);

    return 0;
}