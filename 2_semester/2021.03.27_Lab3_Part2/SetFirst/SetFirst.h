#ifndef SETFIRST_SETFIRST_H
#define SETFIRST_SETFIRST_H

#include <memory>
#include <iostream>

using std::shared_ptr;
using std::size_t;
using std::ostream;
using std::pair;
using std::bidirectional_iterator_tag;
using std::iterator;

template<typename T>
class SetFirst
{
public:
    SetFirst();

    SetFirst(const SetFirst<T> &);

    SetFirst(SetFirst<T> &&) noexcept;

    void Add(const T &);

    void Delete(const T &);

    void Clear();

    constexpr bool Has(const T &) const noexcept;

    constexpr size_t Size() const noexcept;

    constexpr bool Empty() const noexcept;

    constexpr T FindNext(const T &) const;

    constexpr T FindPrevious(const T &) const;

    template<typename T3>
    friend ostream &operator<<(ostream &, const SetFirst<T3> &);

    SetFirst<T> &operator=(SetFirst<T> &&) noexcept;

    class Iterator;

    Iterator begin();
    Iterator end();

private:
    class Node;

    size_t size_;
    shared_ptr<Node> root_ = shared_ptr<Node>(nullptr);

    void RecursiveCopy(const shared_ptr<Node> &);

    void RecursivePrint(const shared_ptr<Node> &, ostream &) const;

    shared_ptr<Node> FindElement(const T &) const;

    void DeleteByPointer(shared_ptr<Node> &);

    shared_ptr<Node> GetMaximumValue(const shared_ptr<Node> &) const noexcept;

    shared_ptr<Node> GetMinimumValue(const shared_ptr<Node> &) const noexcept;

    shared_ptr<Node> NextElement(shared_ptr<Node>) const;

    shared_ptr<Node> PreviousElement(shared_ptr<Node>) const;

    void DeleteTree(shared_ptr<Node> &);
};


#endif //SETFIRST_SETFIRST_H
