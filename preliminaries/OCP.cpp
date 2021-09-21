#include <string>
#include <vector>
#include <iostream>

enum class Color	{ Red, Green, Blue};
enum class Size		{ Small, Medium, Large };

struct Product 
{
	std::string Name;
	Color Color;
	Size Size;
};

struct ProductFilter
{
	typedef std::vector<Product*> Items;

	static Items by_color(const Items& items, Color filter_color)
	{
		Items result;
		for (auto& i : items)
		{
			if (i->Color == filter_color)
			{
				result.push_back(i);
			}
		}

		return result;
	}

	static Items by_size(const Items& items, Size filter_size)
	{
		Items result;
		for (auto& i : items)
		{
			if (i->Size == filter_size)
			{
				result.push_back(i);
			}
		}

		return result;
	}

	static Items by_size_and_color(const Items& items, Size filter_size, Color filter_color)
	{
		Items result;
		for (auto& i : items)
		{
			if (i->Size == filter_size && i->Color == filter_color)
			{
				result.push_back(i);
			}
		}

		return result;
	}
};

////// /|\ : Open for Modification, Closed for Extension
/////  \|/ : Closed for Modification, Open for Extension  -> Open-Closed Principle

template <typename T> struct ISpecification
{
	virtual bool is_satisfied(T* item) = 0;
};

template <typename T> struct IFilter
{
	virtual std::vector<T*> filter(std::vector<T*> items, ISpecification<T>& spec) = 0;
};

struct BetterFilter : IFilter<Product>
{
	typedef std::vector<Product*> Items;
	std::vector<Product*> filter(std::vector<Product*> items, ISpecification<Product>& spec) override
	{
		Items result;
		for (auto& p : items)
		{
			if (spec.is_satisfied(p))
			{
				result.push_back(p);
			}
		}
		return result;
	}
};

struct ColorSpecification : ISpecification<Product>
{
	Color color;
	explicit ColorSpecification(const Color color) : color(color)
	{

	}

	bool is_satisfied(Product* item) override 
	{
		return item->Color == color;
	}
};

template <typename T> struct AndSpecification : ISpecification<T>
{
	ISpecification<T>& first;
	ISpecification<T>& second;

	AndSpecification(ISpecification<T>& first, ISpecification<T>& second) : first(first), second(second)
	{

	}

	bool is_satisfied(T* item) override 
	{
		return first.is_satisfied(item) && second.is_satisfied(item);
	}
};

struct SizeSpecification : ISpecification<Product>
{
	Size size;
	explicit SizeSpecification(const Size size) : size(size)
	{

	}

	bool is_satisfied(Product* item) override
	{
		return item->Size == size;
	}
};

int _main()
{
	Product apple	{ "Apple", Color::Green, Size::Small };
	Product tree	{ "Tree", Color::Green, Size::Large };
	Product house	{ "House", Color::Blue, Size::Large };

	std::vector<Product*> all{ &apple, &tree, &house };

	BetterFilter bf;
	ColorSpecification green(Color::Green);

	auto green_things = bf.filter(all, green);

	for (auto& x : green_things)
	{
		std::cout << x->Name << " is green." << '\n';
	}

	SizeSpecification large(Size::Large);
	AndSpecification<Product> large_green{ green, large };

	auto green_large_things = bf.filter(all, large_green);
	for (auto& x : green_large_things)
	{
		std::cout << x->Name << " is green and large." << '\n';
	}


	getchar();

	return 1;
}