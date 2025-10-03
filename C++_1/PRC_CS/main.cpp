#include "CaesarCode.h"
#include "CaesarCode.cpp"
#include <iostream>
#include <limits>
/*
In cryptography, a Caesar cipher, also known as Caesar's cipher, the shift cipher, 
Caesar's code, or Caesar shift, is one of the simplest and most widely known 
encryption techniques. It is a type of substitution cipher in which each letter in 
the plaintext is replaced by a letter some fixed number of positions down the alphabet. 
For example, with a left shift of 3, D would be replaced by A, E would become B, and so on.
The method is named after Julius Caesar, who used it in his private correspondence.

The action of a Caesar cipher is to replace each plaintext letter with a different one a 
fixed number of places down the alphabet. 
The cipher illustrated here uses a left shift of 3, so that (for example) each occurrence 
of E in the plaintext becomes B in the ciphertext.
*/

int main() {
    // File needed to creat dictionary from list of the most poppular words in english.
    CaesarCode file("google-10000-english-2.txt");
    // Ask user, if he wants to code or decode the text. 
    std::cout << "Choose action (number):\n1. Code\n2. Decode\n\n";
    // Define and enter user's chosen option.
    int option;
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    if (option == 1) {
        // Code the text.
        file.code_text();
    }
    else if (option == 2) {
        // Decode the text
        file.decode_text();
    }
    else {
        std::cout << "Invalid choice!" << std::endl;
        return 1;
    }
    return 0;
}