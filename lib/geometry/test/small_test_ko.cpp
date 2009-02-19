template <typename>
struct foo
{ typedef double type; };

template <typename, typename>
struct bar
{ typedef double type; };


template <typename A>
struct return_type
{ typedef typename bar<typename foo<A>::type, double>::type type; };


template <typename A>
typename return_type<A>::type
func1(A);

template<typename A>
typename bar<typename foo<A>::type, typename foo<typename A::some_type>::type>::type
func2(A);

template <typename A>
typename return_type<A>::type
func3(A)
{ return 0; }


int main()
{
	func3(0);
	return 0;
}
