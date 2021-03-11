#include "Deque.h"
#include "Deque.cpp"

int main()
{
    auto test = Deque<int>();

    for (auto counter = 0; counter < 13; ++counter)
        test.PushBack(counter);

    test.PushFront(-228);

    test.Print();


    return 0;
}
