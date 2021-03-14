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
    this->UpdateIterators();
}

template<typename T>
Deque<T>::Deque(const initializer_list<T> &data):size_(0), block_position__end_(0), index_position__end_(0),
                                                 block_position__begin_(0), index_position__begin_(0)
{
    for (auto counter = 0; counter < kStartAmountBlocks; ++counter)
        this->links_to_blocks_.push_back(make_shared<array<T, kBlockSize>>());
    for (const auto &item : data)
        this->PushBack(item);
    this->UpdateIterators();
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
        {
            if (this->block_position__begin_ > 0) // there is free on the left
            {
                auto link_on_the_first = this->links_to_blocks_[0];
                for (auto counter = 0; counter < this->links_to_blocks_.size() - 1; ++counter)
                    this->links_to_blocks_[counter] = this->links_to_blocks_[counter + 1];
                this->links_to_blocks_[this->links_to_blocks_.size() - 1] = link_on_the_first;
                --this->block_position__begin_;
            }
            else
            {
                this->links_to_blocks_.push_back(make_shared<array<T, kBlockSize>>());
            }
        }

        ++this->block_position__end_;
        this->index_position__end_ = -1;
    }
    this->links_to_blocks_[this->block_position__end_]->at(++this->index_position__end_) = new_element;
    ++this->size_;
    this->UpdateIterators();
}

template<typename T>
void Deque<T>::PushFront(const T &new_element)
{
    if (this->size_ == 0)
    {
        this->block_position__begin_ = this->block_position__end_ = this->index_position__begin_ = this->index_position__end_ = 0;
        this->links_to_blocks_[this->block_position__begin_]->at(this->index_position__begin_) = new_element;
        ++this->size_;
        return;
    }

    if (this->index_position__begin_ == 0) // need to go on the left
    {
        if (this->block_position__begin_ == 0) // no blocks on the left
        {
            if (this->block_position__end_ < this->links_to_blocks_.size() - 1) // maybe some free on the right ?
            {
                shared_ptr<array<T, kBlockSize>> link_on_the_last = this->links_to_blocks_[
                        this->links_to_blocks_.size() - 1];
                for (auto counter = links_to_blocks_.size() - 1; counter > 0; --counter)
                    this->links_to_blocks_[counter] = this->links_to_blocks_[counter - 1];
                this->links_to_blocks_[0] = link_on_the_last;
            }
            else
            {
                this->links_to_blocks_.insert(this->links_to_blocks_.cbegin(), make_shared<array<T, kBlockSize>>());
            }
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
    this->UpdateIterators();
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
        this->UpdateIterators();
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
            this->index_position__begin_ = (this->index_position__begin_ == kBlockSize - 1 ? 0 :
                                            this->index_position__begin_ + 1);
        }
        --this->size_;
        this->UpdateIterators();
    }
}

template<typename T>
void Deque<T>::Clear()
{
    this->size_ = 0;
    this->block_position__end_ = this->index_position__end_ = this->block_position__begin_ = this->index_position__begin_ = 0;
    while (this->links_to_blocks_.size() != kStartAmountBlocks)
        this->links_to_blocks_.pop_back();

    this->UpdateIterators();
}


template<typename T>
constexpr size_t Deque<T>::Size() const noexcept
{
    return this->size_;
}

template<typename T>
constexpr bool Deque<T>::Empty() const noexcept
{
    return this->size_ != 0;
}

template<typename T>
ostream &operator<<(ostream &os, const Deque<T> &obj)
{
    auto current_block = obj.block_position__begin_,
            current_index_in_block = obj.index_position__begin_;
    os << "[INFO]: Totally array<T, blockSize> - blocks: " << obj.links_to_blocks_.size() << ". Used blocks: ["
       << obj.block_position__begin_ << "..." << obj.block_position__end_ << "] Index_of_first: "
       << obj.index_position__begin_ << " \n";
    os << "(" << obj.size_ << ") { ";
    bool is_done = (current_block == obj.block_position__end_ && current_index_in_block == obj.index_position__end_);
    while (!is_done)
    {
        is_done = (current_block == obj.block_position__end_ && current_index_in_block == obj.index_position__end_);
        os << obj.links_to_blocks_[current_block]->at(current_index_in_block) << " ";
        if (current_index_in_block == obj.kBlockSize - 1) os << " | ";
        current_block += ((current_index_in_block + 1) / obj.kBlockSize);
        current_index_in_block = (current_index_in_block + 1) % obj.kBlockSize;
    }
    os << " }\n\n";

    return os;
}

template<typename T>
T &Deque<T>::operator[](const size_t &index)
{
    if (index < this->size_)
    {
        auto index_in_block = static_cast<int>(
                (kBlockSize * this->block_position__begin_ + this->index_position__begin_ + index) % kBlockSize);
        auto block_number = static_cast<int>(
                (kBlockSize * this->block_position__begin_ + this->index_position__begin_ + index) / kBlockSize);

        return this->links_to_blocks_[block_number]->at(index_in_block);
    }
}

template<typename T>
typename Deque<T>::Iterator Deque<T>::begin()
{
    auto new_iterator = Iterator(this,
                                 &(this->links_to_blocks_[this->block_position__begin_]->at(index_position__begin_)),
                                 this->block_position__begin_, this->index_position__begin_);
    created_begin_iterators_.insert(&new_iterator);
    return new_iterator;
}

template<typename T>
typename Deque<T>::Iterator Deque<T>::end()
{
    auto new_iterator = ++Iterator(this,
                                   &(this->links_to_blocks_[this->block_position__end_]->at(index_position__end_)),
                                   this->block_position__end_, this->index_position__end_);
    created_end_iterators_.insert(&new_iterator);
    return new_iterator;
}

template<typename T>
void Deque<T>::UpdateIterators()
{
    for (auto &item : this->created_begin_iterators_)
        item->UpdateBeginIterator();

    for (auto &item : this->created_end_iterators_)
        item->UpdateEndIterator();
}





