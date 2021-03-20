//
// Created by User on 19-Mar-21.
//

#include "BinarySearchTree.h"

template<typename T1, typename T2>
Map<T1, T2>::Node::Node(const pair<T1, T2> &value, shared_ptr<Node> parent)
        :value_(value), parent_(parent), left_child_(nullptr), right_child_(nullptr)
{}


template<typename T1, typename T2>
Map<T1, T2>::Map():size_(0), root_(shared_ptr<Node>(nullptr))
{}

template<typename T1, typename T2>
constexpr size_t Map<T1, T2>::Size() const noexcept
{
    return this->size_;
}

template<typename T1, typename T2>
constexpr bool Map<T1, T2>::Empty() const noexcept
{
    return this->size_ == 0;
}

template<typename T1, typename T2>
void Map<T1, T2>::Add(const pair<T1, T2> &value)
{
    auto *new_element = new Node(value, shared_ptr<Node>(nullptr));
    if (this->size_ != 0)
    {
        auto element = this->root_, parent = this->root_;

        while (element != shared_ptr<Node>(nullptr))
        {
            parent = element;
            element = value.first <= element->value_.first ? element->left_child_ : element->right_child_;
        }

        new_element->parent_ = parent;
        value.first <= parent->value_.first ? (parent->left_child_ = shared_ptr<Node>(new_element))
                                            : (parent->right_child_ = shared_ptr<Node>(new_element));
    }
    else
    {
        this->root_ = shared_ptr<Node>(new_element);
    }

    ++this->size_;
}


template<typename T1, typename T2>
ostream &operator<<(ostream &os, const Map<T1, T2> &object)
{
    os << "Tree(" << object.size_ << "): {";
    object.RecursivePrint(object.root_, os);
    os << "}\n";

    return os;
}

template<typename T1, typename T2>
shared_ptr<typename Map<T1, T2>::Node> Map<T1, T2>::FindElement(const T1 &value) const
{
    auto search_element = this->root_;

    while (search_element != shared_ptr<Node>(nullptr) || (search_element->value_).first != value)
        search_element = value <= search_element->value_.first ? search_element->left_child_
                                                               : search_element->right_child_;

    return search_element;
}

template<typename T1, typename T2>
constexpr bool Map<T1, T2>::Has(const T1 &value) const noexcept
{
    return this->FindElement(value) != shared_ptr<Node>(nullptr);
}

template<typename T1, typename T2>
T2 &Map<T1, T2>::operator[](const T1 &value)
{
    return ((this->FindElement(value))->value_).second;
}

template<typename T1, typename T2>
void Map<T1, T2>::RecursivePrint(const shared_ptr<Node> &element, ostream &os) const
{
    if (element != shared_ptr<Node>(nullptr))
    {
        RecursivePrint(element->left_child_, os);
        os << " " << (element->value_).first << ":" << (element->value_).second << " ";
        RecursivePrint(element->right_child_, os);
    }
}




