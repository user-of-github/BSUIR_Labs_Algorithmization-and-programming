#include "Set.h"

int main()
{
    cout.setf(ios::boolalpha);
    cin.tie(NULL);
    cin.tie(NULL);

    Set example;

    example.Add(1);
    example.Add(1);
    example.Add(1.2);
    example.Add(-3.6);
    example.Add(-3.6);
    cout<<example; // output: (3) {1; 1.2; -3.6}

    cout<<example.Contains(0)<<" "<<example.Contains(1.20)<<"\n"; // output: false true

    for (int counter = 0; counter < 3; counter ++)
        example.Add(counter);

    cout<<example; // output: (5) {1; 1.2; -3.6; 0; 2}

    example.Clear();
    cout<<example; // output: (0) {}

    for (int counter = 0; counter < 3; counter ++)
        example.Add(counter);

    cout<<example; // output: (3) {0; 1; 2}


    return 0;
}
