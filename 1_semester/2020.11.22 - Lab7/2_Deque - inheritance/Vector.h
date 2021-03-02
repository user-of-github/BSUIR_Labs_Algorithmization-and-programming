#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <iostream>

using std::cin,
      std::cout,
      std::ostream;

const int ERROR_CODE = -2020;

class Vector
{
protected:
    unsigned int length;
    unsigned int realSize = 2;
    int *arr = new int [2];
    void CopyArrays(int *from, int *to, const int &_startPos, const int &_finPos);
public:
    // constructors, destructor
    Vector ();
    Vector(const unsigned int &_size);
    Vector(const unsigned int &_size, const int &_value);
    Vector(const Vector &_a);
    ~Vector ();

    // methods
    unsigned int Size () const;
    void Print () const;
    int Top () const;
    int FindFirst (const int &_value) const;

    void Push (const int &_new);
    void Insert (const unsigned int &_index, const int &_new);

    void Pop ();
    void Remove (const unsigned int &_index);
    void RemoveAll ();

    //operators
    friend ostream& operator << (ostream &cout, const Vector &a);
    int operator [] (const unsigned int &_index) const;
    void operator = (const Vector &a);
};

#endif // VECTOR_H_INCLUDED
