#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"
#include <iostream>

using std::cout;
using std::make_pair;
using std::string;

int main()
{
    (void) cout.tie(NULL);
    (void) std::ios_base::sync_with_stdio(false);
    (void) std::iostream::sync_with_stdio(false);

    (void) cout.setf(std::ios::boolalpha);

    auto surnames_and_marks = Map<string, unsigned short>();
    cout << surnames_and_marks; // Map(0): {}

    surnames_and_marks.Add(make_pair<string, int>("Slutski", 10));
    surnames_and_marks.Add(make_pair<string, int>("Khrapko", 9));
    surnames_and_marks.Add(make_pair<string, int>("Suhovej", 9));
    surnames_and_marks.Add(make_pair<string, int>("Markevich", 7));
    surnames_and_marks.Add(make_pair<string, int>("Levankou", 8));
    cout << surnames_and_marks; // Map(5): { Khrapko:9  Levankou:8  Markevich:7  Slutski:10  Suhovej:9 }

    cout << surnames_and_marks.Has("Mehovich") << '\n'; // false
    cout << surnames_and_marks.Has("Slutski") << '\n'; // true

    surnames_and_marks["Khrapko"] = 7;
    cout << surnames_and_marks; // { Khrapko:7  Levankou:8  Markevich:7  Slutski:10  Suhovej:9 }

    surnames_and_marks.Delete("Slutski");
    cout << surnames_and_marks; // Map(4): { Khrapko:7  Levankou:8  Markevich:7  Suhovej:9 }

    surnames_and_marks.Delete("Khrapko");
    cout << surnames_and_marks; // Map(3): { Levankou:8  Markevich:7  Suhovej:9 }

    surnames_and_marks.Delete("Markevich");
    surnames_and_marks.Delete("Levankou");
    surnames_and_marks.Delete("Suhovej");
    cout << surnames_and_marks; // Map(0): {}

    surnames_and_marks.Add(make_pair("Slutski", 9));
    cout << surnames_and_marks; // Map(1): { Slutski:9 }

    surnames_and_marks.Add(make_pair("Slutski", 10));
    cout << surnames_and_marks; // Map(1): { Slutski:10 }

    surnames_and_marks.Add(make_pair("TestSurname", 2));
    surnames_and_marks.Add(make_pair("Matuhin", 10));
    surnames_and_marks.Add(make_pair("Vaaomi", 9));
    cout << surnames_and_marks; // Map(4): { Matuhin:10  Slutski:10  TestSurname:2  Vaaomi:9 }

    cout << surnames_and_marks.FindNext("TestSurname") << '\n'; // 9
    cout << surnames_and_marks.FindPrevious("Slutski") << '\n'; // 10

    surnames_and_marks.Clear();
    cout << surnames_and_marks; // Map(0): {}

    surnames_and_marks.Add(make_pair("surname", 0));
    cout << surnames_and_marks; // Map(1): { surname:0 }

    surnames_and_marks.Add(make_pair("surname2", 2));
    cout << surnames_and_marks; // Map(2): { surname:0  surname2:2 }

    auto copy_surnames_and_marks = Map<string, unsigned short>(surnames_and_marks);
    cout << copy_surnames_and_marks; // Map(2): { surname:0  surname2:2 }
    cout << surnames_and_marks; // Map(2): { surname:0  surname2:2 }

    auto move_copy = std::move(copy_surnames_and_marks);
    move_copy.Add(make_pair("kek", 228));
    move_copy.Delete("surname");
    cout << move_copy; // Map(2): { kek:228  surname2:2 }
    cout << copy_surnames_and_marks; // Map(0): {}

    cout << surnames_and_marks; // Map(2): { surname:0  surname2:2 }


    move_copy = std::move(surnames_and_marks);
    cout << move_copy; // Map(2): { surname:0  surname2:2 }


    return 0;
}
