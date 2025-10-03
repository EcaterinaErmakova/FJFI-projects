#include <utility>

namespace my {

namespace detail {

// dopredna deklarace
template< std::size_t I, class... Types >
class storage;

// specializace pro pripad s aspon jednim prvkem
template< std::size_t I, class Head, class... Tail >
class storage<I, Head, Tail...>
: public storage<I + 1, Tail...>
{
private:
    // atribut prvniho typu z posloupnosti
    Head value;

public:
    storage() = default;

    storage(Head head, Tail... tail)
    : value(head), storage<I + 1, Tail...>(tail...)
    {}

    // pristupova metoda
    Head& get(std::integral_constant<std::size_t, I> tag)
    {
        /* tohle nefunguje
        if (I == 0)
            return value;
        else 
            return storage<Tail...>::get(I - 1);
        */
       return value;
    }

    // zpristupnit metody get z predku
    using storage<I + 1, Tail...>::get;
};

// specializace pro prazdnou posloupnost
template<std::size_t I>
class storage<I>
{
public:
    storage() = default;

    void get() {}
};

}

template< class... Types >
class tuple
: public detail::storage<0, Types...>
{
    // tohle nefunguje:
    //Types... atributes;

public:
    tuple() = default;

    // konstruktor s parametry
    tuple(Types... values)
    : detail::storage<0, Types...>( values... )
    {}
};

// pouziti "...":
// 1. sizeof...(Types)
// 2. expandovani: Types...

template< std::size_t I, class... Types >
auto& get(tuple<Types...>& tpl)
{
    using tag = std::integral_constant<std::size_t, I>;
    return tpl.get(tag());
}

} // namespace my