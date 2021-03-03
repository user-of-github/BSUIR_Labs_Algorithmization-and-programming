#include <iostream>
#include "Vector.h"
#include "Vector.cpp"
#include "VectorIterator.h"

using std::cout;

int main()
{
    Vector<int> numbers = {1, 2, 3, 4};
    Vector<int> numbers_copy = Vector<int>(numbers);

    numbers.Print(); // (4):{ 1 2 3 4 }
    numbers_copy.Print(); // (4):{ 1 2 3 4 }

    numbers[3] = 2021;

    numbers_copy = std::move(numbers);
    numbers_copy.Print(); // (4):{ 1 2 3 2021 }
    numbers.Print(); // (0):{ }

    Vector<int> one_more_copy = std::move(numbers_copy);
    one_more_copy.Print(); // (4):{ 1 2 3 2021 }

    one_more_copy.PushBack(20);
    one_more_copy.Print(); // (5):{ 1 2 3 2021 20 }

    for (unsigned int counter = 0; counter < 7; ++counter)
        one_more_copy.PopBack();
    one_more_copy.Print(); // (0):{ }

    for (int counter = -556; counter < -545; ++counter)
    {
        one_more_copy.PushBack(counter);
    }

    for (const auto &item : one_more_copy)
    {
        cout << item << " "; // -556 -555 -554 -553 -552 -551 -550 -549 -548 -547 -546
    }
    cout << "\n";

    for (auto &item : one_more_copy)
    {
        item = 2021;
    }
    one_more_copy.Print(); // (11):{ 2021 2021 2021 2021 2021 2021 2021 2021 2021 2021 2021 }


    // REVERSE
    for (auto it = --one_more_copy.end(); it != one_more_copy.begin(); --it)
    {
        cout << *it << " "; // 2021 2021 2021 2021 2021 2021 2021 2021 2021 2021
    }


    return 0;
}


