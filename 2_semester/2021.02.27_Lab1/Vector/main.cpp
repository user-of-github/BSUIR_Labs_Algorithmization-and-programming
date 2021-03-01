#include <iostream>
#include "Vector.h"
#include "Vector.cpp"
#include "VectorIterator.h"

using std::cout;
using std::cin;

int main()
{
    Vector<int> test({1, 2, 3, 4});
    Vector<int> test2 = Vector<int>(5, 6);

    //test2.Print();

    //test2 = std::move(test);

    //test2.Print();

    auto test3 = Vector<int>();
    for (unsigned counter = 10; counter >= 6; --counter)
        test3.PushBack(counter);

    //test3.Print();
    test2 = test3;
    //test2.Print();
    test2 = std::move(test);
    //test2.Print();

    for (auto item : test2)
        cout<<item;

    return 0;
}


