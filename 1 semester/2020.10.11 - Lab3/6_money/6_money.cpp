#include <iostream>
#include<vector>

void printNumber (std::vector<char> &arr)
{
    for (int counter = 0; counter < arr.size(); counter ++)
    {
        std::cout<<(static_cast<int>(arr[counter]));
    }

    return;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    long long a;
    int n;
    std::cin>>a>>n;
    std::vector<char> MAIN;

    if (a == 0 && n != 1)
    {
        std::cout<<-1;
        return 0;
    }
    if ((static_cast<long double>(a) / static_cast<long double>(n)) > 9)
    {
        std::cout<<-1;
        return 0;
    }


    char maxDigit = 9;
    while (a > 0)
    {
        if (a >= maxDigit)
        {
            MAIN.push_back(maxDigit);
            a -= maxDigit;
        }

        else
        {
            maxDigit--;
        }
    }

    for (int additional = MAIN.size(); additional < n; additional ++)
    {
        MAIN.push_back(0);
    }


    printNumber(MAIN);


    return 0;
}
