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
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef A allocator_type;

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
        allocator_type _alloc;

    public:

        vector() noexcept {
            _capacity = 0;
            _size = 0;
            _data = _alloc.allocate(DEFAULT_SIZE);
        };

        vector(std::initializer_list<T> list) {
            _size = list.size();
            _capacity = list.size();
            _data = _alloc.allocate(_size);
            pointer iter = _data;
            for (auto c = list.begin(); c != list.end(); ++c, ++iter) {
                _alloc.construct(iter, mystl::move(*c));
            }
        }

        explicit vector(const allocator_type &a) noexcept {
            _capacity = 0;
            _size = 0;
            _data = _alloc.allocate(DEFAULT_SIZE);
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

        ~vector() {
            pointer reverse_iter = _data + _size - 1;
            for (int i = 0; i < _size; ++i) {
                pointer p = reverse_iter - i;
                _alloc.destroy(p);
            }
            _alloc.deallocate(_data, 0);
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

        const_reference operator[](size_type idx) const {
            return _data[idx];
        }

        reference operator[](size_type idx) {
            return _data[idx];
        }
    };

}

#endif //MYSTL_VECTOR_H
