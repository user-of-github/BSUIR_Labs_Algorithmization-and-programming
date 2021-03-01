#include "Deque.h"

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);

    Deque example;
    cout<<example; // output: (0) {}

    example.Push(-5);
    example.Push(100);
    cout<<example; // output: (2) {-5; 100}

    example.Unshift(0);
    cout<<example; // output: (3) {0; -5; 100}

    example.Insert(1, 20);
    example.Insert(1, 20);
    cout<<example; // output: (5) {0; 20; 20; -5; 100}

    example.Remove(3);
    cout<<example; // output: (4) {0; 20; 20; 100}

    example.Shift();
    cout<<example; // output: (3) {20; 20; 100}

    example.Pop();
    cout<<example; // output: (2) {20; 20}


    Deque object = example;
    object.Push(2020);
    cout<<object; // output: (3) {20; 20; 2020}

    cout<<object.FindFirst(20)<<" "<<object.FindFirst(-22)<<"\n"; // output: 0 -1

    object.RemoveAll();
    cout<<object; // output: (0) {}

    object.Push(123);
    object.Insert(0, 321);
    cout<<object; // output: (2) {321; 123}


    return 0;
}
