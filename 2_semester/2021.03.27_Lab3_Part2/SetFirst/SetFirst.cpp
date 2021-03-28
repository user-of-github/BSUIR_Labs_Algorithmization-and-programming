//
// Created by User on 28-Mar-21.
//

#include "SetFirst.h"

#include "SetFirst.h"


template<typename T>
SetFirst<T>::SetFirst():size_(0), root_(shared_ptr<Node>(nullptr))
{}

template<typename T>
SetFirst<T>::SetFirst(const SetFirst<T> &rhs):size_(0), root_(shared_ptr<Node>(nullptr))
{
    this->RecursiveCopy(rhs.root_);
}

template<typename T>
SetFirst<T>::SetFirst(SetFirst<T> &&rhs) noexcept: size_(0), root_(shared_ptr<Node>(nullptr))
{
    this->Clear();
    this->root_ = rhs.root_;
    auto rhs_left = rhs.root_->left_child_,
            rhs_right = rhs.root_->right_child_;
    if (rhs_right != shared_ptr<Node>(nullptr))
        rhs_right->parent_ = this->root_;
    if (rhs_left != shared_ptr<Node>(nullptr))
        rhs_left->parent_ = this->root_;

    this->size_ = rhs.size_;
    rhs.root_ = shared_ptr<Node>(nullptr);
    rhs.size_ = 0;
}

template<typename T>
void SetFirst<T>::Add(const T &new_item)
{
    auto try_has = this->FindElement(new_item);
    if (try_has != shared_ptr<Node>(nullptr))
        return;

    auto *new_element = new Node(new_item, shared_ptr<Node>(nullptr));
    if (this->size_ != 0)
    {
        auto element = this->root_, parent = this->root_;

        while (element != shared_ptr<Node>(nullptr))
        {
            parent = element;
            element = new_item <= element->value_ ? element->left_child_ : element->right_child_;
        }

        new_element->parent_ = parent;
        new_item <= parent->value_ ? (parent->left_child_ = shared_ptr<Node>(new_element))
                                   : (parent->right_child_ = shared_ptr<Node>(new_element));
    } else
    {
        this->root_ = shared_ptr<Node>(new_element);
    }

    ++this->size_;
}

template<typename T>
void SetFirst<T>::Delete(const T &value)
{
    auto search_element = this->FindElement(value);
    if (search_element != shared_ptr<Node>(nullptr) && this->size_ > 0)
    {
        this->DeleteByPointer(search_element);
        --this->size_;
    }

    if (this->size_ == 0)
        this->root_ = shared_ptr<Node>(nullptr);
}

template<typename T>
void SetFirst<T>::Clear()
{
    if (this->root_ != shared_ptr<Node>(nullptr) && this->size_ != 0)
    {
        this->DeleteTree(this->root_);
        this->root_ = shared_ptr<Node>(nullptr);
    }
    this->size_ = 0;
}

template<typename T>
constexpr bool SetFirst<T>::Has(const T &value) const noexcept
{
    return this->FindElement(value) != shared_ptr<Node>(nullptr);
}

template<typename T>
constexpr size_t SetFirst<T>::Size() const noexcept
{
    return this->size_;
}

template<typename T>
constexpr bool SetFirst<T>::Empty() const noexcept
{
    return this->size_ == 0;
}

template<typename T>
constexpr T SetFirst<T>::FindNext(const T &key) const
{
    return ((this->NextElement(this->FindElement(key)))->value_).second;
}

template<typename T>
constexpr T SetFirst<T>::FindPrevious(const T &key) const
{
    return ((this->PreviousElement(this->FindElement(key)))->value_);
}

template<typename T>
ostream &operator<<(ostream &os, const SetFirst<T> &element)
{
    os << "Set(" << element.size_ << "): {";
    element.RecursivePrint(element.root_, os);
    os << "}\n";

    return os;
}


template<typename T>
SetFirst<T> &SetFirst<T>::operator=(SetFirst<T> &&rhs) noexcept
{
    this->Clear();
    this->root_ = rhs.root_;
    auto rhs_left = rhs.root_->left_child_,
            rhs_right = rhs.root_->right_child_;
    if (rhs_right != shared_ptr<Node>(nullptr))
        rhs_right->parent_ = this->root_;
    if (rhs_left != shared_ptr<Node>(nullptr))
        rhs_left->parent_ = this->root_;

    this->size_ = rhs.size_;
    rhs.root_ = shared_ptr<Node>(nullptr);
    rhs.size_ = 0;

    return *this;
}


template<typename T>
class SetFirst<T>::Node
{
public:
    T value_;
    shared_ptr<Node> left_child_,
            right_child_,
            parent_;

    Node(const T &, shared_ptr<Node>);
};

template<typename T>
SetFirst<T>::Node::Node(const T &value, shared_ptr<Node> parent)
        :value_(value), parent_(parent), left_child_(nullptr), right_child_(nullptr)
{}

template<typename T>
void SetFirst<T>::RecursiveCopy(const shared_ptr<Node> &rhs)
{
    if (rhs == shared_ptr<Node>(nullptr))
        return;

    this->Add(rhs->value_);
    this->RecursiveCopy(rhs->left_child_);
    this->RecursiveCopy(rhs->right_child_);
}

template<typename T>
void SetFirst<T>::RecursivePrint(const shared_ptr<Node> &element, ostream &os) const
{
    if (element != shared_ptr<Node>(nullptr))
    {
        RecursivePrint(element->left_child_, os);
        os << ' ' << element->value_ << ' ';
        RecursivePrint(element->right_child_, os);
    }
}

template<typename T>
shared_ptr<typename SetFirst<T>::Node> SetFirst<T>::FindElement(const T &key) const
{
    auto search_element = this->root_;

    while (search_element != shared_ptr<Node>(nullptr) && search_element->value_ != key)
        search_element = key <= search_element->value_ ? search_element->left_child_
                                                       : search_element->right_child_;

    return search_element;
}


template<typename T>
void SetFirst<T>::DeleteByPointer(shared_ptr<Node> &target)
{
    if (target == shared_ptr<Node>(nullptr))
        return;

    if (target->left_child_ != shared_ptr<Node>(nullptr) && target->right_child_ != shared_ptr<Node>(nullptr))
    {
        auto local_max = this->GetMaximumValue(target->left_child_);
        target->value_ = local_max->value_;
        DeleteByPointer(local_max);
    } else if (target->left_child_ != shared_ptr<Node>(nullptr))
        (target == target->parent_->left_child_) ? (target->parent_->left_child_ = target->left_child_)
                                                 : (target->parent_->right_child_ = target->left_child_);
    else if (target->right_child_ != shared_ptr<Node>(nullptr))
        (target == target->parent_->right_child_) ? (target->parent_->right_child_ = target->right_child_)
                                                  : (target->parent_->left_child_ = target->right_child_);
    else
        (target == target->parent_->left_child_) ? (target->parent_->left_child_ = shared_ptr<Node>(nullptr))
                                                 : target->parent_->right_child_ = shared_ptr<Node>(nullptr);
}

template<typename T>
shared_ptr<typename SetFirst<T>::Node>
SetFirst<T>::GetMaximumValue(const shared_ptr<Node> &start) const noexcept
{
    auto response = start;

    while (response->right_child_ != shared_ptr<Node>(nullptr))
        response = response->right_child_;

    return response;
}

template<typename T>
shared_ptr<typename SetFirst<T>::Node>
SetFirst<T>::GetMinimumValue(const shared_ptr<Node> &start) const noexcept
{
    auto response = start;

    while (response->left_child_ != shared_ptr<Node>(nullptr))
        response = response->left_child_;

    return response;
}

template<typename T>
shared_ptr<typename SetFirst<T>::Node> SetFirst<T>::NextElement(shared_ptr<Node> target) const
{
    if (target->right_child_ != shared_ptr<Node>(nullptr))
        return GetMaximumValue(target->right_child_);

    auto response = target->parent_;

    while (response != shared_ptr<Node>(nullptr) && target == response->right_child_)
    {
        target = response;
        response = response->parent_;
    }
    return response;
}

template<typename T>
shared_ptr<typename SetFirst<T>::Node> SetFirst<T>::PreviousElement(shared_ptr<Node> target) const
{
    if (target->left_child_ != shared_ptr<Node>(nullptr))
        return this->GetMinimumValue(target->left_child_);

    auto response = target->parent_;
    while (response != shared_ptr<Node>(nullptr) and target == response->left_child_)
    {
        target = response;
        response = response->parent_;
    }
    return response;
}

template<typename T>
void SetFirst<T>::DeleteTree(shared_ptr<Node> &node)
{
    if (node == shared_ptr<Node>(nullptr))
        return;

    this->DeleteTree(node->left_child_);
    this->DeleteTree(node->right_child_);

    node = shared_ptr<Node>(nullptr);
}


template<class T>
class SetFirst<T>::Iterator : std::iterator<std::bidirectional_iterator_tag, T>
{
public:
    Iterator();

    Iterator(SetFirst *, shared_ptr<Node>);

    Node *operator->();

    T &operator*();

    T operator*() const;

    Iterator &operator++();

    const Iterator operator++(int);

    Iterator &operator--();

    const Iterator operator--(int);

    bool operator==(const Iterator &) const;

    bool operator!=(const Iterator &) const;

private:
    shared_ptr<Node> object_;
    SetFirst *owner_;
};

template<typename T>
typename SetFirst<T>::Iterator SetFirst<T>::begin()
{
    return Iterator(this, this->GetMinimumValue(this->root_));
}

template<typename T>
typename SetFirst<T>::Iterator SetFirst<T>::end()
{
    return ++Iterator(this, this->GetMaximumValue(this->root_));
}


template<class T>
SetFirst<T>::Iterator::Iterator(): object_(shared_ptr<Node>(nullptr)), owner_(shared_ptr<Node>(nullptr))
{}

template<class T>
SetFirst<T>::Iterator::Iterator(SetFirst *owner, shared_ptr<Node> link): object_(link), owner_(owner)
{}

template<class T>
T &SetFirst<T>::Iterator::operator*()
{
    return this->object_->value_;
}

template<class T>
typename SetFirst<T>::Node *SetFirst<T>::Iterator::operator->()
{
    return this->object_;
}

template<class T>
T SetFirst<T>::Iterator::operator*() const
{
    return *this->object_;
}

template<class T>
typename SetFirst<T>::Iterator &SetFirst<T>::Iterator::operator--()
{
    this->object_ = this->owner_->PreviousElement(this->object_);
    return *this;
}

template<class T>
bool SetFirst<T>::Iterator::operator==(const SetFirst<T>::Iterator &it) const
{
    return this->object_ == it.object_;
}

template<class T>
bool SetFirst<T>::Iterator::operator!=(const SetFirst<T>::Iterator &it) const
{
    return this->object_ != it.object_;
}

template<class T>
typename SetFirst<T>::Iterator &SetFirst<T>::Iterator::operator++()
{
    this->object_ = this->owner_->NextElement(this->object_);
    return *this;
}

template<class T>
const typename SetFirst<T>::Iterator SetFirst<T>::Iterator::operator++(int)
{
    Iterator temp(this->object_);
    ++(*this);
    return temp;
}

template<class T>
const typename SetFirst<T>::Iterator SetFirst<T>::Iterator::operator--(int)
{
    Iterator temp(this->object_);
    --(*this);
    return temp;
}