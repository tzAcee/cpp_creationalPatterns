#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <ostream>


class Point
{
private:
	Point(float x, float y)
		: x{ x },
		y{ y }
	{
	}
public:
	float x, y;

	static Point NewCartesian(const float x, const float y)
	{
		return { x,y };
	}

	static Point NewPolar(const float r, const float theta)
	{
		return { r * cos(theta), r * sin(theta) };
	}

	friend std::ostream& operator<<(std::ostream& os, const Point& obj)
	{
		return os
			<< "x: " << obj.x
			<< " y: " << obj.y;
	}
};

int _main()
{
	auto c = Point::NewCartesian(1, 2);
	std::cout << c << std::endl;

	auto p = Point::NewPolar(5, M_PI_4);
	std::cout << p << std::endl;

	getchar();
	return 0;
}