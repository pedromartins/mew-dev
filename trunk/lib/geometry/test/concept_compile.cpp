#include <iostream>
#include <boost/concept/requires.hpp>


template <typename T>
struct foo
{};

template <class X>
struct DummyConcept
{
       typedef typename X::something something;
};


template<typename T>
BOOST_CONCEPT_REQUIRES(((DummyConcept<T>)),
(void)) for_each_point(T&)
//void for_each_point(T&)
{ std::cout << "first overload" << std::endl; }

template<typename T>
void for_each_point(foo<T>)
{ std::cout << "second overload" << std::endl; }


int main()
{
       for_each_point(foo<int>());

       return 0;
}
