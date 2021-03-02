#include <iostream>
using std::cin,
      std::cout,
      std::ostream;

#include "Set.h"

int main()
{
    Set example;
    cout<<example; // output: Set (0): { }

    example.Add(2020);
    example.Add(2020);
    example.Add(1);
    example.Add(12);
    example.Add(0);
    cout<<example; // output: Set (4): { {0} {1} {12} {2020} }

    example.Add(2021);
    example.Add(2025);
    example.Add(2026);
    example.Add(2023);
    cout<<example; // output: Set (8): { {0} {1} {12} {2020} {2021} {2023} {2025} {2026} }

    example.Delete(2021);
    cout<<example; // output: Set (7): { {0} {1} {12} {2020} {2023} {2025} {2026} }

    example.Delete(2020); // ROOT
    cout<<example; // output: Set (6): { {0} {1} {12} {2023} {2025} {2026} }

    cout<<example.Has(2020)<<" "<<example.Has(2027)<<"\n"; // output: false false
    cout<<example.Has(2025)<<"\n"; // output: true
    example.Clear();
    cout<<example;

    return 0;
}


