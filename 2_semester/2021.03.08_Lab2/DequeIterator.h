//
// Created by User on 13-Mar-21.
//

#ifndef INC_2021_03_08_LAB2_DEQUEITERATOR_H
#define INC_2021_03_08_LAB2_DEQUEITERATOR_H

#include "Deque.h"
#include <iterator>

using std::iterator;
using std::random_access_iterator_tag;

template<typename T>
class Deque<T>::Iterator : iterator<random_access_iterator_tag, T>
{
private:
    Deque<T> *owner_;
    size_t block_position_, index_position_;
    T* object_;



public:
    Iterator() : owner_(nullptr), object_(nullptr), block_position_(0), index_position_(0)
    {}

    Iterator(Deque<T> *owner, T *object, size_t &block_position, size_t &index_position) :
            owner_(owner), block_position_(block_position), index_position_(index_position)
    {
        this->object_ = &(this->owner_->links_to_blocks_[this->block_position_]->at(this->index_position_));
    }

    T *operator->();

    T &operator*();

    constexpr T operator*() const;

    Iterator &operator++();

    Iterator &operator--();

    constexpr bool operator==(const Iterator &) const noexcept;

    constexpr bool operator!=(const Iterator &) const noexcept;

    void UpdateBeginIterator();

    void UpdateEndIterator();
};

template<typename T>
T *Deque<T>::Iterator::operator->()
{
    return this->object_;
}

template<typename T>
T &Deque<T>::Iterator::operator*()
{
    return *(this->object_);
}

template<typename T>
constexpr T Deque<T>::Iterator::operator*() const
{
    return *(this->object_);
}

template<typename T>
typename Deque<T>::Iterator &Deque<T>::Iterator::operator++()
{
    this->block_position_ += (this->index_position_ + 1) / Deque::kBlockSize;
    this->index_position_ = (this->index_position_ + 1) % Deque::kBlockSize;
    this->object_ = &(this->owner_)->links_to_blocks_[block_position_]->at(index_position_);
    return *this;
}

template<typename T>
typename Deque<T>::Iterator &Deque<T>::Iterator::operator--()
{
    this->block_position_ -= (this->index_position_ == 0 ? 1 : 0);
    this->index_position_ = (this->index_position_ == 0 ? Deque::kBlockSize - 1 : this->index_position_ - 1);
    this->object_ = ((this->owner_)->links_to_blocks_[block_position_]->at(index_position_));
    return *this;
}

template<typename T>
constexpr bool Deque<T>::Iterator::operator==(const Deque<T>::Iterator &rhs) const noexcept
{
    return this->object_ == rhs.object_;
}

template<typename T>
constexpr bool Deque<T>::Iterator::operator!=(const Deque<T>::Iterator &rhs) const noexcept
{
    return this->object_ != rhs.object_;
}

template<typename T>
void Deque<T>::Iterator::UpdateBeginIterator()
{
    this->index_position_ = this->owner_->index_position__begin_;
    this->block_position_ = this->owner_->block_position__begin_;
    this->object_ = &(this->owner_->links_to_blocks_[this->block_position_]->at(this->index_position_));
}

template<typename T>
void Deque<T>::Iterator::UpdateEndIterator()
{
    this->index_position_ = this->owner_->index_position__end_;
    this->block_position_ = this->owner_->block_position__end_;
    this->object_ = &(this->owner_->links_to_blocks_[this->block_position_]->at(this->index_position_));
}

#endif //INC_2021_03_08_LAB2_DEQUEITERATOR_H
