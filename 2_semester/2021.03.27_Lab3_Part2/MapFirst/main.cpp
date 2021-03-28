#include "MapFirst.h"
#include "MapFirst.cpp"

using std::make_pair;
using std::string;
using std::cout;


int main()
{
    // MAP для итератора над вершиной дерева
    auto test_map_1 = MapFirst<string, unsigned short>();
    test_map_1.Add(make_pair("Slutski", 23));
    test_map_1.Add(make_pair("Sukhovey", 24));
    test_map_1.Add(make_pair("Katanaev", 13));
    test_map_1.Add(make_pair("Bondarkov", 2));
    cout << test_map_1; // Map(4): { Bondarkov:2  Katanaev:13  Slutski:23  Sukhovey:24 }

    for (auto it = test_map_1.begin(); it != test_map_1.end(); ++it)
        cout << *it << ' '; // 2 13 23 24
    cout << '\n';

    for (auto &item : test_map_1)
        item = 228;
    cout << test_map_1; // Map(4): { Bondarkov:228  Katanaev:228  Slutski:228  Sukhovey:228 }
    cout << test_map_1["Katanaev"] << '\n'; // 228

    return 0;
}
