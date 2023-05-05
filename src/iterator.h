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
        typedef Category iterator_category;
        typedef T value_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Distance difference_type;
    };

    template<typename Iterator,
            bool = std::__has_iterator_category<Iterator>::value>
    struct _iterator_traits {
    };

    template<typename Iterator>
    struct _iterator_traits<Iterator, true> {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
    };

    template<typename Iterator>
    struct iterator_traits
            : public _iterator_traits<Iterator> {
    };

    // 指针特化
    template<typename T>
    struct iterator_traits<T *> {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
    };

    // const 指针特化
    template<typename T>
    struct iterator_traits<const T *> {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef const T *pointer;
        typedef const T &reference;
    };

    // 是否输入迭代器
    template<typename InputIterator>
    using RequireInputIter = typename
    enable_if<is_convertible<typename
    iterator_traits<InputIterator>::iterator_category,
            input_iterator_tag>::value>::type;

    // 通用迭代器
    template<typename Iterator, typename Container>
    class normal_iterator {
    protected:
        // 可能是迭代器或者指针类型
        Iterator _data;
        typedef iterator_traits<Iterator> traits_type;

    public:
        typedef Iterator iterator_type;
        typedef typename traits_type::iterator_category iterator_category;
        typedef typename traits_type::value_type value_type;
        typedef typename traits_type::difference_type difference_type;
        typedef typename traits_type::reference reference;
        typedef typename traits_type::pointer pointer;

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

        typedef iterator_traits<Iterator> traits_type;

    public:
        typedef Iterator iterator_type;
        typedef typename traits_type::difference_type difference_type;
        typedef typename traits_type::pointer pointer;
        typedef typename traits_type::reference reference;

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


}

#endif //MYSTL_ITERATOR_H
