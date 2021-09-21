#include <vector>
#include <string>
#include <fstream>

struct Journal
{
	std::string Title;
	std::vector<std::string> Entries;

	explicit Journal(const std::string& title) : Title{ title }
	{

	}

	void add(const std::string& entry)
	{
		Entries.push_back(entry);
	}

	// save() in eigene Klasse -> Single Resposibility Priciple.
};

struct PersistenceManager
{
	static void save(const Journal& j, const std::string& filename)
	{
		std::ofstream ofs(filename);

		for (auto& s : j.Entries)
		{
			ofs << s << std::endl;
		}

		ofs.close();
	}
};