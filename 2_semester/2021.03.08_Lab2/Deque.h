//
// Created by User on 08-Mar-21.
//

#ifndef INC_2021_03_08_LAB2_DEQUE_H
#define INC_2021_03_08_LAB2_DEQUE_H

#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <set>

using std::cout;
using std::vector;
using std::array;
using std::size_t;
using std::ostream;
using std::shared_ptr;
using std::make_shared;

template<typename T>
class Deque
{
public:
    Deque();

    void PushBack(const T &);

    void PushFront(const T &);

    void PopBack();

    void PopFront();

    void Clear();

    constexpr size_t Size() const noexcept;

    constexpr bool Empty() const noexcept;

    template<typename T1>
    friend ostream &operator<<(ostream &, const Deque<T1> &);

    T &operator[](const size_t &);

    class Iterator;

    Iterator begin();

    Iterator end();

protected:
    static const size_t kBlockSize = 3;
    static const size_t kStartAmountBlocks = 2;

    vector<shared_ptr<array<T, kBlockSize>>> links_to_blocks_;

    size_t block_position__end_, index_position__end_,
            block_position__begin_, index_position__begin_;

    size_t size_;
};


#endif //INC_2021_03_08_LAB2_DEQUE_H
