/*
vstup:  std::vector<std::string>  a std::string x
algoritmus/vlastni funkce...
vystup: std::vector<std::string> obsahujici jen ty stringy, ktere obsahuji dany podretezec x
*/
#include <iostream>
#include <string>
#include <vector>
/*
std::vector<std::string> filter(const std::vector<std::string>& input, std::string x)
{
    std::vector<std::string> result;
    for (std::string word : input) {
        // od C++23
        //if (word.contains(x))
        if (word.find(x) != std::string::npos)
            result.push_back(word);
    }
    return result;
}
*/
template <typename Function>
std::vector<std::string> filter(const std::vector<std::string>& input, const Function& condition)
{
    std::vector<std::string> result;
    for (std::string word : input) {
        if (condition(word))
            result.push_back(word);
    }
    return result;
}

int main()
{
    std::vector<std::string> input = {
        "hello",
        "world",
        "obsahujici",
        "jen",
        "stringy",
    };
    std::string x = "o";

    //std::vector<std::string> result = filter(input, x);
    std::vector<std::string> result = filter(input,
        [x](std::string w){return w.find(x) != std::string::npos;}
    );
    result = filter(input,
        [](std::string w){return w.size() >= 10;}
    );

    // overeni vysledku
    for (std::string word : result) {
        std::cout << word << std::endl;
    }
}