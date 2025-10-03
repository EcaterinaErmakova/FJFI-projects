#include <iostream>

class vector
{
    long size;
    double* data;

    void allocate(long n)
    {
        data = new double[n];
        size = n;
    }

public:
    // konstruktory
    vector()
    {
        size = 0;
        data = nullptr;
    }

    vector(long n)
    {
        data = new double[n];
        size = n;
    }

    vector(long n, double a)
    {
        data = new double[n];
        size = n;

        for (long i = 0; i < n; i++) {
            data[i] = a;
        }
    }

    // kopírovací konstruktor
    vector(const vector& v)
    {
        size = v.get_size();
        data = new double[size];

        for (long i = 0; i < size; i++) {
            data[i] = v.data[i];
        }

        std::cout << "copy-constructor" << std::endl;
    }

    // přiřazovací operátor (copy-assignment)
    vector& operator=(const vector& v)
    {
        // pokud mají objekty stejnou identitu, není potřeba dělat nic
        if (this == &v) {
            return *this;
        }

        // napřed zajistit správnou velikost
        if (get_size() != v.get_size()) {
            // nelze dealokovat nullptr
            if (data != nullptr) {
                delete[] data;
            }
            size = v.get_size();
            data = new double[size];
        }

        // zkopírovat data
        for (long i = 0; i < size; i++) {
            data[i] = v.data[i];
        }

        return *this;
    }

    // "stěhovací" konstruktor (move-constuctor)
    vector(vector&& v)
    {
        size = v.size;
        data = v.data;
        v.size = 0;
        v.data = nullptr;

        std::cout << "move-constructor" << std::endl;
    }

    // "stěhovací" přiřazení (move-assignment)
    vector& operator=(vector&& v)
    {
        // napřed zajistit správnou dealokaci
        if (data != nullptr) {
            delete[] data;
        }
        
        size = v.size;
        data = v.data;
        v.size = 0;
        v.data = nullptr;

        std::cout << "move-assignment operator" << std::endl;

        return *this;
    }

    // destruktor
    ~vector()
    {
        // dealokace
        delete[] data;
        
        std::cout << "destructor" << std::endl;
    }

    long get_size() const
    {
        return size;
    }

    // přístup k prvkům
    //double getElement(long i) {...}
    //void setElement(long i, double x) {...}
    double operator[](long i) const
    {
        return data[i];
    }

    // "read-write" přístup k prvkům
    // vector v(10);
    // v[0] = 0;
    // v[0] += 1;
    double& operator[](long i)
    {
        return data[i];
    }

    // další možnosti:
    // - resize
    // - iterace

    // scitaci operator
    vector operator+(const vector& v) const
    {
        if (get_size() != v.get_size()) {
            throw std::invalid_argument("vectors must have the same size");
        }

        vector result(get_size());

        for (long i = 0; i < get_size(); i++) {
            //... = operator[](i) + v[i];
            result[i] = (*this)[i] + v[i];
        }

        return result;
    }
};

// operátor pro výpis
// vector v(10);
// std::cout << v << std::endl;
// napište kód, aby se vypsalo tohle:   [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
std::ostream& operator<<(std::ostream& stream, const vector& v)
{

    for (long i = 0; i < v.get_size(); i++) {
        stream << v[i] << ' ';
    }
    stream << '\n';

    return stream;
}

int main()
{
    long n = 10;

    vector v1(n);
    vector v2(n);

    // inicializace
    for (long i = 0; i < n; i++) {
        v1[i] = 1;
        v2[i] = i;
    }

    // pro vyrazy 'v1 + v2' atd. je potreba doplnit odpovidajici operatory

    // kopirovaci konstruktor
    vector v3 = v2;
    vector v4(v2);
    vector v5;
    v5 = v2;  // tohle vola operator=, ne konstruktor

    // move konstruktor
    vector v6 = std::move(v5);
    // ted je v5 prazdny vektor!!!
    std::cout << v5.get_size() << std::endl;

    vector v7 = v1 + v2; // zde vznika docasny objekt a automaticky se vola move-constructor
    v4 = v1 + v2; // zde vznika docasny objekt a vola se move-assignment

}
