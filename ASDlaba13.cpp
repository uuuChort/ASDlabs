#include <iostream>
#include <vector>
#include <string>
#include <fstream>


void getData(std::string& data, std::ifstream& file)
{
	if (file.is_open())
	{
		std::string line;

		while (std::getline(file, line))
		{
			data += line;
		}
	}
	else
	{
		std::cout << "File can't open!" << std::endl;
	}

}

int inTable(std::vector<std::pair<char, int>>& table, char c)// Создание таблицы
{
	int result = -1;

	for (int i = 0; i < table.size(); i++)
	{
		if (c == table[i].first)
		{
			result = i;
		}
	}

	return result;
}

int BM(std::string& text, std::string& pattern)
{
	int result = -1;
	std::vector<std::pair<char, int>> table;

	for (int i = pattern.size() - 2; i >= 0; i--)
	{
		if (inTable(table, pattern[i]) == -1)
		{
			table.push_back({ pattern[i], pattern.size() - i - 1 });
		}
	}

	if (!inTable(table, pattern[0]))
	{
		table.push_back({ pattern[0],pattern.size() - 1 });
	}

	int i = pattern.size() - 1;

	while (i < text.size())
	{
		int k = 0;

		int j = pattern.size() - 1;
		for (; j != 0; --j)
		{
			int off = 0;

			if (text[i - k] != pattern[j])
			{
				if (j == pattern.size() - 1)
				{
					int d = inTable(table, text[i]);
					off = d != -1 ? table[d].second : pattern.size();
				}
				else
				{
					int pos = inTable(table, pattern[j]);
					off = table[pos].second;
				}

				i += off;
				break;
			}

			k++;
		}

		if (j == 0)
		{
			result = i - k + 1;
			break;
		}
	}

	return result;
}


void main()
{
	std::ifstream file;
	file.open("text_dm.txt");

	std::string text = "";
	getData(text, file);

	setlocale(LC_ALL, "rus");

	std::cout << "Введите строку для поиска: ";

	std::string pattern;
	std::cin >> pattern;

	std::cout << BM(text, pattern) << std::endl; 
}

