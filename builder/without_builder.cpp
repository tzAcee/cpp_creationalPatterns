#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

using namespace std;

int no_main()
{
	// <p>hello<\p>
	auto text = "hello";
	string output;
	output += "<p>";
	output += text;
	output += "</p>";

	cout << output << '\n';

	printf("<p>%s</p>\n", text);

	// <ul><li>hello<\li><li>world<\li><\ul>
	string words[] = { "hello", "world" };
	ostringstream oss;
	oss << "<ul>";
	for (auto w : words)
	{
		oss << " <li>" << w << "</li>";
	}
	oss << " </ul>\n";
	printf(oss.str().c_str());

	getchar();
	return 0;
}