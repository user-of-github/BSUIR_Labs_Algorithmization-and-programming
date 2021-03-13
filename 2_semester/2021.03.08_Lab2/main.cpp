#include "Deque.h"
#include "Deque.cpp"

int main()
{
    auto test = Deque<int>();
    cout << test; // (0) {  }

    for (auto counter = 0; counter < 5; ++counter)
        test.PushFront(counter);
    cout << test; // (5) { 4  | 3 2 1  | 0  }

    for (auto counter = 0; counter < 13; ++counter)
        test.PushBack(counter);
    cout << test; // (18) { 4  | 3 2 1  | 0 0 1  | 2 3 4  | 5 6 7  | 8 9 10  | 11 12  }

    while (test.Size() != 0)
        test.PopFront();
    cout << test; // (0) {  }

    for (auto counter = 22; counter < 27; ++counter)
        test.PushBack(counter);
    cout << test; // (5) { 22 23 24  | 25 26  }

    for (auto counter = -9; counter > -17; --counter)
        test.PushFront(counter);
    cout << test; // (13) { -16 -15  | -14 -13 -12  | -11 -10 -9  | 22 23 24  | 25 26  }

    for (auto counter = 1; counter < 3; ++counter)
        test.PopBack();
    cout << test; // (11) { -16 -15  | -14 -13 -12  | -11 -10 -9  | 22 23 24  |  }

    for (auto counter = 4; counter < test.Size() - 3; ++counter)
        test[counter] = 2021;
    cout << test; // (11) { -16 -15  | -14 -13 2021  | 2021 2021 2021  | 22 23 24  |  }

    return 0;
}
