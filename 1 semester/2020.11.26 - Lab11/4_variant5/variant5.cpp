/* В первой строке текстового файла записано количество чисел
(не более 10000). Далее в каждой строке записано одно или
несколько натуральных чисел, разделенных пробелами. Для каждого числа
определить, является ли его десятичная запись палиндромом. Все числа не
превосходят 10^9 */

#include <iostream>
#include <algorithm>

using std::cin,
      std::cout,
      std::ios_base,
      std::sort,
      std::string;

bool comparator (const unsigned int &a, const unsigned int &b)
{
    return a < b;
}

bool isPalindrom (unsigned long long num)
{
    string check = "";
    while (num > 0)
    {
        check += (static_cast<char>(num%10));
        num /= 10;
    }
    for (unsigned short counter = 0; counter < check.size() / 2; counter ++)
    {
        if (check[counter] != check[check.size() - counter - 1])
        {
            return false;
        }
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

    unsigned short length = 0;
    cin>>length;

    unsigned long long *arr = new unsigned long long [length];
    for (unsigned short counter = 0; counter < length; counter ++)
    {
        cin>>arr[counter];
    }

    sort (arr, arr + length, comparator);

    for (unsigned int counter = 0; counter < length; counter ++)
    {

        if (counter > 0 && arr[counter] != arr[counter - 1])
        {
            cout<<"\n"<<arr[counter]<<":"<<(isPalindrom(arr[counter]) ? "palindrome" : "non-palindrome");
        }
        else if (counter == 0)
        {
            cout<<arr[counter]<<":"<<(isPalindrom(arr[counter]) ? "palindrome" : "non-palindrome");
        }
    }

    return 0;
}
