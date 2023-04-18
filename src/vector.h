//
// Created by hlx on 2023-04-13.
//

#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

#include <iostream>
#include <memory>
#include "base.h"
#include "allocator.h"

namespace mystl {

    template<typename T, typename A = allocator<T> >
    class vector {
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef A allocator_type;

    public:
        class iterator {
        private:
            pointer _data;
        public:
            iterator() : _data(nullptr) {}

            explicit iterator(pointer data) : _data(data) {}

            pointer base() const noexcept {
                return nullptr;
            }

            pointer operator++() {

            }

            ~iterator() = default;
        };

    private:
        size_type _size;
        size_type _capacity;
        pointer _data;

    public:

        vector() noexcept {
            _capacity = 0;
            _size = 0;
            _data = new T[DEFAULT_SIZE];
        };

        vector(std::initializer_list<T> list) {
            _size = list.size();
            _capacity = list.size();
            _data = new T[_size];
            pointer iter = _data;
            for (auto c = list.begin(); c != list.end(); ++c, ++iter) {
                *iter = *c;
            }
        }

        explicit vector(const allocator_type &a) noexcept {
            _capacity = 0;
            _size = 0;
            _data = new T[DEFAULT_SIZE];
        }

        ~vector() {

        };

        size_type size() const noexcept {
            return _size;
        }

        size_type capacity() const noexcept {
            return _capacity;
        }

        bool empty() const noexcept {
            return _size == 0;
        }

        iterator begin() {
            return iterator(_data);
        }

        iterator end() {
            return iterator(_data + _size);
        }

        T &operator[](size_type idx) {
            return _data[idx];
        }
    };

}

#endif //MYSTL_VECTOR_H
