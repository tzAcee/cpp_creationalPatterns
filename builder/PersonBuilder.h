#pragma once
#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilder
{
private:
	Person p;
protected:
	Person& person;

	explicit PersonBuilder(Person& person)
		: person{person}
	{
	}
public:
	PersonBuilder() : person{p}
	{}

	operator Person()
	{
		return move(person);
	}

	PersonAddressBuilder lives();
	PersonJobBuilder works();
};
