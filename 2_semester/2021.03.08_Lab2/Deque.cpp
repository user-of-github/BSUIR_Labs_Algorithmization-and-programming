//
// Created by User on 08-Mar-21.
//

#include "Deque.h"

template<typename T>
Deque<T>::Deque():size_(0), number_of_allocated_blocks_(0), block_position__end_(0), index_position__end_(0),
                  block_position__begin_(0), index_position__begin_(0)
{
    this->number_of_allocated_blocks_ = kStartAmountBlocks;
    for (auto counter = 0; counter < kStartAmountBlocks; ++counter)
        this->links_to_blocks_.push_back(new array<T, kBlockSize>);

    this->begin_ = this->end_ = &((*this->links_to_blocks_[0])[0]);
}

template<typename T>
Deque<T>::~Deque()
{
    for (auto &block : this->links_to_blocks_)
        delete block;
}

template<typename T>
void Deque<T>::PushBack(const T &new_element)
{
    //cout << "Try to add " << new_element << " to " << block_position__end_ << " " << index_position__end_ << "\n";
    if (this->index_position__end_ == kBlockSize) // turn to other block
    {
        if (this->block_position__end_ == this->number_of_allocated_blocks_ - 1) // need to create new block
        {
            this->links_to_blocks_.push_back(new array<T, kBlockSize>);
            ++this->number_of_allocated_blocks_;
        }
        ++this->block_position__end_;
        this->index_position__end_ = 0;
    }

    (*this->links_to_blocks_[this->block_position__end_])[this->index_position__end_++] = new_element;
    ++this->size_;

    //cout << "Added " << new_element << " to " << block_position__end_ << " " << index_position__end_ - 1 << "\n";
}

template<typename T>
void Deque<T>::PushFront(const T &new_element)
{
    if (this->index_position__begin_ == 0) // need to go to previous block (to the left block)
    {
        if (this->block_position__begin_ == 0) // it is already the first block => we need one more on the left
        {
            if (this->block_position__end_ == this->number_of_allocated_blocks_ - 1) // if there's no empty on the right
            {
                ++this->number_of_allocated_blocks_;
                this->links_to_blocks_.push_back(new array<T, kBlockSize>);
            }

            auto *pointer_on_empty_block = this->links_to_blocks_[this->block_position__end_ + 1];
            for (auto counter = 1; counter <= this->block_position__end_ + 1; ++counter)
                this->links_to_blocks_[counter] = this->links_to_blocks_[counter - 1];
            this->links_to_blocks_[0] = pointer_on_empty_block;
        }
        else
        {
            --this->block_position__begin_;
        }

        this->index_position__begin_ = kBlockSize - 1;
    }
    else
    {
        --this->index_position__begin_;
    }

    (*(this->links_to_blocks_[this->block_position__begin_]))[this->index_position__begin_] = new_element;
    ++this->size_;

    ++this->block_position__end_;
}

template<typename T>
void Deque<T>::PopBack(const T &)
{

}

template<typename T>
void Deque<T>::PopFront(const T &)
{

}

template<typename T>
size_t Deque<T>::Size() const
{
    return this->size_;
}

template<typename T>
void Deque<T>::MoveToNextElement(size_t &block, size_t &index)
{
    if (block < this->block_position__end_)
    {
        if (index < kBlockSize - 1)
            ++index;
        else
        {
            index = 0;
            ++block;
        }
    }
    else if (block == this->block_position__end_)
    {
        if (index < this->index_position__end_)
            ++index;
    }
}

template<typename T>
void Deque<T>::Print()
{
    //cout << "Start position: " << this->block_position__begin_ << " ; " << this->index_position__begin_ << "\n";
    auto current_block = this->block_position__begin_;
    auto current_index_in_block = this->index_position__begin_;

    cout << "(" << this->size_ << ") {";
    for (auto counter = 0; counter < this->size_; ++counter)
    {
        cout << (*(this->links_to_blocks_[current_block]))[current_index_in_block] << " ";
        this->MoveToNextElement(current_block, current_index_in_block);
    }
    cout << "}";

}



