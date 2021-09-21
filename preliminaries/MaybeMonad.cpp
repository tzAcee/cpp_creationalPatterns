#include <iostream>

template <typename T> struct Maybe;

template <typename T> Maybe<T> maybe(T* context)
{
	return Maybe<T>(context);
}

template <typename T> struct Maybe 
{
	T* context;

	explicit Maybe(T* const context) :context{context}
	{

	}

	template <typename Func>
	auto With(Func evaluator)
	{
		if (context == nullptr)
		{
			return Maybe<typename std::remove_pointer<decltype(evaluator(context))>::type>(nullptr);
		}
		else
		{
			return maybe(evaluator(context));
		}
	}

	template <typename Func>
	auto Do(Func action)
	{
		if (context != nullptr) action(context);
		return *this;
	}
};

struct Address
{
	std::string* house_name = nullptr;
};

struct Person
{
	Address* address = nullptr;
};

void print_house_name(Person* p)
{
	//if(p != nullptr && p->adress != nullptr && p->adress->house_name != nullptr)
	//	std::cout << *p->adress->house_name << '\n';

	maybe(p)
		.With([](auto x) { return x->address; })
		.With([](auto x) { return x->house_name; })
		.Do([](auto x) { std::cout << *x << '\n'; });
}

int main()
{
	Person p;
	p.address = new Address;
	p.address->house_name = new std::string("name");
	print_house_name(&p);

	delete p.address->house_name;
	delete p.address;

	return 0;
}