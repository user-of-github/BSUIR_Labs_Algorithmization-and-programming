/* Дано длинное неотрицательное целое число X. Проверить
делится ли X без остатка на 2,3,4,5,6,8,9,10,11,64.
Длина числа X не превышает 10000 цифр. */

#include<fstream>
#include<string>

using namespace std;

const string evenNumbers = "02468";

/* Это функция вспомогательная. Для функции проверки деления на чётное число.
Когда делим на 4, смотрим последние 2 цифры. Когда на 8 — последние 3. И т.д.*/
int lengthForDivideEven (int divider)
{
    if (divider == 2)
        return 1;
    else if (divider == 4)
        return 2;
    else if (divider == 8)
        return 3;
    else if (divider == 64)
        return 6;
}


bool isDivisibleByEven (string data, int divider)
{
    int necessaryLength = lengthForDivideEven(divider),
        value = 0;

    if (necessaryLength > data.size())
    {
        for (int counter = 0; counter < data.size(); counter ++)
            value = (value * 10) + ((int)(data[counter] - '0'));
    }
    else
    {
        for (int counter = data.size() - necessaryLength; counter < data.size(); counter++)
            value = (value * 10) + ((int)(data[counter] - '0'));
    }

    return (value % divider == 0);
}

// сразу пропишем и для 3, и для 9 в одной функции
bool isDivisibleBy3or9 (string data, int divider)
{
    int sumOfNumbers = 0;
    for (int counter = 0; counter < data.size(); counter++)
        sumOfNumbers += (int)(data[counter] - '0');

    return (sumOfNumbers % divider == 0);
}

bool isDivisibleBy5 (string data)
{
    return (data[data.size() - 1] == '0' || data[data.size() - 1] == '5');
}

bool isDivisibleBy6 (string data)
{
    return (isDivisibleByEven(data, 2) && isDivisibleBy3or9(data, 3));
}

bool isDivisibleBy10 (string data)
{
    return (isDivisibleByEven(data, 2) && isDivisibleBy5(data));
}

bool isDivisibleBy11 (string data)
{
    int alternatingAmountSign = 0;
    bool sign = true;
    for (int counter = 0; counter < data.size(); counter ++)
    {
        alternatingAmountSign += ((sign == true) ? ((int)(data[counter] - '0')) : ((-1)*(int)(data[counter] - '0')));
        sign = !sign;
    }
    return (alternatingAmountSign % 11 == 0);
}
int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    string input;
    cin>>input;

    /*  2,3,4,5,6,8,9,10,11,64 */
    cout<<isDivisibleByEven(input, 2)<<" ";
    cout<<isDivisibleBy3or9(input, 3)<<" ";
    cout<<isDivisibleByEven(input, 4)<<" ";
    cout<<isDivisibleBy5(input)<<" ";
    cout<<isDivisibleBy6(input)<<" ";
    cout<<isDivisibleByEven(input, 8)<<" ";
    cout<<isDivisibleBy3or9(input, 9)<<" ";
    cout<<isDivisibleBy10(input)<<" ";
    cout<<isDivisibleBy11(input)<<" ";
    cout<<isDivisibleByEven(input, 64);

    return 0;
}
