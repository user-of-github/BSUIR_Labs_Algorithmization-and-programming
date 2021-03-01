#include "Deque.h"

Deque::Deque ()
{
    this->length = 0;
    this->first = nullptr;
}

Deque::Deque (const Deque &_obj)
{
    this->length = 0;
    this->first = nullptr;

    Node *element = _obj.first;
    for (unsigned int counter = 0; counter < _obj.length; counter ++)
    {
        int temp = element->value;
        this->Push(temp);
        element = element->next;
    }
    this->length = _obj.length;
}
Deque::~Deque ()
{
    this->RemoveAll();
}

unsigned int Deque::Size () const
{
    return this->length;
}

int Deque::FindFirst (const int &_toFind) const
{
    Node *element = this->first;
    unsigned int counter = 0;
    for (counter = 0; counter < this->length; counter ++)
    {
        if (element->value == _toFind)
        {
            break;
        }
        element = element->next;
    }

    return (counter < this->length ? counter : -1);
}

void Deque::Push (const int &_new)
{
    if (this->length == 0)
    {
        this->first = new Node(_new);
        this->last = first;
    }
    else
    {
        Node *someNew = new Node(_new);
        this->last->next = someNew;
        this->last = someNew;
    }

    this->length ++;

    return;
}

void Deque::Unshift (const int &_new)
{
    this->first = new Node (_new, this->first);
    this->length ++;

    return;
}

void Deque::Insert (const unsigned int &_index, const int &_new)
{
    if (_index > 0 && _index < this->length)
    {
        Node *element = this->first;
        for (unsigned int counter = 0; counter < _index - 1; counter ++)
        {
            element = element->next;
        }

        Node *newElement = new Node(_new, element->next);
        element->next = newElement;

        this->length++;
    }
    else if (_index == 0)
    {
        this->Unshift(_new);
    }
    else if (_index == this->length)
    {
        this->Push(_new);
    }

    return;
}

void Deque::Pop ()
{
    if (this->length > 0)
    {
        this->Remove(this->length - 1);
    }

    return;
}

void Deque::Shift ()
{
    if (this->length > 0)
    {
        Node *temp = (this->first);
        this->first = this->first->next;

        delete temp;

        this->length --;
    }
    return;
}

void Deque::Remove (const unsigned int &_index)
{
    if (_index >= 0 && _index < this->length)
    {
        if (_index == 0)
        {
            this->Shift();
        }
        else
        {
            unsigned int counter = 0;

            Node *element = this->first;
            for (counter = 0; counter < _index - 1; counter ++)
            {
                element = element->next;
            }

            Node *deleted = element->next;

            element->next = deleted->next;
            delete deleted;

            if (_index == this->length - 1)
            {
                this->last = element;
            }

            this->length --;
        }
    }

    return;
}

void Deque::RemoveAll()
{
    while (this->length > 0)
        this->Shift();

    return;
}

int & Deque:: operator [] (const unsigned int &_index) const
{
    if (_index >= 0 && _index < this->length)
    {
        Node *element = this->first;
        for (unsigned int counter = 0; counter < _index; counter ++)
        {
            element = element->next;
        }

        return element->value;
    }
}

void Deque::operator = (const Deque &_obj)
{
    *(this) = Deque(_obj);
    return;
}

ostream & operator << (ostream &cout, const Deque &obj)
{
    cout<<"("<<obj.length<<") {";
    for (unsigned int counter = 0; counter < obj.length; counter ++)
    {
        cout<<obj[counter]<<(counter != (obj.length - 1) ? "; " : "");
    }
    cout<<"}";

    cout<<"\n";

    return cout;
}
