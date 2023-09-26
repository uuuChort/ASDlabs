#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
struct Good
{
	int weight;
	explicit Good(int weight) :weight(weight) {}
};


class Box
{
private:
	int size;
	vector<Good> knapsack;

public:
	explicit Box(int weight) : size(weight)
	{
		knapsack = vector<Good>();
	}

	void addGood(const Good& good)
	{
		knapsack.emplace_back(good.weight);
	}

	vector<Good> getGoods()
	{
		vector<Good> goods;
		for (const auto& k : knapsack)
		{
			goods.emplace_back(k.weight);
		}
		return goods;
	}

	void getMaxValue()
	{
		//кол-во комбинаций = 2^n, где n - количество предметов
		string totalNamesCombination;
		vector<Good> goods = getGoods();
		vector<int> indexes;
		int containerQuantity = 0;

		while (!goods.empty())
		{
			containerQuantity++; //если вещи еще остались, тогда ++ кол-во контейнеров
			int goodsSize = (int)goods.size();
			auto combinations = pow(2, goodsSize); //количество итераций
			int bestWeight = 0;

			for (int i = 0; i < combinations; i++)
			{
				int iNumber = i;
				vector<int> binaryForce(goodsSize, 0);

				for (int j = 0; j < goodsSize; j++) //полный перебор
				{
					binaryForce[j] = iNumber & 1; //побитово записываем число i
					iNumber >>= 1; //побитово сдвигаем i
				}
				int currentWeight = 0;
				vector<int> currentIndexes;

				for (int k = 0; k < goodsSize; k++)
				{
					if (binaryForce[k])
					{
						currentWeight += goods[k].weight;
						currentIndexes.push_back(k);
					}
				}
				if (currentWeight <= size && currentWeight > bestWeight)
				{
					bestWeight = currentWeight;
					indexes = currentIndexes;
				}
				if (bestWeight == size)
				{
					break;
				}
			}
			sort(indexes.begin(), indexes.end());

			for (int k = (int)indexes.size() - 1; k >= 0; k--)
			{
				goods.erase(goods.begin() + indexes[k]); //удаляем с конца элементы с максимальным весом
			}
		}
		cout << "Количество контейнеров: " << containerQuantity << "\n";
	}
};

int main()
{
	setlocale(LC_ALL, "Rus");
	Box box(15);
	box.addGood(Good(1));
	box.addGood(Good(2));
	box.addGood(Good(5));
	box.addGood(Good(4));
	box.addGood(Good(10));
	box.getMaxValue();
}