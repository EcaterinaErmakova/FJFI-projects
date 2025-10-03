//#include <tuple>
#include "11_tuple.h"
#include <string>

int main()
{
    my::tuple<int> t1(1);
    my::tuple<int, double> t2(1, 22.5);
    my::tuple<int, double, std::string> t3(1, 22.5, "hello world");

    // pristup k prvkum v tuple
    my::get<1>(t2) = 2.0;
}