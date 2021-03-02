#include "Vector.h"

void Vector::CopyArrays (int *from, int *to, const int &_startPos, const int &_finPos)
{
    if (_startPos >= 0 && _finPos >= 0 )
    {
        for (unsigned int counter = _startPos; counter <= _finPos; counter ++)
        {
            to[counter] = from[counter];
        }
    }

    return;
}

Vector::Vector ()
{
    this->length = 0;
    this->arr = new int [this->realSize];
}

Vector::Vector(const unsigned int &_size)
{
    *this = Vector();
    for (unsigned int counter = 0; counter < _size; counter ++)
        this->Push(0);
}

Vector::Vector(const unsigned int &_size, const int &_value)
{
    *this = Vector();
    for (unsigned int counter = 0; counter < _size; counter ++)
        this->Push(_value);
}

Vector::Vector(const Vector &_a)
{
    this->realSize = _a.realSize;
    this->length = _a.length;
    this->arr = new int[realSize];

    CopyArrays(_a.arr, this->arr, 0, this->length);
}

Vector::~Vector()
{
    delete[] this->arr;
}

unsigned int Vector::Size () const
{
    return this->length;
}

int Vector::Top () const
{
    return (this->length != 0 ? this->arr[this->length - 1] : ERROR_CODE);
}

void Vector::Print () const
{
    for (int counter = 0; counter < this->length; counter ++)
        cout<<this->arr[counter]<<" ";

    cout<<"\n";

    return;
}

void Vector::Push (const int &_new)
{
    if (this->realSize == this->length)
    {
        int *backup = new int [this->length];
        CopyArrays(this->arr, backup, 0, this->length - 1);
        delete[] this->arr;

        this->realSize *= 2;
        this->arr = new int [this->realSize];
        this->length++;

        CopyArrays(backup, this->arr, 0, this->length - 2);
        this->arr[this->length - 1] = _new;

        delete[] backup;
    }
    else
    {
        this->length ++;
        this->arr[this->length - 1] = _new;
    }

    return;
}

void Vector::Insert (const unsigned int &_index, const int &_new)
{
    if (_index >= 0 && _index <= this->length)
    {
        this->Push(0);

        for (unsigned int counter = this->length - 1; counter > _index; counter --)
        {
            this->arr[counter] = this->arr[counter - 1];
        }

        this->arr[_index] = _new;
    }


    return;
}

void Vector::Remove (const unsigned int &_index)
{
    if (_index >= 0 && _index < this->length && this->length > 0)
    {
        for (unsigned int counter = _index; counter < this->length - 1; counter ++)
        {
            this->arr[counter] = this->arr[counter + 1];
        }

        this->length --;
    }
    return;
}

void Vector::Pop ()
{
    if (this->length > 0)
        this->length --;

    return;
}

void Vector::RemoveAll()
{
    this->length = 0;
    this->realSize = 2;
    delete[] this->arr;
    this->arr = new int [this->realSize];

    return;
}

int Vector::FindFirst (const int &_value) const
{
    int counter = 0;
    for (counter = 0; counter < this->length; counter ++)
    {
        if (this->arr[counter] == _value)
            break;
    }

    return (counter < this->length ? counter : ERROR_CODE);
}

ostream& operator << (ostream &cout, const Vector &a)
{
    cout<<"("<<a.length<<") ";
    cout<<"[";
    for (unsigned int counter = 0; counter < a.length; counter ++)
    {
        cout<<a.arr[counter]<<(counter == a.length - 1 ? "" : "; ");
    }
    cout<<"]\n";

    return cout;
}


int Vector::operator [] (const unsigned int &_index) const
{
    return ((_index >= 0 && _index < this->length) ? this->arr[_index] : ERROR_CODE);
}

void Vector::operator = (const Vector &a)
{
    this->realSize = a.realSize;
    this->length = a.length;
    this->arr = new int[realSize];

    CopyArrays(a.arr, this->arr, 0, this->length);
    return;
}
