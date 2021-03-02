#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED

#include <iostream>

using std::cin,
      std::cout,
      std::ostream,
      std::ios;

class Set
{
private:
    class Member
    {
    public:
        double value;
        Member *next = nullptr,
                *previous = nullptr;

        Member (const double &_newValue)
        {
            this->value = _newValue;
            this->next = nullptr;
            this->previous = nullptr;
        }
    };
    unsigned int _size;
    Member *first, *last;
    int Find (const double &_key) const;
    double & operator [] (const unsigned int &_index) const;
public:
    Set ();
    ~Set ();

    unsigned int Size () const;
    bool Contains (const double &_key) const;
    void Add (const double &_new);
    void Remove (const double &_key);

    void Clear ();
    friend ostream & operator << (ostream &cout, const Set &object);
};

#endif // SET_H_INCLUDED
