#include "SetFirst.h"
#include "SetFirst.cpp"

using std::cout;
using std::string;

int main()
{
    (void) cout.tie(NULL);
    (void) std::ios_base::sync_with_stdio(false);
    (void) std::iostream::sync_with_stdio(false);

    (void) cout.setf(std::ios::boolalpha);

    auto test_set_1 = SetFirst<string>();
    test_set_1.Add("BSUIR");
    test_set_1.Add("BSU");
    test_set_1.Add("BSEU");
    test_set_1.Add("BSUIR");

    cout << test_set_1; // Set(3): { BSEU  BSU  BSUIR }

    test_set_1.Delete("BSEU");
    cout << test_set_1; // Set(2): { BSU  BSUIR }

    cout << test_set_1.Has("BSU") << ' '
         << test_set_1.Has("BSEU") << ' ' << test_set_1.Size() << '\n'; // true false 2

    auto it = test_set_1.begin();
    cout << *(++it) << '\n'; // // BSUIR
    for (const auto &item : test_set_1)
        cout << item << ' '; // BSU BSUIR

    return 0;
}
