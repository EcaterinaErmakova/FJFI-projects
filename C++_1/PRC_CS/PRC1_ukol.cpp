
#include <cctype>
#include <cctype>
#include <cstddef>
#include <iostream>



int get_max(const std::vector<int>& array)
{
    int max=array[0];
    for (int i: array){
        if(i>max){max=i;}
    }
    return max;
}

int main()
{
    int size;
    std::cout << "Enter size of list: "<<std::endl;
    std::cin >> size;

    std::vector<int> list(size);
    std::cout << "Enter list of numbers:\n";
    for (int i = 0; i < size; ++i) {std::cin >> list[i];}
    std::cout<<"Max number is: "<<get_max(list);
};
