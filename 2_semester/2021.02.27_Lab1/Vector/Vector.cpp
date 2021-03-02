#include "Vector.h"

template<class T>
void Vector<T>::CopyArray(const T *from, T *to, const unsigned int &how_many_elements)
{
    for (unsigned int counter = 0; counter < how_many_elements; ++counter)
        to[counter] = from[counter];
}

template<class T>
void Vector<T>::CopyFullInstance(const Vector<T> &other)
{
    delete[] this->array_;
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    this->array_ = new T[this->capacity_];
    CopyArray(other.array_, this->array_, this->size_);
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
Vector<T>::Vector(const Vector<T> &other):array_(nullptr)
{
    this->CopyFullInstance(other);
}

template<class T>
Vector<T>::Vector(Vector<T> &&other) noexcept: array_(nullptr)
{
    this->CopyFullInstance(other);
    other.capacity_ = other.size_ = 0;
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
    delete[] copy;
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
    std::cout << "(" << this->size_ << "):{ ";
    for (unsigned int counter = 0; counter < this->size_; ++counter)
        std::cout << this->array_[counter] << " ";
    std::cout << "}\n";
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
    return !static_cast<bool>(this->size_);
}

template<class T>
T &Vector<T>::operator[](const unsigned int &index)
{
    if (index < this->size_)
        return this->array_[index];
}

template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
    this->array_ = nullptr;
    this->CopyFullInstance(other);
    return *this;
}

template<class T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other) noexcept
{
    this->CopyFullInstance(other);
    delete[] other.array_;
    other.size_ = other.capacity_ = 0;
    return *this;
}


template<class T>
typename Vector<T>::Iterator Vector<T>::begin()
{
    return Iterator(this->array_);
}

template<class T>
typename Vector<T>::Iterator Vector<T>::end()
{
    return Iterator(this->array_ + this->Size());
}