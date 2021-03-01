#include "Deque.h"

void Deque :: Shift ()
{
    this->Remove(0);
    return;
}

void Deque :: Unshift (const int &_new)
{
    this->Insert(0, _new);
    return;
}

ostream& operator << (ostream &cout, const Deque &a)
{
    cout<<"("<<a.length<<") ";
    cout<<"{";
    for (unsigned int counter = 0; counter < a.length; counter ++)
    {
        cout<<a.arr[counter]<<(counter == a.length - 1 ? "" : "; ");
    }
    cout<<"}\n";

    return cout;
}

