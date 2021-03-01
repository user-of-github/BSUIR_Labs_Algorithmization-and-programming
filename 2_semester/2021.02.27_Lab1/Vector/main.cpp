#include <iostream>
#include <iterator>

using std::cout;
using std::cin;

template<class T>
class Vector
{
private:
    const unsigned int kStartCapacity = 4;

    T *array_;
    unsigned int size_, capacity_;

    void CopyArray(const T *, T *, const unsigned int &);

public:
    class Iterator;
    Vector();

    explicit Vector(const unsigned int &);

    Vector(const unsigned int &, const T &);

    Vector(const std::initializer_list<T> &);

    Vector(const Vector<T> &);

    Vector(Vector<T> &&) noexcept;

    ~Vector();

    void Resize(const unsigned int &);

    void PushBack(const T &);

    void PopBack();

    void Print() const;

    unsigned int Size() const;

    unsigned int Capacity() const;

    bool Empty() const;

    T operator[](const unsigned int &) const;

    Vector<T> &operator=(const Vector<T> &);
    Vector<T>& operator=(Vector<T> &&) noexcept;
};

template<class T>
class Vector<T>::Iterator:std::iterator<std::random_access_iterator_tag, T>
{
private:
    T *object_;
public:
    
};

int main()
{
    Vector<int> test({1, 2, 3, 4});
    Vector<int> test2 = Vector<int>(5, 6);

    test2.Print();

    //test2 = std::move(test);

    test2.Print();

    auto test3 = Vector<int>();
    for (unsigned counter = 10; counter >= 6; --counter)
        test3.PushBack(counter);

    test3.Print();
    test2 = test3;
    test2.Print();
    test2 = std::move(test);
    test2.Print();
    return 0;
}


template<class T>
void Vector<T>::CopyArray(const T *from, T *to, const unsigned int &how_many_elements)
{
    for (unsigned int counter = 0; counter < how_many_elements; ++counter)
        to[counter] = from[counter];
}

template<class T>
Vector<T>::Vector():size_(0), capacity_(kStartCapacity)
{
    this->array_ = new T[this->capacity_];
}

template<class T>
Vector<T>::Vector(const unsigned int &capacity):size_(0), capacity_(capacity)
{
    this->array_ = new T[this->capacity_];
}

template<class T>
Vector<T>::Vector(const unsigned int &capacity, const T &start_value):capacity_(capacity), size_(capacity)
{
    this->array_ = new T[this->capacity_];
    for (unsigned int counter = 0; counter < this->size_; ++counter)
        this->array_[counter] = start_value;
}

template<class T>
Vector<T>::Vector(const std::initializer_list<T> &list):capacity_(list.size()), size_(0)
{
    this->array_ = new T[this->capacity_];
    for (const T &item : list)
        this->array_[this->size_++] = item;
    this->size_ = list.size();
}

template<class T>
Vector<T>::Vector(const Vector<T> &object):size_(object.size_), capacity_(object.capacity_)
{
    this->array_ = new T[this->capacity_];
    this->CopyArray(object.array_, this->array_, this->size_);
}

template<class T>
Vector<T>::Vector(Vector<T> &&other) noexcept :size_(other.size_), capacity_(other.capacity_)
{
    other.capacity_ = other.size_ = 0;
    this->CopyArray(other.array_, this->array_, this->size_);
    delete[] other.array_;
}

template<class T>
Vector<T>::~Vector()
{
    delete[] this->array_;
}

template<class T>
void Vector<T>::Resize(const unsigned int &new_capacity)
{
    T *copy = new T[this->size_];
    this->CopyArray(this->array_, copy, this->size_);
    delete[] this->array_;
    this->capacity_ = new_capacity;
    this->array_ = new T[this->capacity_];
    this->CopyArray(copy, this->array_, this->size_);
}

template<class T>
void Vector<T>::PushBack(const T &new_item)
{
    if (this->size_ == this->capacity_)
        this->Resize((this->capacity_ * 2));

    ++this->size_;
    this->array_[this->size_ - 1] = new_item;
}

template<class T>
void Vector<T>::PopBack()
{
    if (this->size_ > 0)
        --this->size_;
}

template<class T>
void Vector<T>::Print() const
{
    for (unsigned int counter = 0; counter < this->size_; ++counter)
        cout << this->array_[counter] << " ";
    cout << "\n";
}

template<class T>
unsigned int Vector<T>::Size() const
{
    return this->size_;
}

template<class T>
unsigned int Vector<T>::Capacity() const
{
    return this->capacity_;
}

template<class T>
bool Vector<T>::Empty() const
{
    return static_cast<bool>(this->size_);
}

template<class T>
T Vector<T>::operator[](const unsigned int &index) const
{
    return (index < this->size_ ? this->array_[index] : T());
}

template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &object)
{
    if (this != &object)
    {
        delete[] this->array_;
        this->size_ = object.size_;
        this->capacity_ = object.capacity_;
        this->array_ = new T[this->capacity_];
        CopyArray(object.array_, this->array_, this->size_);
    }
    return *this;
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T> &&other) noexcept
{
    delete this->array_;
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    this->array_ = new T [this->capacity_];
    this->CopyArray(other.array_, this->array_, this->size_);
    delete[] other.array_;
    other.size_ = other.capacity_ = 0;
    return *this;
}