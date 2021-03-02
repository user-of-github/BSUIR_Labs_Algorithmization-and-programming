/*
Назовём непустую строку тернарной, если
в её состав входят только символы '1', '2' и '3'.
Над заданной строкой выполним следующее преобразование:

    каждый исходный символ '1' заменим строкой '23';
    каждый исходный символ '2' заменим символом '1';
    каждый исходный символ '3' заменим символом '2'.

Сколько различных символов будет в строке после выполнения N таких
преобразований?
Input
Первая строка содержит исходную тернарную строку. Её длина не превосходит
10 символов. Во второй строке записана величина N (1<N<=1001).
Output
Выведите три числа: количество единиц, двоек и троек в полученной
тернарной строке
*/



#include <iostream>
#include<string>
using namespace std;

string input;
long long  counter1 = 0,
           counter2 = 0,
           counter3 = 0,
           counter1_copy = 0,
           counter2_copy = 0,
           counter3_copy = 0,
           N;
int main()
{
    cin>>input;
    cin>>N;
    for (long long i = 0; i<input.size(); i++)
    {
        if (input[i] == '1')
            counter1++;
        else if (input[i] == '2')
            counter2++;
        else
            counter3++;
    }
    for (long long i = 0; i<N; i++)
    {
        counter1_copy = counter1;
        counter2_copy = counter2;
        counter3_copy = counter3;

        counter2 = counter1_copy + counter3_copy;
        counter1 = counter2_copy;
        counter3 = counter1_copy;
    }

    cout<<counter1<<" "<<counter2<<" "<<counter3;
    return 0;
}
