#include <conio.h>
#include "List.h"
#include "List.cpp"
#include "ListIterator.h"

int main()
{
    auto test = List<int>({1, 2, 3, 4, 2021});
    cout << test; // (5): { 1 2 3 4 2021 }

    test.PushFront(-1);
    test.PushBack(10);
    cout << test; // (7): { -1 1 2 3 4 2021 10 }


    test.PopFront();
    test.PopBack();
    test.PopFront();
    test.PopBack();
    test.PopFront();
    test.PopBack();
    test.PopFront();
    cout << test; // (0): { }

    test.PushFront(123);
    test.PushFront(987);
    cout << test; // (2): { 987 123 }

    auto copy = List<int>(test);
    cout << copy; // (2): { 987 123 }

    copy.PushFront(8888);
    test = copy;
    cout << test; // (3): { 8888 987 123 }

    auto another_copy = List<int>(copy);
    cout << another_copy; // (3): { 8888 987 123 }

    another_copy.PopBack();
    another_copy.PopBack();
    another_copy.PopBack();
    another_copy.PushFront(1212);
    cout << another_copy; // (1): { 1212 }

    copy = std::move(another_copy);
    cout << copy; // (1): { 1212 }
    cout << another_copy; // (0): { } [was cleared because of std::move]

    another_copy.PushFront(101);
    cout << another_copy; // (1): { 101 } [but is still available for further actions]

    copy.PushBack(-1212);
    for (auto &item : copy)
        item = 0;
    cout << copy; // (2): { 0 0 }


    for (auto it = --copy.end(); it != --copy.begin(); --it)
        cout << *it << " "; // 0 0 [REVERSE]
    cout << "\n";


    List<int> tmp = List<int>();
    cout << tmp; // (0): { } [new empty list]

    copy = (tmp);
    cout << copy; // (0): { } [also empty, because was copied from tmp]

    copy.PushBack(2288); // (1): { 2288 }
    cout << copy;

    copy.PushBack(12);
    copy.PushBack(12);
    copy.PushBack(12);
    copy.PushBack(12);
    auto itCopy = copy.begin();
    ++itCopy; // 12
    cout<<*itCopy;

    cout << copy;
    _getch();

    
    return 0;
}