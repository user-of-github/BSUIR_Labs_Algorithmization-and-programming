#include "HashTable.h"

template<typename KeyType, typename ValueType, typename HasherType>
HashTable<KeyType, ValueType, HasherType>::HashTable(const size_t &size): array_length_(size), number_of_elements_(0),
        hash_()
{
    this->data_ = new forward_list<pair<KeyType, ValueType>>[this->array_length_];
}

template<typename KeyType, typename ValueType, typename HasherType>
HashTable<KeyType, ValueType, HasherType>::HashTable(const HashTable &rhs): array_length_(rhs.array_length_),
        number_of_elements_(rhs.number_of_elements_), hash_(rhs.hash_)
{
    this->data_ = new forward_list<pair<KeyType, ValueType>>[this->array_length_];
    this->CopyTable(rhs.data_, this->data_, this->array_length_);
}

template<typename KeyType, typename ValueType, typename HasherType>
HashTable<KeyType, ValueType, HasherType>::HashTable(HashTable &&rhs) noexcept: array_length_(rhs.array_length_),
        number_of_elements_(rhs.number_of_elements_), data_(rhs.data_), hash_(rhs.hash_)
{
    rhs.array_length_ = rhs.number_of_elements_ = 0;
    rhs.data_ = nullptr;
}

template<typename KeyType, typename ValueType, typename HasherType>
HashTable<KeyType, ValueType, HasherType>::~HashTable()
{
    delete[] this->data_;
}

template<typename KeyType, typename ValueType, typename HasherType>
constexpr bool HashTable<KeyType, ValueType, HasherType>::Contains(const KeyType &key) const
{
    return !this->data_[static_cast<size_t>(this->hash_(key)) % this->array_length_].empty();
}

template<typename KeyType, typename ValueType, typename HasherType>
void HashTable<KeyType, ValueType, HasherType>::Insert(const KeyType &key, const ValueType &value)
{
    if ((double) ((double) this->number_of_elements_ / this->array_length_) > kRehashSize)
        this->ReHash();

    auto index = static_cast<size_t>(this->hash_(key)) % this->array_length_;
    for (auto &item : this->data_[index])
        if (item.first == key)
        {
            item.second = value;
            return;
        }
    this->data_[index].push_front(make_pair(key, value));
    ++this->number_of_elements_;
}

template<typename KeyType, typename ValueType, typename HasherType>
void HashTable<KeyType, ValueType, HasherType>::Erase(const KeyType &key)
{
    auto index = static_cast<size_t>(this->hash_(key)) % this->array_length_;
    if (this->data_[index].empty())
        return;

    if (this->data_[index].front().first == key)
        this->data_[index].pop_front();

    auto it = begin(this->data_[index]),
            current = begin(this->data_[index]);

    while (it != end(this->data_[index]))
    {
        current = it;
        ++it;
        if ((*it).first == key)
            break;
    }

    if (it == end(this->data_[index]))
        return;

    this->data_[index].erase_after(current);

    --this->number_of_elements_;
}

template<typename KeyType, typename ValueType, typename HasherType>
void HashTable<KeyType, ValueType, HasherType>::Clear()
{
    for (size_t counter = 0; counter < this->array_length_; ++counter)
        data_[counter].clear();

    this->number_of_elements_ = 0;
}

template<typename Key1, typename Value1, typename Hasher1>
ostream &operator<<(ostream &os, const HashTable<Key1, Value1, Hasher1> &obj)
{
    os << "HashTable(" << obj.number_of_elements_ << ')' << ": ";
    for (size_t counter = 0; counter < obj.array_length_; ++counter)
    {
        if (obj.data_[counter].empty())
            continue;

        os << "[" << counter << "]: ";
        for (const auto &item : obj.data_[counter])
            os << item.first << ':' << item.second << "  ";
        os << " | ";
    }
    os << '\n';

    return os;
}

template<typename KeyType, typename ValueType, typename HasherType>
ValueType &HashTable<KeyType, ValueType, HasherType>::operator[](const KeyType &key)
{
    auto index = static_cast<size_t>(this->hash_(key)) % this->array_length_;
    if (this->data_[index].empty())
        this->Insert(key, ValueType());

    for (auto &item : this->data_[index])
        if (item.first == key)
            return item.second;
}

template<typename KeyType, typename ValueType, typename HasherType>
constexpr ValueType HashTable<KeyType, ValueType, HasherType>::operator[](const KeyType &key) const
{
    auto index = static_cast<size_t>(this->hash_(key)) % this->array_length_;
    if (this->data_[index].empty())
        this->Insert(key, ValueType());

    for (const auto &item : this->data_[index])
        if (item.first == key)
            return item.second;
}

template<typename KeyType, typename ValueType, typename HasherType>
HashTable<KeyType, ValueType, HasherType> &HashTable<KeyType, ValueType, HasherType>::operator=(const HashTable &rhs)
{
    this->Clear();
    delete[] this->data_;
    this->array_length_ = rhs.array_length_;
    this->data_ = new forward_list<pair<KeyType, ValueType>>[this->array_length_];
    this->number_of_elements_ = rhs.number_of_elements_;
    CopyTable(rhs.data_, this->data_, this->array_length_);

    return *this;
}

template<typename KeyType, typename ValueType, typename HasherType>
HashTable<KeyType, ValueType, HasherType> &
HashTable<KeyType, ValueType, HasherType>::operator=(HashTable &&rhs) noexcept
{
    this->Clear();
    delete[] this->data_;

    this->array_length_ = rhs.array_length_;
    this->number_of_elements_ = rhs.number_of_elements_;
    this->data_ = rhs.data_;
    rhs.array_length_ = rhs.number_of_elements_ = 0;
    rhs.data_ = nullptr;

    return *this;
}

template<typename KeyType, typename ValueType, typename HasherType>
void HashTable<KeyType, ValueType, HasherType>::CopyTable(forward_list<pair<KeyType, ValueType>> *from,
                                                          forward_list<pair<KeyType, ValueType>> *to,
                                                          const size_t &size)
{
    for (size_t counter = 0; counter < size; ++counter)
        for (const auto &item : from[counter])
            to[counter].push_front(item);
}

template<typename KeyType, typename ValueType, typename HasherType>
void HashTable<KeyType, ValueType, HasherType>::ReHash()
{
    auto *copy = new forward_list<pair<KeyType, ValueType>>[this->array_length_];
    CopyTable(this->data_, copy, this->array_length_);
    auto copy_size = this->array_length_;

    delete[] this->data_;
    this->array_length_ *= 2;
    this->data_ = new forward_list<pair<KeyType, ValueType>>[this->array_length_];
    this->number_of_elements_ = 0;

    for (size_t counter = 0; counter < copy_size; ++counter)
        for (const auto &item : copy[counter])
            this->Insert(item.first, item.second);

    delete[] copy;
    std::cout << "Rehashed from " << copy_size << " to " << this->array_length_ << '\n';
}