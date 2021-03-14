#include "Deque.h"
#include "Deque.cpp"
#include "DequeIterator.h"

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


    for (auto &item : test)
        item = 2000;
    cout << test;

    test.Clear();
    auto count = 10;
    while (count < 32)
    {
        test.PushBack(count++);
        test.PushFront(count++);
    }
    cout << test;

    /*for (auto &item : test)
        item = 2000;
    cout << test;*/

    // cout << *test.begin() << "\n";

    for (auto counter = 0; counter < 5; ++counter)
        test.PopFront();
    cout << test;

    Deque<int> test2 = {17, 51, 14, 03, 2021};
    cout << test2; // (5) { 17 51 14  | 3 2021  }

    auto current_begin_test2 = test2.begin();
    cout << *current_begin_test2 << std::endl; // 17

    test2.PushFront(45);
    cout << test2; // (6) { 45  | 17 51 14  | 3 2021  }
    cout << *current_begin_test2 << std::endl; // 45 // begin was UPDATED

    return 0;
}
