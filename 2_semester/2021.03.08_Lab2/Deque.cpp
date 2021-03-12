//
// Created by User on 08-Mar-21.
//

#include "Deque.h"

template<typename T>
Deque<T>::Deque():size_(0), block_position__end_(0), index_position__end_(0),
                  block_position__begin_(0), index_position__begin_(0)
{
    for (auto counter = 0; counter < kStartAmountBlocks; ++counter)
        this->links_to_blocks_.push_back(make_shared<array<T, kBlockSize>>());
}

template<typename T>
Deque<T>::~Deque()
{
    /*for (auto &block : this->links_to_blocks_)
        delete block;*/
}

template<typename T>
void Deque<T>::PushBack(const T &new_element)
{
    if (this->size_ == 0)
    {
        this->links_to_blocks_[this->block_position__begin_]->at(this->index_position__end_) = new_element;
        ++this->size_;
        return;
    }

    if (this->index_position__end_ == kBlockSize - 1) // turn to other block
    {
        if (this->block_position__end_ == this->links_to_blocks_.size() - 1) // need to create new block
            this->links_to_blocks_.push_back(make_shared<array<T, kBlockSize>>());

        ++this->block_position__end_;
        this->index_position__end_ = -1;
    }
    this->links_to_blocks_[this->block_position__end_]->at(++this->index_position__end_) = new_element;
    ++this->size_;
}

template<typename T>
void Deque<T>::PushFront(const T &new_element)
{
    if (this->size_ == 0)
    {
        this->links_to_blocks_[this->block_position__begin_]->at(this->index_position__begin_) = new_element;
        ++this->size_;
        return;
    }

    if (this->index_position__begin_ == 0) // need to go on the left
    {
        if (this->block_position__begin_ == 0) // no blocks on the left
        {
            this->links_to_blocks_.insert(this->links_to_blocks_.cbegin(), make_shared<array<T, kBlockSize>>());
            ++this->block_position__end_;
        }
        else
        {
            --this->block_position__begin_;
        }
        this->index_position__begin_ = kBlockSize;
    }
    this->links_to_blocks_[this->block_position__begin_]->at(--this->index_position__begin_) = new_element;
    ++this->size_;
}

template<typename T>
void Deque<T>::PopBack()
{
    if (this->size_ > 0)
    {
        if (this->size_ == 1)
        {
            this->index_position__begin_ = this->index_position__end_ = this->block_position__end_ = this->block_position__begin_ = 0;
        }
        else
        {
            this->block_position__end_ -= (this->index_position__end_ == 0 ? 1 : 0);
            this->index_position__end_ = (this->index_position__end_ == 0 ? kBlockSize - 1 :
                                          this->index_position__end_ - 1);
        }
        --this->size_;
    }
}

template<typename T>
void Deque<T>::PopFront()
{
    if (this->size_ > 0)
    {
        if (this->size_ == 1)
        {
            this->index_position__begin_ = this->index_position__end_ = this->block_position__end_ = this->block_position__begin_ = 0;
        }
        else
        {
            this->block_position__begin_ += (this->index_position__begin_ == kBlockSize - 1 ? 1 : 0);
            this->index_position__begin_ = (this->index_position__begin_ == kBlockSize - 1 ? kBlockSize - 1 :
                                            this->index_position__begin_ + 1);
        }
        --this->size_;
    }
}

template<typename T>
constexpr size_t Deque<T>::Size() const
{
    return this->size_;
}

template<typename T>
ostream &operator<<(ostream &os, const Deque<T> &obj)
{
    auto current_block = obj.block_position__begin_;
    auto current_index_in_block = obj.index_position__begin_;

    os << "(" << obj.size_ << ") { ";
    bool is_done = (current_block == obj.block_position__end_ && current_index_in_block == obj.index_position__end_);
    while (!is_done)
    {
        is_done = (current_block == obj.block_position__end_ && current_index_in_block == obj.index_position__end_);
        os << obj.links_to_blocks_[current_block]->at(current_index_in_block) << " ";
        current_block += (current_index_in_block + 1 / obj.kBlockSize);
        current_index_in_block = (current_index_in_block + 1) % obj.kBlockSize;
    }
    os << " }\n";

    return os;
}


