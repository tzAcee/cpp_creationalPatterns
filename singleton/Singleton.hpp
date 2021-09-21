#pragma once
#include <fstream>
#include <iostream>
#include <string>

class SingletonDatabase
{
	SingletonDatabase()
	{
		std::cout << "Database init" << '\n';

		std::ifstream ifs("capitals.txt");

		std::string s, s2;
		while (std::getline(ifs, s))
		{
			std::getline(ifs, s2);
		}

	}

	std::map<std::string, int > capitals;

};
