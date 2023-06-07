//
// Created by hlx on 2023-04-23.
//

#ifndef MYSTL_ITERATOR_H
#define MYSTL_ITERATOR_H

#include "type_traits.h"

namespace mystl {

    // 迭代器类型
    struct input_iterator_tag {
    };

    struct output_iterator_tag {
    };

    struct forward_iterator_tag : public input_iterator_tag {
    };

    struct bidirectional_iterator_tag : public forward_iterator_tag {
    };

    struct random_access_iterator_tag : public bidirectional_iterator_tag {
    };

    // 迭代器原型
    template<typename Category, typename T, typename Distance = std::ptrdiff_t,
            typename Pointer = T *, typename Reference = T &>
    struct iterator {
        using iterator_category = Category;;
        using value_type = T;
        using pointer = Pointer;
        using reference = Reference;
        using difference_type = Distance;
    };

    template<typename Iterator,
            bool = std::__has_iterator_category<Iterator>::value>
    struct _iterator_traits {
    };

    template<typename Iterator>
    struct _iterator_traits<Iterator, true> {
        using iterator_category = typename Iterator::iterator_category;
        using value_type = typename Iterator::value_type;
        using difference_type = typename Iterator::difference_type;
        using pointer = typename Iterator::pointer;
        using reference = typename Iterator::reference;
    };

    template<typename Iterator>
    struct iterator_traits
            : public _iterator_traits<Iterator> {
    };

    // 指针特化
    template<typename T>
    struct iterator_traits<T *> {
        using iterator_category = random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;
    };

    // const 指针特化
    template<typename T>
    struct iterator_traits<const T *> {
        using iterator_category = random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T *;
        using reference = const T &;
    };

    // 是否输入迭代器
    template<typename InputIterator>
    using RequireInputIter = enable_if_t<is_convertible<typename
    iterator_traits<InputIterator>::iterator_category, input_iterator_tag>::value>;

    // 通用迭代器
    template<typename Iterator, typename Container>
    class normal_iterator {
    protected:
        // 可能是迭代器或者指针类型
        Iterator _data;
        using traits_type = iterator_traits<Iterator>;

    public:
        using iterator_type = Iterator;
        using iterator_category = typename traits_type::iterator_category;
        using value_type = typename traits_type::value_type;
        using difference_type = typename traits_type::difference_type;
        using reference = typename traits_type::reference;
        using pointer = typename traits_type::pointer;

        normal_iterator() : _data(nullptr) {}

        explicit normal_iterator(pointer data) : _data(data) {}

        normal_iterator(const normal_iterator &other) : _data(other._data) {}

        pointer base() const noexcept {
            return _data;
        }

        normal_iterator &operator++() noexcept {
            ++_data;
            return *this;
        }

        normal_iterator operator++(int) noexcept {
            return normal_iterator(_data++);
        }

        normal_iterator &operator--() noexcept {
            --_data;
            return *this;
        }

        normal_iterator operator--(int) noexcept {
            return normal_iterator(_data--);
        }

        normal_iterator operator+(difference_type n) const noexcept {
            return normal_iterator(_data + n);
        }

        normal_iterator &operator+=(difference_type n) noexcept {
            _data += n;
            return *this;
        }

        normal_iterator operator-(difference_type n) const noexcept {
            return normal_iterator(_data - n);
        }

        normal_iterator &operator-=(difference_type n) noexcept {
            _data -= n;
            return *this;
        }

        reference operator*() const noexcept {
            return *_data;
        }

        pointer operator->() const noexcept {
            return _data;
        }

        reference operator[](difference_type n) const noexcept {
            return _data[n];
        }

        inline friend
        difference_type operator-(const normal_iterator &lhs, const normal_iterator &rhs) noexcept {
            return lhs.base() - rhs.base();
        }

        inline friend
        bool operator==(const normal_iterator &lhs, const normal_iterator &rhs) noexcept {
            return lhs.base() == rhs.base();
        }

        inline friend
        bool operator!=(const normal_iterator &lhs, const normal_iterator &rhs) noexcept {
            return lhs.base() != rhs.base();
        }

        inline friend
        bool operator>(const normal_iterator &lhs, const normal_iterator &rhs) noexcept {
            return lhs.base() > rhs.base();
        }

        inline friend
        bool operator>=(const normal_iterator &lhs, const normal_iterator &rhs) noexcept {
            return (lhs.base() >= rhs.base()) || (lhs.base() == rhs.base());
        }

        inline friend
        bool operator<(const normal_iterator &lhs, const normal_iterator &rhs) noexcept {
            return lhs.base() < rhs.base();
        }

        inline friend
        bool operator<=(const normal_iterator &lhs, const normal_iterator &rhs) noexcept {
            return (lhs.base() <= rhs.base()) || (lhs.base() == rhs.base());
        }

        ~normal_iterator() = default;
    };


    template<typename Iterator>
    class reverse_iterator : public iterator<
            typename iterator_traits<Iterator>::iterator_category,
            typename iterator_traits<Iterator>::value_type,
            typename iterator_traits<Iterator>::difference_type,
            typename iterator_traits<Iterator>::pointer,
            typename iterator_traits<Iterator>::reference> {

    protected:
        Iterator current;

        using traits_type = iterator_traits<Iterator>;

    public:
        using iterator_type = Iterator;
        using difference_type = typename traits_type::difference_type;
        using pointer = typename traits_type::pointer;
        using reference = typename traits_type::reference;

        // 默认构造
        reverse_iterator() : current() {}

        explicit reverse_iterator(iterator_type x) : current(x) {}

        reverse_iterator(const reverse_iterator &x) : current(x.current) {}

        template<typename Iter>
        explicit reverse_iterator(const reverse_iterator<Iter> &x)
                : current(x.base()) {}

        // 默认析构
        ~reverse_iterator() = default;

        iterator_type base() const {
            return current;
        }

        reference operator*() const {
            Iterator tmp = current;
            return *--tmp;
        }

        pointer operator->() const {
            return &(operator*());
        }

        reverse_iterator &operator++() {
            --current;
            return *this;
        }


        reverse_iterator operator++(int) {
            reverse_iterator tmp = *this;
            --current;
            return tmp;
        }


        reverse_iterator &operator--() {
            ++current;
            return *this;
        }


        reverse_iterator operator--(int) {
            reverse_iterator tmp = *this;
            ++current;
            return tmp;
        }


        reverse_iterator operator+(difference_type n) const {
            return reverse_iterator(current - n);
        }


        reverse_iterator &operator+=(difference_type n) {
            current -= n;
            return *this;
        }

        reverse_iterator operator-(difference_type n) const {
            return reverse_iterator(current + n);
        }


        reverse_iterator &operator-=(difference_type n) {
            current += n;
            return *this;
        }

        reference operator[](difference_type n) const {
            return *(*this + n);
        }

        inline friend
        difference_type operator-(const reverse_iterator &lhs, const reverse_iterator &rhs) noexcept {
            return lhs.base() - rhs.base();
        }

        inline friend
        bool operator==(const reverse_iterator &lhs, const reverse_iterator &rhs) noexcept {
            return lhs.base() == rhs.base();
        }

        inline friend
        bool operator!=(const reverse_iterator &lhs, const reverse_iterator &rhs) noexcept {
            return lhs.base() != rhs.base();
        }

        inline friend
        bool operator>(const reverse_iterator &lhs, const reverse_iterator &rhs) noexcept {
            return lhs.base() > rhs.base();
        }

        inline friend
        bool operator>=(const reverse_iterator &lhs, const reverse_iterator &rhs) noexcept {
            return (lhs.base() >= rhs.base()) || (lhs.base() == rhs.base());
        }

        inline friend
        bool operator<(const reverse_iterator &lhs, const reverse_iterator &rhs) noexcept {
            return lhs.base() < rhs.base();
        }

        inline friend
        bool operator<=(const reverse_iterator &lhs, const reverse_iterator &rhs) noexcept {
            return (lhs.base() <= rhs.base()) || (lhs.base() == rhs.base());
        }
    };


    template<typename Container>
    inline auto
    begin(Container &container) -> decltype(container.begin()) {
        return container.begin();
    }

    template<typename Container>
    inline auto
    begin(const Container &container) -> decltype(container.begin()) {
        return container.begin();
    }


    template<typename Container>
    inline auto end(Container &container) -> decltype(container.end()) {
        return container.end();
    }


    template<typename Container>
    inline auto end(const Container &container) -> decltype(container.end()) {
        return container.end();
    }


    template<typename T, size_t N>
    inline T *begin(T (&array)[N]) {
        return array;
    }

    template<typename T, size_t N>
    inline T *end(T (&array)[N]) {
        return array + N;
    }

}

#endif //MYSTL_ITERATOR_H
