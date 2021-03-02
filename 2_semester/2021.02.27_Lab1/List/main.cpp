#include "List.h"
#include "List.cpp"
#include "ListIterator.h"

int main()
{
    List<int> test({1, 2, 3});
    test.Print();

    List<int> test2({42, 42, 42, 42});
    test2.Print();

    test2 = (test);
    test2.Print();

    for (auto &item : test2)
        item = 6;

    test2.Print();
    return 0;
}