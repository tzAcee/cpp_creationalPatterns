#pragma once

#include <memory>
#include <map>
#include <string>
#include <iostream>

struct HotDrink
{

	virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink
{
	void prepare(const int volume) override
	{
		std::cout << "Take tea bag, boil water, pour " << volume << "ml" << '\n';
 	}
};

struct Coffee : HotDrink
{
	void prepare(const int volume) override
	{
		std::cout << "Grind some beans, boil water, pour " << volume << "ml" << '\n';
	}
};