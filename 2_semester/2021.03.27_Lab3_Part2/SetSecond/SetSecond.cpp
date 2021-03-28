#include "SetSecond.h"


template<typename T>
SetSecond<T>::SetSecond():size_(0), root_(shared_ptr<Node>(nullptr))
{}

template<typename T>
SetSecond<T>::SetSecond(const SetSecond<T> &rhs):size_(0), root_(shared_ptr<Node>(nullptr))
{
    this->RecursiveCopy(rhs.root_);
}

template<typename T>
SetSecond<T>::SetSecond(SetSecond<T> &&rhs) noexcept: size_(0), root_(shared_ptr<Node>(nullptr))
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
void SetSecond<T>::Add(const T &new_item)
{
    auto try_has = this->FindElement(new_item);
    if (try_has != shared_ptr<Node>(nullptr))
        return;

    auto new_element = std::make_shared<Node>(Node(new_item, shared_ptr<Node>(nullptr)));

    if (this->size_ != 0)
    {
        auto element = this->root_, parent = this->root_;

        while (element != shared_ptr<Node>(nullptr))
        {
            parent = element;
            element = new_item <= element->value_ ? element->left_child_ : element->right_child_;
        }

        new_element->parent_ = parent;
        new_item <= parent->value_ ? (parent->left_child_ = new_element)
                                   : (parent->right_child_ = new_element);
    }
    else
    {
        this->root_ = new_element;
    }

    this->UpdateListAdd(new_element);
    ++this->size_;
}

template<typename T>
void SetSecond<T>::Delete(const T &value)
{
    auto search_element = this->FindElement(value);
    if (search_element != shared_ptr<Node>(nullptr) && this->size_ > 0)
    {
        this->UpdateListDelete(search_element);
        this->DeleteByPointer(search_element);
        --this->size_;
    }

    if (this->size_ == 0)
        this->root_ = shared_ptr<Node>(nullptr);
}

template<typename T>
void SetSecond<T>::Clear()
{
    if (this->root_ != shared_ptr<Node>(nullptr) && this->size_ != 0)
    {
        this->DeleteTree(this->root_);
        this->root_ = shared_ptr<Node>(nullptr);
    }
    this->size_ = 0;
}

template<typename T>
constexpr bool SetSecond<T>::Has(const T &value) const noexcept
{
    return this->FindElement(value) != shared_ptr<Node>(nullptr);
}

template<typename T>
constexpr size_t SetSecond<T>::Size() const noexcept
{
    return this->size_;
}

template<typename T>
constexpr bool SetSecond<T>::Empty() const noexcept
{
    return this->size_ == 0;
}

template<typename T>
constexpr T SetSecond<T>::FindNext(const T &key) const
{
    return ((this->NextElement(this->FindElement(key)))->value_).second;
}

template<typename T>
constexpr T SetSecond<T>::FindPrevious(const T &key) const
{
    return ((this->PreviousElement(this->FindElement(key)))->value_);
}

template<typename T>
ostream &operator<<(ostream &os, const SetSecond<T> &element)
{
    os << "Set(" << element.size_ << "): {";
    element.RecursivePrint(element.root_, os);
    os << "}\n";

    return os;
}


template<typename T>
SetSecond<T> &SetSecond<T>::operator=(SetSecond<T> &&rhs) noexcept
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
class SetSecond<T>::Node
{
public:
    T value_;
    shared_ptr<Node> left_child_,
            right_child_,
            parent_;

    Node(const T &, shared_ptr<Node>);
};

template<typename T>
SetSecond<T>::Node::Node(const T &value, shared_ptr<Node> parent)
        :value_(value), parent_(parent), left_child_(nullptr), right_child_(nullptr)
{}

template<typename T>
void SetSecond<T>::RecursiveCopy(const shared_ptr<Node> &rhs)
{
    if (rhs == shared_ptr<Node>(nullptr))
        return;

    this->Add(rhs->value_);
    this->RecursiveCopy(rhs->left_child_);
    this->RecursiveCopy(rhs->right_child_);
}

template<typename T>
void SetSecond<T>::RecursivePrint(const shared_ptr<Node> &element, ostream &os) const
{
    if (element != shared_ptr<Node>(nullptr))
    {
        RecursivePrint(element->left_child_, os);
        os << ' ' << element->value_ << ' ';
        RecursivePrint(element->right_child_, os);
    }
}

template<typename T>
shared_ptr<typename SetSecond<T>::Node> SetSecond<T>::FindElement(const T &key) const
{
    auto search_element = this->root_;

    while (search_element != shared_ptr<Node>(nullptr) && search_element->value_ != key)
        search_element = key <= search_element->value_ ? search_element->left_child_
                                                       : search_element->right_child_;

    return search_element;
}


template<typename T>
void SetSecond<T>::DeleteByPointer(shared_ptr<Node> &target)
{
    if (target == shared_ptr<Node>(nullptr))
        return;

    if (target->left_child_ != shared_ptr<Node>(nullptr) && target->right_child_ != shared_ptr<Node>(nullptr))
    {
        auto local_max = this->GetMaximumValue(target->left_child_);
        target->value_ = local_max->value_;
        DeleteByPointer(local_max);
    }
    else if (target->left_child_ != shared_ptr<Node>(nullptr))
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
shared_ptr<typename SetSecond<T>::Node>
SetSecond<T>::GetMaximumValue(const shared_ptr<Node> &start) const noexcept
{
    auto response = start;

    while (response->right_child_ != shared_ptr<Node>(nullptr))
        response = response->right_child_;

    return response;
}

template<typename T>
shared_ptr<typename SetSecond<T>::Node>
SetSecond<T>::GetMinimumValue(const shared_ptr<Node> &start) const noexcept
{
    auto response = start;

    while (response->left_child_ != shared_ptr<Node>(nullptr))
        response = response->left_child_;

    return response;
}

template<typename T>
shared_ptr<typename SetSecond<T>::Node> SetSecond<T>::NextElement(shared_ptr<Node> target) const
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
shared_ptr<typename SetSecond<T>::Node> SetSecond<T>::PreviousElement(shared_ptr<Node> target) const
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
void SetSecond<T>::DeleteTree(shared_ptr<Node> &node)
{
    if (node == shared_ptr<Node>(nullptr))
        return;

    this->DeleteTree(node->left_child_);
    this->DeleteTree(node->right_child_);

    node = shared_ptr<Node>(nullptr);
}


template<class T>
class SetSecond<T>::Iterator : std::iterator<std::bidirectional_iterator_tag, T>
{
public:
    Iterator();

    Iterator(SetSecond *, shared_ptr<Node>);

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
    SetSecond *owner_;
};

template<typename T>
typename SetSecond<T>::Iterator SetSecond<T>::begin()
{
    return Iterator(this, this->GetMinimumValue(this->root_));
}

template<typename T>
typename SetSecond<T>::Iterator SetSecond<T>::end()
{
    return ++Iterator(this, this->GetMaximumValue(this->root_));
}

template<typename T>
void SetSecond<T>::UpdateListAdd(shared_ptr<Node> &where)
{
    if (where == this->GetMinimumValue(this->root_))
        this->links_to_nodes_.push_front(where);
    else if (where == this->GetMaximumValue(this->root_))
        this->links_to_nodes_.push_back(where);
    else
    {
        auto position = find(this->links_to_nodes_.begin(), this->links_to_nodes_.end(), this->NextElement(where));
        this->links_to_nodes_.insert(position, where);
    }
}

template<typename T>
void SetSecond<T>::UpdateListDelete(shared_ptr<Node> &where)
{
    auto position = find(this->links_to_nodes_.begin(), this->links_to_nodes_.end(), where);
    this->links_to_nodes_.erase(position);
}

template<class T>
SetSecond<T>::Iterator::Iterator(): object_(shared_ptr<Node>(nullptr)), owner_(shared_ptr<Node>(nullptr))
{}

template<class T>
SetSecond<T>::Iterator::Iterator(SetSecond *owner, shared_ptr<Node> link): object_(link), owner_(owner)
{}

template<class T>
T &SetSecond<T>::Iterator::operator*()
{
    return this->object_->value_;
}

template<class T>
typename SetSecond<T>::Node *SetSecond<T>::Iterator::operator->()
{
    return this->object_;
}

template<class T>
T SetSecond<T>::Iterator::operator*() const
{
    return *this->object_;
}

template<class T>
typename SetSecond<T>::Iterator &SetSecond<T>::Iterator::operator--()
{
    this->object_ = *(--find(this->owner_->links_to_nodes_.begin(), this->owner_->links_to_nodes_.end(),
                             this->object_));
    return *this;
}

template<class T>
bool SetSecond<T>::Iterator::operator==(const SetSecond<T>::Iterator &it) const
{
    return this->object_ == it.object_;
}

template<class T>
bool SetSecond<T>::Iterator::operator!=(const SetSecond<T>::Iterator &it) const
{
    return this->object_ != it.object_;
}

template<class T>
typename SetSecond<T>::Iterator &SetSecond<T>::Iterator::operator++()
{
    this->object_ = *(++find(this->owner_->links_to_nodes_.begin(), this->owner_->links_to_nodes_.end(),
                             this->object_));
    return *this;
}

template<class T>
const typename SetSecond<T>::Iterator SetSecond<T>::Iterator::operator++(int)
{
    Iterator temp(this->owner_, this->object_);
    ++(*this);
    return temp;
}

template<class T>
const typename SetSecond<T>::Iterator SetSecond<T>::Iterator::operator--(int)
{
    Iterator temp(this->owner_, this->object_);
    --(*this);
    return temp;
}