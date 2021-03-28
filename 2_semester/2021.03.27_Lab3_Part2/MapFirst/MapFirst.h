#ifndef INC_2021_03_27_LAB3_PART2__MAP_H_
#define INC_2021_03_27_LAB3_PART2__MAP_H_

#include <memory>

#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"

using std::bidirectional_iterator_tag;
using std::iterator;
using std::shared_ptr;

template<typename T1, typename T2>
class MapFirst : public BinaryTree<T1, T2>
{
public:
    class Iterator;

    constexpr Iterator begin();

    constexpr Iterator end();
};

template<typename T1, typename T2>
class MapFirst<T1, T2>::Iterator : iterator<bidirectional_iterator_tag, T1>
{
public:
    Iterator();

    Iterator(BinaryTree<T1, T2> *, const shared_ptr<typename BinaryTree<T1, T2>::Node>);

    shared_ptr<typename BinaryTree<T1, T2>::Node> operator->();

    T2 &operator*();

    constexpr T2 operator*() const;

    Iterator &operator++();

    const Iterator operator++(int);

    Iterator &operator--();

    const Iterator operator--(int);

    bool operator==(const Iterator &) const;

    bool operator!=(const Iterator &) const;

    template<typename T3, typename T4>
    friend ostream &operator<<(ostream &, const MapFirst<T3, T4> &);


protected:
    shared_ptr<typename BinaryTree<T1, T2>::Node> object_;
    BinaryTree<T1, T2> *owner_;
};


#endif //INC_2021_03_27_LAB3_PART2__MAP_H_
