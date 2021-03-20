
#ifndef INC_2021_03_19_LAB3_BINARYSEARCHTREE_H
#define INC_2021_03_19_LAB3_BINARYSEARCHTREE_H

#include <memory>
#include <iostream>

using std::shared_ptr;
using std::size_t;
using std::make_shared;
using std::ostream;
using std::pair;

template<typename T1, typename T2>
class Map
{
public:
    Map();

    void Add(const pair<T1, T2> &);

    constexpr bool Has(const T1 &) const noexcept;

    constexpr size_t Size() const noexcept;

    constexpr bool Empty() const noexcept;

    template<typename T3, typename T4>
    friend ostream &operator<<(ostream &, const Map<T3, T4> &);

    T2 &operator[](const T1 &);

private:
    class Node;

    size_t size_;
    shared_ptr<Node> root_ = nullptr;

    void RecursivePrint(const shared_ptr<Node> &, ostream &) const;

    shared_ptr<Node> FindElement(const T1 &) const;
};

template<typename T1, typename T2>
class Map<T1, T2>::Node
{
public:
    pair<T1, T2> value_;
    shared_ptr<Node> left_child_,
            right_child_,
            parent_;

    Node(const pair<T1, T2> &, shared_ptr<Node>);
};


#endif //INC_2021_03_19_LAB3_BINARYSEARCHTREE_H
