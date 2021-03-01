#include <iostream>
#include "List.h"
#include "List.cpp"

using std::cout;

int main()
{
    List<int> test({1, 2, 3});

    for (auto item : test)
        cout << item << ' ';

    return 0;
}