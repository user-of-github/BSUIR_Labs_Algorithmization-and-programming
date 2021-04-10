#ifndef INC_2021_04_10_LAB4_HASHTABLE_H
#define INC_2021_04_10_LAB4_HASHTABLE_H

#include <iostream>
#include <forward_list>

using std::hash;
using std::pair;
using std::forward_list;
using std::ostream;
using std::make_pair;
using std::begin;
using std::end;

template<typename KeyType, typename ValueType, typename HasherType = hash<KeyType>>
class HashTable
{
public:
    explicit HashTable(const size_t & = 123);

    HashTable(const HashTable &);

    HashTable(HashTable &&) noexcept;

    ~HashTable();

    constexpr bool Contains(const KeyType &) const;

    void Insert(const KeyType &, const ValueType &);

    void Erase(const KeyType &);

    void Clear();

    template<typename Key1, typename Value1, typename Hasher1>
    friend ostream &operator<<(ostream &, const HashTable<Key1, Value1, Hasher1> &);

    ValueType &operator[](const KeyType &);

    constexpr ValueType operator[](const KeyType &) const;

    HashTable &operator=(const HashTable &);

    HashTable &operator=(HashTable &&) noexcept;

private:
    constexpr static const double kRehashSize = 0.75;

    HasherType hash_;
    size_t array_length_,
            number_of_elements_;
    forward_list<pair<KeyType, ValueType>> *data_;

    static void
    CopyTable(forward_list<pair<KeyType, ValueType>> *, forward_list<pair<KeyType, ValueType>> *, const size_t &);

    void ReHash();
};


#endif //INC_2021_04_10_LAB4_HASHTABLE_H
