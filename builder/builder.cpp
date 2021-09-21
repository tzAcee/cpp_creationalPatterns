#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

using namespace std;

class html_builder;

struct html_element
{
	string name;
	string text;
	vector<html_element> elements;
	const size_t indent_size = 2;

	html_element() = default;

	html_element(const string& name, const string& text)
		: name{name},
		  text{text}
	{
	}

	string str(int indent = 0) const
	{
		ostringstream oss;
		string i(indent_size * indent, ' ');
		oss << i << "<" << name << ">" << '\n';

		if(text.size() > 0)
		{
			oss << string(indent_size * (indent + 1), ' ') << text << '\n';
		}

		for(const auto &e : elements)
		{
			oss << e.str(indent + 1);
		}

		oss << i << "</" << name << ">" << '\n';

		return oss.str();
	}

	static html_builder build(const string& root_name);

	static unique_ptr<html_builder> create(const string& root_name);
};


struct html_builder
{
	html_element root;

	explicit html_builder(const string& root_name)
	{
		root.name = root_name;
	}

	html_builder& add_child(const string& child_name, const string& child_text)
	{
		html_element e{ child_name, child_text };
		root.elements.emplace_back(e);

		return *this;
	}

	html_builder* add_child_2(const string& child_name, const string& child_text)
	{
		html_element e{ child_name, child_text };
		root.elements.emplace_back(e);

		return this;
	}

	string str() const
	{
		return root.str();
	}

	operator html_element() const { return root; }
};

html_builder html_element::build(const string& root_name)
{
	return html_builder{ root_name };
}

static unique_ptr<html_builder> create(const string& root_name)
{

	return make_unique<html_builder>(root_name);
}

int main_()
{
	html_builder builder{ "ul" };
	builder
		.add_child("li", "hello")
		.add_child("li", "world");

	html_element e = html_element::build("ul")
				.add_child("li", "hello")
				.add_child("li", "world");

	//auto ee = html_element::create("ul")->add_child_2("", "")->add_child_2("", "");

	cout << e.str() << '\n';

	getchar();
	return 0;
}