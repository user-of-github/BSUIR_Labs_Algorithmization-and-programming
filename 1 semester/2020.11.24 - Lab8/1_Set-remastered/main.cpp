#include "Set.h"

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);

    cout.setf(ios::boolalpha);
    Set example;
    cout<<example; // output: Set (0) : { }
    example.Add(1);
    example.Add(-1);
    example.Add(2);
    example.Add(0);
    example.Add(0);
    example.Add(0);
    cout<<example; // output: Set (4) : { -1; 0; 1; 2; }
    cout<<example.Has(0)<<"\n"; // output: true
    cout<<example.Has(3)<<"\n"; // output: false

    return 0;
}


