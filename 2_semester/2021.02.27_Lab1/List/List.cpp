#include "List.h"

template<class T>
class List<T>::ListItem
{
public:
    T value_;
    ListItem *previous_, *next_;

    ListItem();

    explicit ListItem(const T &);
};

template<class T>
void List<T>::CopyListFrom(const List<T> &from)
{
    this->Clear();

    ListItem *current = from.first_;
    while (current != from.pseudo_last_ && current != nullptr)
    {
        this->PushBack(current->value_);
        current = current->next_;
    }
}

template<class T>
void List<T>::CreatePseudoLast()
{
    this->pseudo_last_ = new ListItem();
    this->pseudo_last_->next_ = nullptr;
    this->pseudo_last_->previous_ = nullptr;
}

template<class T>
void List<T>::UpdatePseudoLast()
{
    if (this->pseudo_last_ == nullptr)
        this->CreatePseudoLast();

    if (this->last_ != nullptr)
    {
        this->last_->next_ = this->pseudo_last_;
        this->pseudo_last_->previous_ = this->last_;
    }
}

template<class T>
List<T>::ListItem::ListItem(): next_(nullptr), previous_(nullptr)
{}

template<class T>
List<T>::ListItem::ListItem(const T &value): value_(value), next_(nullptr), previous_(nullptr)
{}

template<class T>
List<T>::List(): size_(0), first_(nullptr), last_(nullptr)
{
    this->CreatePseudoLast();
}

template<class T>
List<T>::List(const std::initializer_list<T> &data): size_(0), first_(nullptr), last_(nullptr)
{
    this->CreatePseudoLast();
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
    this->CreatePseudoLast();
    this->CopyListFrom(other);
    this->UpdatePseudoLast();
}

template<class T>
List<T>::List(List<T> &&other) noexcept: size_(0), first_(nullptr), last_(nullptr)
{
    this->CreatePseudoLast();
    this->size_ = 0;
    this->CopyListFrom(other);
    other.Clear();
    this->UpdatePseudoLast();
    other.CreatePseudoLast();
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

    this->UpdatePseudoLast();
}

template<class T>
void List<T>::PushFront(const T &newItem)
{
    auto *new_child = new ListItem(newItem);
    if (this->size_ == 0)
    {
        this->last_ = this->first_ = new_child;
    }
    else
    {
        auto *current_first = this->first_;
        new_child->next_ = current_first;
        current_first->previous_ = new_child;
    }
    this->first_ = new_child;
    ++this->size_;
    this->UpdatePseudoLast();
}

template<class T>
void List<T>::PopBack()
{
    if (this->size_ != 0)
    {
        --this->size_;
        if (this->size_ == 0)
        {
            this->first_ = this->last_ = nullptr;
            this->CreatePseudoLast();
            return;
        }

        auto *current_last = this->last_;
        current_last->previous_->next_ = nullptr;
        this->last_ = current_last->previous_;
        delete current_last;
        this->UpdatePseudoLast();
    }
}

template<class T>
void List<T>::PopFront()
{
    if (this->size_ > 0)
    {
        --this->size_;
        if (this->size_ == 0)
        {
            this->first_ = this->last_ = nullptr;
            this->CreatePseudoLast();
            return;
        }

        auto *current_first = this->first_;
        this->first_ = current_first->next_;
        current_first->next_->previous_ = nullptr;
        delete current_first;
        this->UpdatePseudoLast();
    }
}

template<class T>
unsigned int List<T>::Size() const
{
    return this->size_;
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
    return Iterator(this->pseudo_last_);
}

template<class T>
List<T> &List<T>::operator=(const List<T> &other)
{
    this->CopyListFrom(other);
    this->UpdatePseudoLast();
    return *this;
}

template<class T>
List<T> &List<T>::operator=(List<T> &&other) noexcept
{
    this->CopyListFrom(other);
    this->UpdatePseudoLast();

    other.Clear();

    other.CreatePseudoLast();
    return *this;
}

template<typename T1>
ostream &operator<<(ostream &os, const List <T1> &obj)
{
    auto *item = obj.first_;

    os << "(" << obj.size_ << "): ";
    os << "{ ";
    while (item != obj.pseudo_last_ && item != nullptr)
    {
        os << item->value_ << " ";
        item = item->next_;
    }
    os << "}\n";

    return os;
}

template<class T>
void List<T>::Clear()
{
    while (!this->Empty())
        this->PopBack();
}
