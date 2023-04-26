//
// Created by hlx on 2023-04-23.
//

#ifndef MYSTL_ITERATOR_H
#define MYSTL_ITERATOR_H

#include "type_traits.h"
#include <iterator>

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


    // 通用迭代器
    template<typename T, typename Pointer>
    class normal_iterator {
    protected:
        Pointer _data;
    public:
        typedef T value_type;
        typedef Pointer pointer;
        typedef T& reference;
        typedef std::ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;

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


}

#endif //MYSTL_ITERATOR_H
