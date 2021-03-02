#include <iostream>
#include "List.h"
#include "List.cpp"

using std::cout;

int main()
{
    List<int> test({1, 2, 3});

    for (auto item : test)
        cout << item << ' ';

    List<int> test2({42, 42, 42, 42});

    for (auto item : test2)
        cout << item << ' ';

    test2 = (test);
    for (auto item : test2)
        cout << item << ' ';

    
    return 0;
}