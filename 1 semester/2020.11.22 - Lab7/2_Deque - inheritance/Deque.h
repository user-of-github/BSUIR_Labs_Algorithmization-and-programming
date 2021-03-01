#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

#include "Vector.h"

class Deque : public Vector
{
public:
    Deque () : Vector () {}
    Deque (const unsigned int &_size) : Vector (_size) {}
    Deque (const unsigned int &_size, const int &_value) : Vector (_size, _value) {}
    Deque (const Deque &_a) : Vector (_a) {}

    void Shift ();
    void Unshift (const int &_new);

    friend ostream& operator << (ostream &cout, const Deque &a);
};

#endif // DEQUE_H_INCLUDED
