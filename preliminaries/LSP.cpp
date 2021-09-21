#include <iostream>


class Rectangle
{
protected:
	int width, height;
public:
	Rectangle(const int width, const int height) : width(width), height(height)
	{

	}

	virtual int get_width() const
	{
		return width;
	}

	virtual int get_height() const
	{
		return height;
	}

	virtual void set_width(const int width)
	{
		this->width = width;
	}

	virtual void set_height(const int height)
	{
		this->height = height;
	}

	int Area() const { return width * height; }
};

class Square : public Rectangle
{
public:
	Square(int size) : Rectangle{ size, size }
	{

	}

	void set_width(const int width) override
	{
		this->width = height = width;
	}

	void set_height(const int height) override
	{
		this->height = width = height;
	}
};

void process(Rectangle& r)
{
	int w = r.get_width();
	r.set_height(10);

	std::cout << "expect area = " << (w * 10) << ", got " << r.Area()<<'\n';
}


// Solution in Init:
struct RectangleFactory
{
	static Rectangle create_rectangle(int width, int height);
	static Rectangle create_square(int size);
};

// Solution in processing: - no override; - square specific function (e.g. set_size())

int __main()
{
	Rectangle r{ 5,5 };
	process(r);

	Square s{ 5 };
	process(s);

	getchar();

	return 0;
}