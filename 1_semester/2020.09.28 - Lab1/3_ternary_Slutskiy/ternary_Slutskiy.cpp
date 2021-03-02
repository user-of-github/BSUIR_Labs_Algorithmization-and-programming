#include <iostream>
#include<string>

using namespace std;

int main()
{
    long long  counter1 = 0,
               counter2 = 0,
               counter3 = 0,
               counter1_copy = 0,
               counter2_copy = 0,
               counter3_copy = 0,
               N;
    string input;

    cin>>input;
    cin>>N;

    /* просчитаем исходное количество символов '1', '2', '3' */
    for (long long i = 0; i < input.size(); i++)
    {
        if (input[i] == '1')
        {
            counter1++;
        }
        else if (input[i] == '2')
        {
            counter2++;
        }
        else
        {
            counter3++;
        }
    }


    /* «на€ преобразовани€, манипулируем созданными переменными. Ќам же нужно количество, а не конечна€ строка*/
    for (long long i = 0; i < N; i++)
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
