#include "List.h"

template<class T>
class List<T>::ListItem
{
public:
    T value_;
    ListItem *previous_, *next_;

    explicit ListItem(const T &);
};

template<class T>
void List<T>::CopyListFrom(const List<T> &from)
{
    while (!this->Empty())
        this->PopBack();
    this->size_ = 0;

    ListItem *current = from.first_;
    while (current != nullptr)
    {
        this->PushBack(current->value_);
        current = current->next_;
    }
}


template<class T>
List<T>::ListItem::ListItem(const T &value): value_(value), next_(nullptr), previous_(nullptr)
{}

template<class T>
List<T>::List(): size_(0), first_(nullptr), last_(nullptr)
{}

template<class T>
List<T>::List(const std::initializer_list<T> &data): size_(0), first_(nullptr), last_(nullptr)
{
    unsigned int counter = 0;
    for (auto &item : data)
    {
        ++counter;
        this->PushBack(item);
    }
    this->size_ = counter;
}

template<class T>
List<T>::List(const List<T> &other):size_(0), first_(nullptr), last_(nullptr)
{
    this->CopyListFrom(other);
}

template<class T>
List<T>::List(List<T> &&other) noexcept: size_(0), first_(nullptr), last_(nullptr)
{
    this->size_ = 0;
    this->CopyListFrom(other);
    while (!other.Empty())
        other.PopBack();
}

template<class T>
void List<T>::PushBack(const T &newItem)
{
    auto *new_child = new ListItem(newItem);
    if (this->size_ == 0)
    {
        this->first_ = new_child;
    }
    else
    {
        auto *current_last = this->last_;
        current_last->next_ = new_child;
        new_child->previous_ = current_last;
    }
    this->last_ = new_child;
    ++this->size_;
}

template<class T>
void List<T>::PushFront(const T &newItem)
{
    auto *new_child = new ListItem(newItem);
    this->first_ = new_child;
    if (this->size_ == 0)
    {
        this->last_ = new_child;
    }
    else
    {
        auto *current_first = this->first_;
        new_child->next_ = current_first;
        current_first->previous_ = new_child;
    }
    ++this->size_;
}

template<class T>
void List<T>::PopBack()
{
    if (this->size_ != 0)
    {
        auto *current_last = this->last_;
        if (this->size_ == 1)
        {
            this->first_ = this->last_ = nullptr;
        }
        else
        {
            current_last->previous_->next_ = nullptr;
            this->last_ = current_last->previous_;
        }
        delete current_last;
        --this->size_;
    }
}

template<class T>
void List<T>::PopFront()
{
    if (this->size_ > 0)
    {
        auto *current_first = this->first_;
        if (this->size_ == 1)
        {
            this->first_ = this->last_ = nullptr;
        }
        else
        {
            this->first_ = current_first->next_;
            current_first->next_->previous_ = nullptr;
        }
        delete current_first;
        --this->size_;
    }
}

template<class T>
unsigned int List<T>::Size() const
{
    return this->size_;
}

template<class T>
void List<T>::Print() const
{
    auto *item = this->first_;
    if (item == nullptr)
        cout << "Empty";
    cout<<"{";
    while (item != nullptr)
    {
        cout << item->value_ << " ";
        item = item->next_;
    }
    cout << "}\n";
}

template<class T>
bool List<T>::Empty() const
{
    return !static_cast<bool>(this->size_);
}

template<class T>
typename List<T>::Iterator List<T>::begin()
{
    return Iterator(this->first_);
}

template<class T>
typename List<T>::Iterator List<T>::end()
{
    return Iterator(this->last_->next_);
}

template<class T>
List<T> &List<T>::operator=(const List<T> &other)
{
    while (!this->Empty())
        this->PopBack();

    this->CopyListFrom(other);

    return *this;
}

template<class T>
List<T> &List<T>::operator=(List<T> &&other) noexcept
{
    while (!this->Empty())
        this->PopBack();
    this->CopyListFrom(other);

    while (!other.Empty())
        other.PopBack();

    return *this;
}