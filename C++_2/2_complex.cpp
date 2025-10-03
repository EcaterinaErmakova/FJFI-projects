

// definice tridy pro komplexni cislo
class complex
{
private:
    // atributy
    double real;
    double imag;
public:
    // konstruktor
    /*
    complex(double r, double i)
    {
        real = r;
        imag = i;
    }
    */

    // konstruktor
    complex(double r = 0, double i = 0)
    : real(r), imag(i)
    {}

    // pristupove metody ("gettery")
    double get_real()
    {
        return real;
    }
    double get_imag()
    {
        return imag;
    }

    // nastavovaci metody ("settery")
    void set_real(double r)
    {
        real = r;
    }
    void set_imag(double i)
    {
        imag = i;
    }

    // operator pro odcitani komplexnich cisel (varianta jako metoda v tride)
    // pocita vyraz "this - c"
    complex operator-(complex c)
    {
        /*
        complex result;
        result.real = real - c.real;
        result.imag = imag - c.imag;
        return result;
        */
        return (*this) - c ; // return (*this) + (-c);
    }

    // unarni minus
    complex operator-() const
    {
        complex result;
        result.real = -real;
        result.imag = -imag;
        return result;
    }

    // definujte vsechny nasledujici operatory:
    // - unarni plus
    // - nasobeni a deleni komplexnich cisel
    // - vsechny operatory "@" pro "komplexni @ realne" a "realne @ komplexni"


    // porovnávací operátory
    bool operator==(complex c)
    {
        return real == c.real && imag == c.imag;
    }

    bool operator!=(complex c)
    {
        // zavoláme operator== jako funkci/metodu
        //return ! operator==(c);

        // "klasické" použití operátoru
        return ! (*this == c);
    }
};


// funkce pro scitani komplexnich cisel
complex add(complex c1, complex c2)
{
    complex c3;
    c3.set_real(c1.get_real() + c2.get_real());
    c3.set_imag(c1.get_imag() + c2.get_imag());
    return c3;
}

// operator pro scitani komplexnich cisel
complex operator+(complex c1, complex c2)
{
    complex c3;
    c3.set_real(c1.get_real() + c2.get_real());
    c3.set_imag(c1.get_imag() + c2.get_imag());
    return c3;
}


int main()
{
    // realne cislo
    double x = 1.5;

    // komplexni cislo
    //double r = 1;
    //double i = 1;
    complex c(1, 1);
    complex c2(1);
    complex c3;

    // vypocty
    complex c4;  // provedte soucet c a c2
    //c4.set_real(c.get_real() + c2.get_real());
    //c4.set_imag(c.get_imag() + c2.get_imag());
    c4 = add(c, c2);
    // soucet c4 = c + (c2 + c3)
    c4 = add(c, add(c2, c3));
    c4 = c + c2 + c3;

    int a;
    a = 1 + 2 + 3;  // to same jako a = ((1 + 2) + 3)


    complex c5;
    c5 = -c2;
}