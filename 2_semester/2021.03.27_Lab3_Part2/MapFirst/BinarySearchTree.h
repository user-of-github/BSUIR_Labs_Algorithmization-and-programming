#ifndef INC_2021_03_19_LAB3_BINARYSEARCHTREE_H
#define INC_2021_03_19_LAB3_BINARYSEARCHTREE_H

#include <memory>
#include <iostream>

using std::shared_ptr;
using std::size_t;
using std::ostream;
using std::pair;

template<typename T1, typename T2>
class BinaryTree
{
public:
    BinaryTree();

    BinaryTree(const BinaryTree<T1, T2> &);

    BinaryTree(BinaryTree<T1, T2> &&) noexcept;

    void Add(const pair<T1, T2> &);

    void Delete(const T1 &);

    void Clear();

    constexpr bool Has(const T1 &) const noexcept;

    constexpr size_t Size() const noexcept;

    constexpr bool Empty() const noexcept;

    constexpr T2 FindNext(const T1 &) const;

    constexpr T2 FindPrevious(const T1 &) const;

    template<typename T3, typename T4>
    friend ostream &operator<<(ostream &, const BinaryTree<T3, T4> &);

    T2 &operator[](const T1 &);

    BinaryTree<T1, T2> &operator=(BinaryTree<T1, T2> &&) noexcept;

    /* protected does not work :( */
    class Node;

    size_t size_;
    shared_ptr<Node> root_ = shared_ptr<Node>(nullptr);

    void RecursiveCopy(const shared_ptr<Node> &);

    void RecursivePrint(const shared_ptr<Node> &, ostream &) const;

    shared_ptr<Node> FindElement(const T1 &) const;

    void DeleteByPointer(shared_ptr<Node> &);

    shared_ptr<Node> GetMaximumValue(const shared_ptr<Node> &) const noexcept;

    shared_ptr<Node> GetMinimumValue(const shared_ptr<Node> &) const noexcept;

    shared_ptr<Node> NextElement(shared_ptr<Node>) const;

    shared_ptr<Node> PreviousElement(shared_ptr<Node>) const;

    void DeleteTree(shared_ptr<Node> &);
};

#endif //INC_2021_03_19_LAB3_BINARYSEARCHTREE_H
