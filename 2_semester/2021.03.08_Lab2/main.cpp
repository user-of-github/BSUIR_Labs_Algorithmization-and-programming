#include "Deque.h"
#include "Deque.cpp"

int main()
{
    auto test = Deque<int>();
    cout << test; // (0) {  }

    for (auto counter = 0; counter < 5; ++counter)
        test.PushFront(counter);
    cout << test; // (5) { 4 3 2 1 0  }

    for (auto counter = 0; counter < 13; ++counter)
        test.PushBack(counter);
    cout << test; // (18) { 4 3 2 1 0 0 1 2 3 4 5 6 7 8 9 10 11 12  }

    while(test.Size() != 0)
        test.PopFront();
    cout << test; // (0) {  }

    for (auto counter = 0; counter < 13; ++counter)
        test.PushBack(counter);
    cout << test; // (13) { 0 1 2 3 4 5 6 7 8 9 10 11 12  }


    return 0;
}
