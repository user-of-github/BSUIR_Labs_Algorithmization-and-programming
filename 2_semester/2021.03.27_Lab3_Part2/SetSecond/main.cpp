#include "SetSecond.h"
#include "SetSecond.cpp"

using std::cout;
using std::string;

int main()
{
    (void) cout.tie(NULL);
    (void) std::ios_base::sync_with_stdio(false);
    (void) std::iostream::sync_with_stdio(false);

    (void) cout.setf(std::ios::boolalpha);

    auto test_set_1 = SetSecond<string>();
    test_set_1.Add("BSUIR");
    test_set_1.Add("BSU");
    test_set_1.Add("BSEU");
    test_set_1.Add("BSUIR");

    cout << test_set_1; // Set(3): { BSEU  BSU  BSUIR }

    test_set_1.Delete("BSU");
    cout << test_set_1; // Set(2): { BSEU  BSUIR }

    cout << test_set_1.Has("BSU") << ' '
         << test_set_1.Has("BSEU") << ' ' << test_set_1.Size() << '\n'; // true false 2

    cout << test_set_1; // Set(2): { BSEU  BSUIR }

    auto it = test_set_1.begin();

    for (const auto &item : test_set_1)
        cout << item << ' '; // BSEU BSUIR
    cout << '\n';

    test_set_1.Add("BNTU");
    test_set_1.Delete("BSEU");

    for (const auto &item : test_set_1)
        cout << item << ' '; // BNTU BSUIR

    cout << '\n';
    return 0;
}
