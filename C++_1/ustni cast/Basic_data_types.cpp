#include <string>

void Basic_data_types(){
    int age = 21; // stores whole numbers: 2-4 bytes
    float gpa = 3.75f; // stores floating-point numbers with 6-7 decimal digits precision: 4 bytes
    double pi = 3.14159265359; // stores floating-point numbers with 15 decimal digits precision: 8 bytes
    char grade = 'A'; // stores single characters: 1 byte
    bool isPassing = true; // stores true or false values: 1 byte
    std::string name = "John"; // stores text
    return;
}

int global_var; // global variables declared outside all functions
int x = 0; 
int lok_glob_var(){
    int lokal_var; // lokal variables declared inside functions or blocks 
    lokal_var = global_var; 
    /* Variable Shadowing: When local and global variables have the same name () */
    int x = 1;
    return x; // return 1 (local priority)
} 
// global variables are accessible throughout the program
// lokal variables are only accessible within that scope