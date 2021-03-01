#include "Set.h"

Set :: Set ()
{
    this->_size = 0;
    this->first = nullptr;
    this->last = nullptr;
}

Set :: ~Set ()
{
    this->Clear();
}

unsigned int Set :: Size () const
{
    return this->_size;
}

bool Set :: Contains (const double &_key) const
{
    return (this->Find(_key) != -1);
}

int Set :: Find (const double &_key) const
{
    Member *element = this->first;
    int counter = 0;
    for (counter = 0; counter < this->_size; counter ++)
    {
        if (element->value == _key)
            return counter;

        element = element->next;
    }

    return -1;
}

void Set :: Add (const double &_new)
{
    if (this->Find(_new) == -1)
    {
        Member *newElement = new Member (_new);
        if (this->_size == 0)
        {
            this->first = newElement;
            this->last = newElement;
            this->_size ++;
        }
        else
        {
            Member *currentLast = this->last;
            this->last = newElement;

            currentLast->next = newElement;
            newElement->previous = currentLast;

            this->_size ++;
        }
    }
    return;
}

double & Set :: operator [] (const unsigned int &_index) const
{
    if (_index >= 0 && _index < this->_size)
    {
        unsigned int counter;
        Member *element;

        if (_index < (this->_size - _index))
        {
            counter = 0;
            element = this->first;
            for (counter = 0; counter < _index; counter ++)
                element = element->next;

        }
        else
        {
            counter = this->_size - 1;
            element = this->last;
            for (counter = this->_size - 1; counter > _index; counter --)
            {
                element = element->previous;
            }
        }
        return element->value;
    }
}

void Set :: Remove (const double &_key)
{
    if (this->_size > 0)
    {
        int index = this->Find(_key);
        if (index != -1) // found
        {
            if (index == 0) // deleting first
            {
                Member *currentFirst = this->first;
                this->first = currentFirst->next;
                delete currentFirst;
                this->_size --;
            }
            else if (index == this->_size - 1) //deleting last
            {
                Member *currentLast = this->last;
                this->last = currentLast->previous;
                delete currentLast;
                this->_size --;
            }
            else // else, somewhere in the centre
            {
                Member *element;

                element = this->first;

                for (unsigned int counter = 0; counter <= index - 1; counter ++)
                    element = element->next;

                Member *deleted = element;
                Member *earlier = element->previous;
                Member *later = element->next;

                earlier->next = later;
                later->previous = earlier;
                delete deleted;
                this->_size --;
            }
            if (this->_size == 0)
            {
                this->first = nullptr;
                this->last = nullptr;
            }
            if (this->_size == 1)
            {
                this->last = this->first;
            }
        }
    }
    return;
}

void Set :: Clear ()
{
    while (this->_size > 1)
    {
        Member *currentFirst = this->first;
        this->first = currentFirst->next;
        delete currentFirst;
        this->_size --;
    }
    Member *temp = this->first;
    delete temp;

    this->first = nullptr;
    this->last = nullptr;

    this->_size = 0;
    return;
}

ostream & operator << (ostream &cout, const Set &object)
{
    cout<<"("<<object._size<<") {";

    for (unsigned int counter = 0; counter < object._size; counter ++)
    {
        cout<<object[counter]<<(counter != object._size - 1 ? "; " : "");
    }
    cout<<"}\n";
}
