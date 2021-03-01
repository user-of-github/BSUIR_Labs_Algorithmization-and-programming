/* Как известно, число 396 имеет в качестве своих делителей числа
 4, 9, 11 (о других делителях не будем вести разговора).

Задано очень большое целое положительное число M.
Вам требуется определить категорию этого числа, исходя из следующей таблицы: .. */

#include <iostream>
#include<string>

using namespace std;

bool is4 (string data)
{
    int necessaryLength = 2,
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

    return (value % 4 == 0);
}

bool is9 (string data)
{
    int sumOfNumbers = 0;
    for (int counter = 0; counter < data.size(); counter++)
        sumOfNumbers += (int)(data[counter] - '0');

    return (sumOfNumbers % 9 == 0);
}

bool is11 (string data)
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
    string input;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>input;

    if (!(is4(input)) && !(is9(input)) && !(is11(input)))
        cout<<1;
    else if ((is4(input)) && !(is9(input)) && !(is11(input)))
        cout<<2;
    else if (!(is4(input)) && (is9(input)) && !(is11(input)))
        cout<<3;
    else if (!(is4(input)) && !(is9(input)) && (is11(input)))
        cout<<4;
    else if ((is4(input)) && (is9(input)) && !(is11(input)))
        cout<<5;
    else if ((is4(input)) && !(is9(input)) && (is11(input)))
        cout<<6;
    else if (!(is4(input)) && (is9(input)) && (is11(input)))
        cout<<7;
    else
        cout<<8;

    return 0;
}
