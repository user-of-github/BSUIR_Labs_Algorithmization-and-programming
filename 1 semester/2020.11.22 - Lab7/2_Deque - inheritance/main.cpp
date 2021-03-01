#include "Deque.h"

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);

    // DEMONSTRATION OF WORK

    // example1
    Deque example = Deque();
    for (int i = 0; i < 5; i++)
        example.Push(i);
    cout<<example; // output: (5) {0; 1; 2; 3; 4}

    example.Shift();
    cout<<example; // output: (4) {1; 2; 3; 4}

    // example2
    Deque example2 = Deque(example);
    example2.Unshift(5);
    cout<<example2; // output: (5) {5; 1; 2; 3; 4}

    return 0;
}
