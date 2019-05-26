#include <stdio.h>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main()
{
	vector<string> input = { "bob pizza pizza pasta", "steve pizza pizza test1 test2", "bob pizza" };
	map<string, map<string, int>> menus;

	for (string str : input)
	{
		int name_len = str.find(" ");
		string name = str.substr(0, name_len);

		for (int i = name_len + 1; ; )
		{
			int menu_len = str.find(" ", i) - i;
			string menu = str.substr(i, menu_len);

			menus[name][menu] = 1;

			if (menu_len < 0)
				break;

			i += menu_len + 1;
		}
	}

	string top_name;
	int top_size = 0;
	for (auto pair : menus)
	{
		if (top_size < pair.second.size())
		{
			top_name = pair.first;
			top_size = pair.second.size();
		}
	}

	printf("%s\n", top_name.c_str());

	return 0;
}