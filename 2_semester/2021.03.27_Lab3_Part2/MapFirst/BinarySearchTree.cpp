#include "BinarySearchTree.h"


template<typename T1, typename T2>
BinaryTree<T1, T2>::BinaryTree():size_(0), root_(shared_ptr<Node>(nullptr))
{}

template<typename T1, typename T2>
BinaryTree<T1, T2>::BinaryTree(const BinaryTree<T1, T2> &rhs):size_(0), root_(shared_ptr<Node>(nullptr))
{
    this->RecursiveCopy(rhs.root_);
}

template<typename T1, typename T2>
BinaryTree<T1, T2>::BinaryTree(BinaryTree<T1, T2> &&rhs) noexcept: size_(0), root_(shared_ptr<Node>(nullptr))
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

template<typename T1, typename T2>
void BinaryTree<T1, T2>::Add(const pair<T1, T2> &new_item)
{
    auto try_has = this->FindElement(new_item.first);
    if (try_has != shared_ptr<Node>(nullptr))
    {
        try_has->value_.second = new_item.second;
        return;
    }

    auto *new_element = new Node(new_item, shared_ptr<Node>(nullptr));
    if (this->size_ != 0)
    {
        auto element = this->root_, parent = this->root_;

        while (element != shared_ptr<Node>(nullptr))
        {
            parent = element;
            element = new_item.first <= element->value_.first ? element->left_child_ : element->right_child_;
        }

        new_element->parent_ = parent;
        new_item.first <= parent->value_.first ? (parent->left_child_ = shared_ptr<Node>(new_element))
                                               : (parent->right_child_ = shared_ptr<Node>(new_element));
    } else
    {
        this->root_ = shared_ptr<Node>(new_element);
    }

    ++this->size_;
}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::Delete(const T1 &key)
{
    auto search_element = this->FindElement(key);
    if (search_element != shared_ptr<Node>(nullptr) && this->size_ > 0)
    {
        this->DeleteByPointer(search_element);
        --this->size_;
    }

    if (this->size_ == 0)
        this->root_ = shared_ptr<Node>(nullptr);
}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::Clear()
{
    if (this->root_ != shared_ptr<Node>(nullptr) && this->size_ != 0)
    {
        this->DeleteTree(this->root_);
        this->root_ = shared_ptr<Node>(nullptr);
    }
    this->size_ = 0;
}

template<typename T1, typename T2>
constexpr bool BinaryTree<T1, T2>::Has(const T1 &key) const noexcept
{
    return this->FindElement(key) != shared_ptr<Node>(nullptr);
}

template<typename T1, typename T2>
constexpr size_t BinaryTree<T1, T2>::Size() const noexcept
{
    return this->size_;
}

template<typename T1, typename T2>
constexpr bool BinaryTree<T1, T2>::Empty() const noexcept
{
    return this->size_ == 0;
}

template<typename T1, typename T2>
constexpr T2 BinaryTree<T1, T2>::FindNext(const T1 &key) const
{
    return ((this->NextElement(this->FindElement(key)))->value_).second;
}

template<typename T1, typename T2>
constexpr T2 BinaryTree<T1, T2>::FindPrevious(const T1 &key) const
{
    return ((this->PreviousElement(this->FindElement(key)))->value_).second;
}

template<typename T1, typename T2>
ostream &operator<<(ostream &os, const BinaryTree<T1, T2> &element)
{
    os << "BinaryTree(" << element.size_ << "): {";
    element.RecursivePrint(element.root_, os);
    os << "}\n";

    return os;
}

template<typename T1, typename T2>
T2 &BinaryTree<T1, T2>::operator[](const T1 &value)
{
    return ((this->FindElement(value))->value_).second;
}

template<typename T1, typename T2>
BinaryTree<T1, T2> &BinaryTree<T1, T2>::operator=(BinaryTree<T1, T2> &&rhs) noexcept
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


template<typename T1, typename T2>
class BinaryTree<T1, T2>::Node
{
public:
    pair<T1, T2> value_;
    shared_ptr<Node> left_child_,
            right_child_,
            parent_;

    Node(const pair<T1, T2> &, shared_ptr<Node>);
};

template<typename T1, typename T2>
BinaryTree<T1, T2>::Node::Node(const pair<T1, T2> &value, shared_ptr<Node> parent)
        :value_(value), parent_(parent), left_child_(nullptr), right_child_(nullptr)
{}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::RecursiveCopy(const shared_ptr<Node> &rhs)
{
    if (rhs == shared_ptr<Node>(nullptr))
        return;

    this->Add(rhs->value_);
    this->RecursiveCopy(rhs->left_child_);
    this->RecursiveCopy(rhs->right_child_);
}

template<typename T1, typename T2>
void BinaryTree<T1, T2>::RecursivePrint(const shared_ptr<Node> &element, ostream &os) const
{
    if (element != shared_ptr<Node>(nullptr))
    {
        RecursivePrint(element->left_child_, os);
        os << " " << (element->value_).first << ":" << (element->value_).second << " ";
        RecursivePrint(element->right_child_, os);
    }
}

template<typename T1, typename T2>
shared_ptr<typename BinaryTree<T1, T2>::Node> BinaryTree<T1, T2>::FindElement(const T1 &key) const
{
    auto search_element = this->root_;

    while (search_element != shared_ptr<Node>(nullptr) && (search_element->value_).first != key)
        search_element = key <= search_element->value_.first ? search_element->left_child_
                                                             : search_element->right_child_;

    return search_element;
}


template<typename T1, typename T2>
void BinaryTree<T1, T2>::DeleteByPointer(shared_ptr<Node> &target)
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

template<typename T1, typename T2>
shared_ptr<typename BinaryTree<T1, T2>::Node>
BinaryTree<T1, T2>::GetMaximumValue(const shared_ptr<Node> &start) const noexcept
{
    auto response = start;

    while (response->right_child_ != shared_ptr<Node>(nullptr))
        response = response->right_child_;

    return response;
}

template<typename T1, typename T2>
shared_ptr<typename BinaryTree<T1, T2>::Node>
BinaryTree<T1, T2>::GetMinimumValue(const shared_ptr<Node> &start) const noexcept
{
    auto response = start;

    while (response->left_child_ != shared_ptr<Node>(nullptr))
        response = response->left_child_;

    return response;
}

template<typename T1, typename T2>
shared_ptr<typename BinaryTree<T1, T2>::Node> BinaryTree<T1, T2>::NextElement(shared_ptr<Node> target) const
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

template<typename T1, typename T2>
shared_ptr<typename BinaryTree<T1, T2>::Node> BinaryTree<T1, T2>::PreviousElement(shared_ptr<Node> target) const
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

template<typename T1, typename T2>
void BinaryTree<T1, T2>::DeleteTree(shared_ptr<Node> &node)
{
    if (node == shared_ptr<Node>(nullptr))
        return;

    this->DeleteTree(node->left_child_);
    this->DeleteTree(node->right_child_);

    node = shared_ptr<Node>(nullptr);
}