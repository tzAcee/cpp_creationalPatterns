#include "boost_di_lib.h"
#include <iostream>
#include <memory>

struct ILogger
{
	virtual ~ILogger()
	{}

	virtual void Log(const std::string& s) = 0;
};

struct ConsoleLogger : ILogger
{
	void Log(const std::string& s) override
	{
		std::cout << "LOG: " << s.c_str() << '\n';
	}
};

struct Engine
{
	float volume = 5.0f;
	int horse_power = 400;

	friend std::ostream& operator<<(std::ostream& os, const Engine& obj)
	{
		return os
			<< "volume: " << obj.volume
			<< " horse_power: " << obj.horse_power;
	}
};

struct Car
{
	std::shared_ptr<Engine> engine;
	std::shared_ptr<ILogger> logger;

	explicit Car(const std::shared_ptr<Engine>& engine, const std::shared_ptr<ILogger>& logger) : engine{ engine }, logger{ logger }
	{
		this->logger->Log("Created a car.");
	}

	friend std::ostream& operator<<(std::ostream& os, const Car& obj)
	{
		return os << "car with engine: " << *obj.engine;
	}
};

int ___main()
{
	//auto e = std::make_shared<Engine>();
	//auto c = std::make_shared<Car>(e);

	using namespace boost;
	auto injector = di::make_injector(
		di::bind<ILogger>().to<ConsoleLogger>()
	);
	auto c = injector.create<std::shared_ptr<Car>>();

	std::cout << *c << '\n';

	getchar();

	return 0;
}