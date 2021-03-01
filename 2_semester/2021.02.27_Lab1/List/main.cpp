#include <iostream>
#include <iterator>
#include "List.h"

using std::cout;

int main()
{
    List<int> test({1, 2, 3});

    for (auto item : test)
        cout << item << ' ';

    return 0;
}



