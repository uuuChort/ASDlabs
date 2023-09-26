#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

typedef std::vector<std::vector<int>> graph;

int to_int(std::string str)
{
	int result = 0;
	if (str.size() == 2)
	{
		result = (str[0] - 48) * 10 + str[1] - 48;
	}
	else if (str.size() == 1)
	{
		result = str[0] - 48;
	}

	return result;
}


void fillMatrix(graph& matrix, std::ifstream& file, int n)
{
	if (file.is_open())
	{
		std::string line;
		int  k = 0;

		while (std::getline(file, line)) // заполение матрицы смежности
		{
			int cnt = 0;

			for (int i = 0; i < n - 1; i++)
			{
				int g = 0;

				if (line[i] == ' ')
				{
					for (int j = i + 1; j < line.size(); j++)
					{
						if (line[j] == ' ')
						{
							std::string test = line.substr(i + 1, j - i - 1);
							matrix[k][g] = to_int(line.substr(i + 1, j - i - 1));
							i = j;
							g++;
						}
					}
				}
			}

			k++;
		}
	}
	else
	{
		std::cout << "Error open file!" << std::endl;
	}
}


int countingTops(std::ifstream& file)
{
	int tops = 0;

	if (file.is_open())
	{
		file.seekg(0); // Вернул указаетль на начало файла.
		std::string line;

		while (std::getline(file, line))
		{
			tops++;
		}
	}
	else
	{
		std::cout << "Error open file!" << std::endl;
	}

	return tops;
}

bool isAllChecked(std::vector<bool> used)
{
	bool result = true;

	for (auto c : used)
	{
		if (c == false)
		{
			result = false;
		}
	}

	return result;
}

void dijstra(graph& matrix, int s, std::vector<int>& d, std::vector<bool>& used)
{
	int minValue = 10000;
	int c = s; //Текущая обрабатываемая верщина
	d[s] = 0;

	for (int i = 0; i < d.size(); i++) // Ставим очень большое расстояние для всех вершин так как ищем min
	{
		if (used[i] == false && d[i] < minValue)
		{
			c = i;
			minValue = d[i];
		}
	}

	for (int i = 0; i < matrix[c].size(); i++) //выбираем лучший вариант для min расстояния
	{
		if (matrix[c][i] != 0 && d[i] > d[c] + matrix[c][i])
		{
			d[i] = d[c] + matrix[c][i];
		}
	}

	used[c] = true;
}


void main()
{
	std::ifstream file;
	file.open("weigthed_graph.txt");
	int n = countingTops(file);//кол-во вершин в графе
	file.close();
	file.open("weigthed_graph.txt");
	graph matrix(n, std::vector<int>(n));
	fillMatrix(matrix, file, n);
	std::vector<bool> used(n);
	std::vector<int> d(n);

	for (int i = 0; i < d.size(); i++)
	{
		d[i] = 10000;
	}
	int s = 0; //Расстояние от текущей вершины

	while (!isAllChecked(used)) // Пока не посетили все вершины
	{
		dijstra(matrix, s, d, used); //Ищем для выбранной вершины min расстояние
	}

	for (auto dist : d)
	{
		std::cout << dist << std::endl;
	}
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
