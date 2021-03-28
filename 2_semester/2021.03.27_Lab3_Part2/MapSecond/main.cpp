#include "MapSecond.h"
#include "MapSecond.cpp"

using std::string;
using std::cout;
using std::make_pair;

int main()
{

    auto test_map_2 = MapSecond<string, string>();

    test_map_2.Add(make_pair("Samsung", "Exynos"));
    test_map_2.Add(make_pair("Huawei", "Kirin"));
    test_map_2.Add(make_pair("Google", "Qualcomm"));
    test_map_2.Add(make_pair("ZZZ-pseudo-last", "kek"));

    cout << test_map_2; // Map(4): { Google:Qualcomm  Huawei:Kirin  Samsung:Exynos  ZZZ-pseudo-last:kek }


    for (const auto &item : test_map_2)
        cout << item << ' ';
    cout << '\n'; // Qualcomm Kirin Exynos

    test_map_2.Add(make_pair("Honor", "Mediatek"));
    cout << test_map_2; // Map(5): { Google:Qualcomm  Honor:Mediatek
    // Huawei:Kirin  Samsung:Exynos  ZZZ-pseudo-last:kek }

    test_map_2.Delete("Google");
    cout << test_map_2; // Map(4): { Honor:Mediatek  Huawei:Kirin  Samsung:Exynos  ZZZ-pseudo-last:kek }

    for (const auto &item : test_map_2)
        cout << item << ' ';
    cout << '\n'; // Mediatek Kirin Exynos

    return 0;
}
