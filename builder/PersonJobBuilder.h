#pragma once
#include "PersonBuilder.h"

class PersonJobBuilder:public PersonBuilder
{
	typedef PersonJobBuilder Self;
public:
	explicit PersonJobBuilder(Person& person)
		: PersonBuilder{person}
	{
	}

	Self& at(const string& company_name)
	{
		person.company_name = company_name;
		return *this;
	}

	Self& as_a(const string& position)
	{
		person.position = position;
		return *this;
	}

	Self& earning(const int income)
	{
		person.annual_income = income;
		return *this;
	}
};
