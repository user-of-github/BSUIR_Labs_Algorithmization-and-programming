#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

#include <iostream>

using std::cin,
      std::cout,
      std::ostream;

class Deque
{
private:
    class Node
    {
    public:
        Node *next;

        int value;

        Node (const int &_value, Node *_next = nullptr)
        {
            this->value = _value;
            this->next = _next;
        }

        void operator = (const int &_value)
        {
            this->value = _value;
            return;
        }
    };

    Node *first;
    Node *last;
    unsigned int length;

public:
    // constructors, destructor
    Deque ();
    Deque (const Deque &_obj);
    ~Deque ();

    // methods
    unsigned int Size () const;
    int FindFirst (const int &_toFind) const;

    void Push (const int &_new);
    void Unshift (const int &_new);
    void Insert (const unsigned int &_index, const int &_new);

    void Pop ();
    void Shift ();
    void Remove (const unsigned int &_index);
    void RemoveAll ();

    // operators
    int & operator [] (const unsigned int &_index) const;
    void operator = (const Deque &_obj);
    friend ostream & operator << (ostream &cout, const Deque &obj);
};

#endif // DEQUE_H_INCLUDED
