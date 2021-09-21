#pragma once
#include <functional>
#include <map>
#include <string>

#include "CoffeeFactory.h"
#include "HotDrinkFactory.h"
#include "TeaFactory.h"

using namespace std;

struct HotDrink;

struct DrinkFactory
{
	std::map<std::string, unique_ptr<HotDrinkFactory>> factories;
public:
	DrinkFactory()
	{
		factories["coffee"] = make_unique<CoffeeFactory>();
		factories["tea"] = make_unique<TeaFactory>();
	}

	unique_ptr<HotDrink> make_drink(const string& name)
	{
		auto drink = factories[name]->make();
		drink->prepare(200); // not specified yet.
		return drink;
	}
};

class DrinkWithVolumeFactory
{
	map<string, function<unique_ptr<HotDrink>()>> factories;
public:
	DrinkWithVolumeFactory()
	{
		factories["tea"] = []
		{
			auto tea = make_unique<Tea>();
			tea->prepare(100);
			return tea;
		};
	}

	unique_ptr<HotDrink> make_drink(const string& name)
	{
		return factories[name]();
	}
};