#include "HashTable.h"
#include "HashTable.cpp"

using std::cout;
using std::string;

int main()
{
    cout.tie(NULL);
    std::ios_base::sync_with_stdio(false);
    std::iostream::sync_with_stdio(false);
    cout.setf(std::ios::boolalpha);

    auto test = HashTable<string, unsigned long long>();
    cout << test; // HashTable(0):

    test.Insert("Acer", 7);
    test.Insert("Asus", 8);
    test.Insert("LG", 10);
    cout << test; // HashTable(3): [47]: Asus:8   | [137]: LG:10   | [251]: Acer:7   |

    cout << test["One+"] << '\n'; // 0
    cout << test; // HashTable(4): [47]: Asus:8   | [137]: LG:10   | [161]: One+:0   | [251]: Acer:7   |

    test.Clear();
    cout << test; // HashTable(0):

    test.Insert("Huawei", 22e1);
    test.Insert("Samsung", 11e3);
    test.Insert("Google", 70e2);
    test.Insert("LG", 15e2);
    cout << test; // HashTable(4): [137]: LG:1500  Google:7000   | [219]: Huawei:220   | [284]: Samsung:11000   |

    cout << test.Contains("Acer") << ' ' << test.Contains("LG") << "\n\n"; // false true


    auto test2 = HashTable<string, char>(3);
    cout << test2; // HashTable(0):

    test2.Insert("firststring", 'V');
    cout << test2; // HashTable(1): [1]: firststring:V   |

    test2.Insert("secondstring", 'F');
    cout << test2; // HashTable(2): [1]: secondstring:F  firststring:V   |

    test2.Insert("thirdstring", 'N');
    cout << test2; // HashTable(3): [1]: thirdstring:N  secondstring:F  firststring:V   | // Rehashed from 3 to 6



    test2.Insert("fourthstring", 'S');
    cout << test2;
    // HashTable(4): [1]: thirdstring:N  secondstring:F   | [2]: fourthstring:S   | [4]: firststring:V   |

    test2.Erase("secondstring");
    cout << test2; // HashTable(3): [1]: thirdstring:N   | [2]: fourthstring:S   | [4]: firststring:V   |


    auto test2_copy = HashTable<string, char>(test2);
    cout << test2_copy; // HashTable(3): [1]: thirdstring:N   | [2]: fourthstring:S   | [4]: firststring:V   |

    auto test2_move = std::move(test2_copy);
    test2_move.Insert("anystring", 'F');
    cout << test2_move; // [1]: anystring:F  thirdstring:N   | [2]: fourthstring:S   | [4]: firststring:V   |   |

    auto test3_move = HashTable<string, unsigned long long>();
    test3_move = std::move(test);
    cout << test3_move; // HashTable(4): [137]: Google:7000  LG:1500   | [219]: Huawei:220   | [284]: Samsung:11000   |

    return 0;
}