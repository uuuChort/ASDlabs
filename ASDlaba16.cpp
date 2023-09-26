#include <vector> 
#include <iostream>

int backpack(std::vector<std::pair<int, int>>& stuff, int W) // Решение задачи, деля ее на маленькие подзадачи, формально, создается дискретная таблица знаечний
{                                                           // (двумерный массив dp) где снизу справа самый лучший исход
    int  n = stuff.size();
    std::vector<std::vector<int>> dp(W + 1, std::vector<int>(n + 1, 0));

    for (int j = 1; j <= n; j++)
    {
        for (int w = 1; w <= W; w++)
        {
            int weigth = stuff[j - 1].second;
            if (weigth <= w)
            {
                int price = stuff[j - 1].first;
                dp[w][j] = std::max(dp[w][j - 1], dp[w - weigth][j - 1] + price); // выбор более выгодного случая 
            }                                                                     //либо ложим элемент и уменьшается его вес или оставляем прежний вес но не увеличивается стоимость
            else
            {
                dp[w][j] = dp[w][j - 1];
            }
        }
    }
    return dp[W][n];
}



void main()
{
    std::vector<std::pair<int, int>> stuff = { {1,3},{6,4}, {4,5}, {7,8}, {6,9} }; // Здесь пары предметов (стоимость, вес)
    int w = 13; // Грузоподъемность рюкзака
    std::cout << backpack(stuff, w) << std::endl;
}