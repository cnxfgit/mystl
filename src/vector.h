//
// Created by hlx on 2023-04-13.
//

#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

#include <iostream>
#include <memory>
#include "allocator.h"
#include "utility.h"

namespace mystl {

    const size_t DEFAULT_SIZE = 8;

    template<typename T, typename A = allocator <T> >
    class vector {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef A allocator_type;

        class iterator {
        public:
            typedef T value_type;
            typedef T *pointer;
            typedef T &reference;
            typedef size_t size_type;
            typedef std::ptrdiff_t difference_type;
            typedef std::random_access_iterator_tag iterator_category;
        private:
            pointer _iter_data;
        public:
            iterator() : _iter_data(nullptr) {}

            explicit iterator(pointer data) : _iter_data(data) {}

            iterator(const iterator &other) : _iter_data(other._iter_data) {}

            pointer base() const noexcept {
                return _iter_data;
            }

            iterator &operator++() noexcept {
                ++_iter_data;
                return *this;
            }

            iterator operator++(int) noexcept {
                return iterator(_iter_data++);
            }

            iterator &operator--() noexcept {
                --_iter_data;
                return *this;
            }

            iterator operator--(int) noexcept {
                return iterator(_iter_data--);
            }

            iterator operator+(difference_type n) const noexcept {
                return iterator(_iter_data + n);
            }

            iterator &operator+=(difference_type n) noexcept {
                _iter_data += n;
                return *this;
            }

            iterator operator-(difference_type n) const noexcept {
                return iterator(_iter_data - n);
            }

            iterator &operator-=(difference_type n) noexcept {
                _iter_data -= n;
                return *this;
            }

            reference operator*() const noexcept {
                return *_iter_data;
            }

            pointer operator->() const noexcept {
                return _iter_data;
            }

            reference operator[](difference_type n) const noexcept {
                return _iter_data[n];
            }

            inline friend
            difference_type operator-(const iterator &lhs, const iterator &rhs) noexcept {
                return lhs.base() - rhs.base();
            }

            inline friend
            bool operator==(const iterator &lhs, const iterator &rhs) noexcept {
                return lhs.base() == rhs.base();
            }

            inline friend
            bool operator!=(const iterator &lhs, const iterator &rhs) noexcept {
                return lhs.base() != rhs.base();
            }

            inline friend
            bool operator>(const iterator &lhs, const iterator &rhs) noexcept {
                return lhs.base() > rhs.base();
            }

            inline friend
            bool operator>=(const iterator &lhs, const iterator &rhs) noexcept {
                return (lhs.base() >= rhs.base()) || (lhs.base() == rhs.base());
            }

            inline friend
            bool operator<(const iterator &lhs, const iterator &rhs) noexcept {
                return lhs.base() < rhs.base();
            }

            inline friend
            bool operator<=(const iterator &lhs, const iterator &rhs) noexcept {
                return (lhs.base() <= rhs.base()) || (lhs.base() == rhs.base());
            }

            ~iterator() = default;
        };

    private:
        size_type _size;
        size_type _capacity;
        pointer _data;
        allocator_type _alloc;

    public:

        vector() noexcept {
            _capacity = DEFAULT_SIZE;
            _size = 0;
            _data = _alloc.allocate(_capacity);
        };

        vector(std::initializer_list<value_type> list) {
            _size = list.size();
            _capacity = list.size();
            _data = _alloc.allocate(_capacity);
            pointer iter = _data;
            for (auto c = list.begin(); c != list.end(); ++c, ++iter) {
                _alloc.construct(iter, *c);
            }
        }

        explicit vector(const allocator_type &a) noexcept {
            _capacity = DEFAULT_SIZE;
            _size = 0;
            _data = _alloc.allocate(_capacity);
        }

        vector(size_type n, value_type value) {
            _capacity = n;
            _size = n;
            _data = _alloc.allocate(_capacity);
            pointer iter = _data;
            for (int i = 0; i < _size; ++i, ++iter) {
                _alloc.construct(iter, value);
            }
        }

        explicit vector(size_type n, const allocator_type &a = allocator_type()) {
            _capacity = n;
            _size = n;
            _data = _alloc.allocate(_capacity);
        }

        vector(const vector &v) {
            _alloc = v._alloc;
            _capacity = v.capacity();
            _size = v.size();
            _data = _alloc.allocate(_capacity);
            for (int i = 0; i < _size; ++i) {
                _data[i] = v[i];
            }
        }

        vector(vector &&v) noexcept {
            _alloc = v._alloc;
            _capacity = v._capacity;
            _size = v._size;
            _data = v._data;

            // 防止move后的vector被析构
            v._data = nullptr;
            v._capacity = 0;
            v._size = 0;
        }

        template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
        vector(Iterator first, Iterator last, const allocator_type &a = allocator_type()) {
            _capacity = last - first;
            _size = _capacity;
            _data = _alloc.allocate(_capacity);

            pointer iter = _data;
            for (auto c = first; c != last; ++c, ++iter) {
                _alloc.construct(iter, *c);
            }
        }

        ~vector() {
            pointer reverse_iter = _data + _size - 1;
            for (int i = 0; i < _size; ++i) {
                pointer p = reverse_iter - i;
                _alloc.destroy(p);
            }
            _alloc.deallocate(_data, 0);
        };

        vector &operator=(const vector &v) {
            if (&v != this) {
                if (v.size() > this->capacity()) {
                    vector temp(v.begin(), v.end());
                    this->swap(v);
                } else if (this->size() > v.size()) {

                }
            }
            return *this;
        }

        vector& operator=(vector&& v)  noexcept {

        }

        vector& operator=(std::initializer_list<value_type> list)  noexcept {

        }

        size_type size() const noexcept {
            return _size;
        }

        size_type capacity() const noexcept {
            return _capacity;
        }

        bool empty() const noexcept {
            return _size == 0;
        }

        iterator begin() noexcept {
            return iterator(_data);
        }

        iterator end() noexcept {
            return iterator(_data + _size);
        }

        const_reference operator[](size_type idx) const {
            return _data[idx];
        }

        reference operator[](size_type idx) {
            return _data[idx];
        }

        allocator_type get_allocator() const noexcept {
            return this->_alloc;
        }

        void swap(vector &v) {
            mystl::swap(this->_capacity, v._capacity);
            mystl::swap(this->_data, v._data);
            mystl::swap(this->_size, v._size);
            mystl::swap(this->_alloc, v._alloc);
        }
    };

}

#endif //MYSTL_VECTOR_H
