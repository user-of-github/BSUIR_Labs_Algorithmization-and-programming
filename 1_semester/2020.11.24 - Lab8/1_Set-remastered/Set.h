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
        Member *parentElement;
        Member *leftChild, *rightChild;
        long long value;
        Member (const long long &_new, Member* _parent)
        {
            this->parentElement = _parent;
            this->leftChild = nullptr;
            this->rightChild = nullptr;
            this->value = _new;
        }
        ~Member ()
        {
            delete this->parentElement;
            delete this->leftChild;
            delete this->rightChild;
        }
    };

    unsigned long long _size = 0;
    Member *root;
    void PrintSetRecursive (Member *member) const;

public:
    Set ();
    long long getRoot () const
    {
        return (this->root)->value;
    }
    unsigned long long Size () const;
    bool Has (const long long &_check) const;
    void Add (const long long &_new);
    void Delete (const long long &_num);
    friend ostream & operator << (ostream & cout, const Set &object);
};

#endif // SET_H_INCLUDED
