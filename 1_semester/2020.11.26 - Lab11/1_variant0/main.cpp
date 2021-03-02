/* В каждой строке текстового файла записано одно натуральное число,
не превосходящее 10^9. Количество таких строк не превышает 100.
Для каждого числа определить цифру, которая чаще всего встречается в его
записи.
Если таких цифр несколько, то найти наибольшую. */

#include <algorithm>
#include <iostream>
using std::sort,
      std::cin,
      std::cout;

struct type
{
    unsigned long long number;
    unsigned short mostFrequent = 0;
};

bool comparator (const type &a, const type &b);
void getMostFrequent (type &object);

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    cin.tie(NULL);
    cout.tie(NULL);

    type data[100];
    unsigned short length = 0;
    unsigned long long temp;
    while (cin >> temp)
    {
        length ++;
        data[length - 1].number = temp;
    }

    if (length == 1 && data[0].number == 0)
        return 0;

    for (unsigned short counter = 0; counter < length; counter ++)
        getMostFrequent(data[counter]);

    sort(data, data + length, comparator);

    for (unsigned short counter = 0; counter < length; counter ++)
    {
        if (counter > 0 && data[counter].number != data[counter - 1].number)
            cout<<data[counter].number<<":"<<data[counter].mostFrequent<<(counter != length - 1 ? "\n" : "");
        else if (counter == 0)
            cout<<data[counter].number<<":"<<data[counter].mostFrequent<<(counter != length - 1 ? "\n" : "");
    }

    return 0;
}

bool comparator (const type &a, const type &b)
{
    return a.number < b.number;
}

void getMostFrequent (type &object)
{
    unsigned short numbers[10] {0};

    unsigned long long copyNumber = object.number;

    while (copyNumber > 0)
    {
        numbers[copyNumber % 10] ++;
        copyNumber /= 10;
    }

    unsigned short mostFrequentIndex = 1;
    for (unsigned short counter = 0; counter < 10; counter ++)
    {
        if (numbers[counter] >= numbers[mostFrequentIndex])
            mostFrequentIndex = counter;
    }
    object.mostFrequent = mostFrequentIndex;
    return;
}
