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
    cout << surnames_and_marks; // Tree(0): {}

    surnames_and_marks.Add(make_pair<string, int>("Slutski", 10));
    surnames_and_marks.Add(make_pair<string, int>("Khrapko", 9));
    surnames_and_marks.Add(make_pair<string, int>("Suhovej", 9));
    surnames_and_marks.Add(make_pair<string, int>("Markevich", 7));
    surnames_and_marks.Add(make_pair<string, int>("Levankou", 8));
    cout << surnames_and_marks; // Tree(5): { Khrapko:9  Levankou:8  Markevich:7  Slutski:10  Suhovej:9 }

    cout << surnames_and_marks.Has("Mehovich") << '\n'; // false
    cout << surnames_and_marks.Has("Slutski") << '\n'; // true

    surnames_and_marks["Khrapko"] = 7;
    cout << surnames_and_marks; // Tree(5): { Khrapko:7  Levankou:8  Markevich:7  Slutski:10  Suhovej:9 }


    return 0;
}
