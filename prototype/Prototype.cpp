
#include <vector>
#include <string>
#include <iostream>
#include <ostream>

using namespace std;

struct Address
{
	string street;
	string city;
	int suite;

	friend std::ostream& operator<<(std::ostream& os, const Address& obj)
	{
		return os
			<< "street: " << obj.street
			<< " city: " << obj.city
			<< " suite: " << obj.suite;
	}
};

struct Contact
{
	string name;
	Address* work_address;

	Contact(const string& name, Address* work_address)
		: name{name},
		  work_address{new Address{*work_address}}
	{
	}

	~Contact()
	{
		delete work_address;
	}

	Contact(const Contact& other) :name {other.name}, work_address{new Address{*other.work_address}}
	{
		
	}

	friend std::ostream& operator<<(std::ostream& os, const Contact& obj)
	{
		return os
			<< "name: " << obj.name
			<< " work_address: " << *obj.work_address;
	}
};

struct EmployeeFactory
{
	static Contact main, aux;

	static unique_ptr<Contact> NewMainOfficeEmployee(const string &name, const int suite)
	{
		//static const Contact employee{ "", new Address{"123 East Dr", "London", 0} };
		//return make_unique<Contact>(employee);
		return NewEmployee(name, suite, main);
	}

	static unique_ptr<Contact> NewAuxOfficeEmployee(const string& name, const int suite)
	{
		//static const Contact employee{ "", new Address{"123 East Dr", "London", 0} };
		//return make_unique<Contact>(employee);
		return NewEmployee(name, suite, aux);
	}

private:
	static unique_ptr<Contact> NewEmployee(const string& name, const int suite, Contact &proto)
	{
		auto result = make_unique<Contact>(proto);
		result->name = name;
		result->work_address->suite = suite;

		return result;
	}
};

Contact EmployeeFactory::main{ "", new Address{"123 East Dr", "London", 0} };
Contact EmployeeFactory::aux{ "", new Address{"123B East Dr", "London", 0} };

int main()
{


	//Contact john{ employee };
	//john.name = "John";
	//john.work_address->suite = 100;

	//Contact jane{ employee };
	//jane.name = "Jane";
	//jane.work_address->suite = 123;

	//cout << jane << '\n' << john << '\n';

	////////////////////////
	auto john = EmployeeFactory::NewMainOfficeEmployee("John", 100);
	auto jane = EmployeeFactory::NewAuxOfficeEmployee("Jane", 123);

	std::cout << *jane << '\n' << *john <<'\n';

	getchar();
	
	return 0;
}
