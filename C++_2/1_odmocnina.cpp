#include <iostream>

double odmocnina(double x, double epsilon = 1e-15)
{
    if (x < 0) {
        // 1. moznost: vratit specialni hodnotu
        //return -1;
        //return NAN;
        // 2. moznost: pocitat komplexni cislo
        //x = -x; // spocitat odmocninu a potom zpatky pridat minus
        // 3. moznost: vyvolat vyjimku
        throw std::invalid_argument("x nesmi byt zaporne");
        //throw std::logic_error("x nesmi byt zaporne");
    }

    double a;
    double b;
    if (x > 1) {
        a = 1;
        b = x;
    }
    else {
        a = x;
        b = 1;
    }

    while (b - a > epsilon) {
        double c = (a + b) / 2;
        if (c*c < x) {
            a = c;
        }
        else {
            b = c;
        }
    }

    return a; // nebo klidne b nebo pulka mezi a,b
}

int main()
{
    double x = 5;
    double y = odmocnina(x);
    double z = sqrt(x);

    std::cout << "odmocnina z " << x << " je " << y << std::endl;
    std::cout << "sqrt z " << x << " je " << z << std::endl;
    std::cout << "chyba vysledku je " << z - y << std::endl;
}