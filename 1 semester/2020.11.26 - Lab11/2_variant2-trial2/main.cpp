/* В первой строке записано количество чисел (не более 10^4). Далее в каждой строке
записано одно или несколько натуральных чисел, больших единицы и не
 превосходящих 10^4 , разделенных пробелами.
Для каждого числа определить, является ли это число простым. */

#include <iostream>
#include <algorithm>

using std::cin,
      std::cout,
      std::ios_base,
      std::sort;

bool comparator (const unsigned int &a, const unsigned int &b)
{
    return a > b;
}

bool isSimple (const unsigned int &number)
{
    if (number == 1)
        return false;
    for (unsigned long long divider = 2; divider * divider <= number; divider++)
    {
        if (number % divider == 0)
            return false;
    }

    return true;
}
int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    unsigned int length = 0;
    cin>>length;

    unsigned int *arr = new unsigned int [length];
    for (unsigned int counter = 0; counter < length; counter ++)
        cin>>arr[counter];

    sort (arr, arr + length, comparator);


    for (unsigned int counter = 0; counter < length; counter ++)
    {
        if (counter > 0 && arr[counter] != arr[counter - 1])
            cout<<"\n"<<arr[counter]<<":"<<(isSimple(arr[counter]) ? "prime" : "composite");
        else if (counter == 0)
            cout<<arr[counter]<<":"<<(isSimple(arr[counter]) ? "prime" : "composite");
    }

    return 0;
}
