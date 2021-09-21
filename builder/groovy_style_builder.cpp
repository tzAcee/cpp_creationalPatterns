#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

struct Tag
{
	string name;
	string text;
	vector<Tag> children;
	vector<pair<string, string>> attributes;

	friend std::ostream& operator<<(std::ostream& os, const Tag& tag)
	{
		os << "<" << tag.name;

		for (const auto& att : tag.attributes)
			os << " " << att.first << "=\"" << att.second << "\"";

		if(tag.children.empty() && tag.text.length() == 0)
		{
			os << "\>" << '\n';
		}
		else
		{
			os << ">" << '\n';
			if(tag.text.length())
			{
				os << tag.text << '\n';
			}

			for(const auto&child:tag.children)
			{
				os << child;
			}
			os << "</" << tag.name << ">" << '\n';
		}
		return os;
	}

protected:
	Tag(const string& name, const string& text)
		: name{name},
		  text{text}
	{
	}

	Tag(const string& name, const vector<Tag>& children)
		: name{name},
		  children{children}
	{
	}
};

struct P:Tag
{
	P(const string& text)
		: Tag{"p", text}
	{
	}

	P(initializer_list<Tag> children) :Tag{"p", children}
	{
	}
};

struct IMG :Tag
{
	explicit IMG(const string& url) : Tag{ "img", "" }
	{
		attributes.emplace_back(make_pair("src", url));
	}
};

int _main()
{
	cout <<
		P {
			IMG {"http://a.com/b.png"},
			P { "test"}
		}
	<< '\n';

	getchar();

	return 0;
}
