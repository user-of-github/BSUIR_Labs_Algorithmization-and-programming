//
// Created by User on 08-Mar-21.
//

#ifndef INC_2021_03_08_LAB2_DEQUE_H
#define INC_2021_03_08_LAB2_DEQUE_H

#include <iostream>
#include <vector>
#include <array>
#include <iterator>

using std::cout;
using std::vector;
using std::array;
using std::size_t;
using std::ostream;

template<typename T>
class Deque
{
public:
    Deque();

    ~Deque();

    void PushBack(const T &);

    void PushFront(const T &);

    void PopBack(const T &);

    void PopFront(const T &);

    size_t Size() const;

    void Print();

private:
    static const size_t kBlockSize = 2;
    static const size_t kStartAmountBlocks = 2;
    vector<array<T, kBlockSize> *> links_to_blocks_;
    size_t size_, number_of_allocated_blocks_;
    size_t block_position__end_, index_position__end_;
    size_t block_position__begin_, index_position__begin_;

    T *begin_, *end_;

    void MoveToNextElement(size_t &, size_t &);
};


#endif //INC_2021_03_08_LAB2_DEQUE_H
