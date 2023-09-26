#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>

typedef std::vector<std::vector<int>> graph;

int fillMatrix(graph& matrix, std::ifstream& file, int n)
{
	if (file.is_open())
	{
		file.seekg(0); // Вернул указаетль на начало файла.
		std::string line;
		int i = 0;

		while (std::getline(file, line)) // заполение матрицы смежности
		{
			for (int j = 0; j < n; j++)
			{
				matrix[i][j] = line.at(j) - 48;
			}

			i++;
		}
	}
	else
	{
		std::cout << "Error open file!" << std::endl;
	}

	return matrix.size();
}


bool isAllUsed(std::vector<bool>& tops)
{
	bool result = true;

	for (const auto t : tops)
	{
		if (t == false)
		{
			result = false;
		}
	}

	return result;
}


void dfs(graph& matrix, int s, int n, std::vector<bool>& used, std::vector<int>& d)
{
	if (d.empty())
	{
		d[s]++;
		used[s] = true;
	}

	for (int i = 0; i < matrix[s].size(); i++)
	{
		if (matrix[s][i] != 0 && used[i] == false)
		{
			d[i] = d[s] + 1;
			used[i] = true;
			dfs(matrix, i, n, used, d);
		}
	}
}


int countingTops(std::ifstream& file)
{
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		return line.size();
	}
	else
	{
		std::cout << "Error open file!" << std::endl;
		return -1;
	}
}

void print(std::vector<int> v)
{
	for (const auto c : v)
	{
		std::cout << c << "\t";
	}

	std::cout << "\n";
}


void clean(std::vector<int>& v)
{
	for (auto& e : v)
	{
		e = 0;
	}
}


void main()
{

	std::ifstream file;
	file.open("doublegraph.txt");
	int n = countingTops(file); //кол-во вершин в графе
	graph matrix(n, std::vector<int>(n));
	fillMatrix(matrix, file, n);  //Заполнение матрицы смежности
	std::vector<bool> used(n);
	std::vector<int> d(n);

	std::vector<std::vector<int>> allWays;

	while (!isAllUsed(used)) // Пока не посетили все вершины
	{
		for (int i = 0; i < used.size(); i++)
		{
			if (used[i] == false)
			{
				clean(d); //Заново заполняем нулями массив расстояний, тк заполнянем новую компоненту
				dfs(matrix, i, n, used, d);

				std::vector<int> temp; //Строим компоненты, исходя из полученный расстояний.

				for (int i = 0; i < d.size(); i++)
				{
					if (d[i] != 0)
					{
						temp.push_back(i);
					}
				}

				allWays.push_back(temp); // Все компоненты
			}
		}
	}

	for (const auto& v : allWays)
	{
		print(v);
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
