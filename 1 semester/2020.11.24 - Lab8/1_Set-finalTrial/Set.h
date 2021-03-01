#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED

#include <iostream>
using std::cin,
      std::cout,
      std::ostream;

class Set
{
private:
    class Node
    {
    public:
        long long value;
        Node *parent = nullptr,
              *leftChild = nullptr,
               *rightChild = nullptr;

        Node (const long long &_value, Node *_parent = nullptr)
        {
            this->value = _value;
            this->parent = _parent;
            this->leftChild = nullptr;
            this->rightChild = nullptr;
        }
    };

    Node *root = nullptr;
    unsigned int _size = 0;

    void DeleteByPointer (Node *pointer);
    void RecursiveClear (Node *element);
    void RecursivePrint (const Node *element) const;

    Node * GetMinimumValue (Node *startNode) const;
    Node * GetMaximumValue (Node *startNode) const;
    Node * FindElement (const long long &_number) const;

public:
    Set ();
    ~Set ();

    unsigned int Size () const;
    bool Has (const long long &_check) const;

    void Add (const long long &_new);
    void Delete (const long long &_number);
    void Clear ();

    friend ostream & operator << (ostream & cout, const Set &object);
};

#endif // SET_H_INCLUDED
