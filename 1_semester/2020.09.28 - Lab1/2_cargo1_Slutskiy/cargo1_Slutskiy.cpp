#include <iostream>
#include<vector>

using namespace std;

int main()
{
    int Q1, P1, Q2, P2, A;

    int max_x,
        max_y;

    vector<int> possibleResults;

    cin>>Q1>>P1>>Q2>>P2>>A;

    /* определяем верхние границы для перевозок в случае только для первого авто и только для второго
    Это нужно для возможности реализовать перебор всех возможных пар X и Y*/
    max_x = (A / Q1) + 1;
    max_y = (A / Q2) + 1;

    /* X - количество рейсов 1-ого, Y - 2-ого. Стоимости удовлетворительных комбинаций запоминаем в массив*/
    for (int x = 0; x <= max_x; x++)
    {
        for (int y = 0; y <= max_y; y++)
        {
            if ((x * Q1 + y*Q2) >= A)
            {
                possibleResults.push_back(((x * P1) + (y * P2)));
            }
        }
    }

    int MIN = possibleResults[0];

    /* находим минимум из всех запомнившихся вариантов*/
    for (int i = 0; i < possibleResults.size(); i++)
    {
        if (possibleResults[i] < MIN)
        {
            MIN = possibleResults[i];
        }

    }

    cout<<MIN;

    return 0;
}
