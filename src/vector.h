//
// Created by hlx on 2023-04-13.
//

#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

#include "utility.h"
#include "algorithm.h"
#include "iterator.h"
#include "memory.h"

namespace mystl {

    const size_t DEFAULT_SIZE = 8;

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
        typedef normal_iterator<pointer, vector> iterator;
        typedef normal_iterator<const_pointer, vector> const_iterator;
        typedef mystl::reverse_iterator<iterator> reverse_iterator;
        typedef mystl::reverse_iterator<const_iterator> const_reverse_iterator;

    private:
        size_type _size;
        size_type _capacity;
        pointer _data;
        allocator_type _alloc;

        // 重定义长度
        template<bool B>
        void _resize(size_type n, const value_type &value = value_type()) {
            if (n <= 0) {
                clear();
            } else if (n < _size) {
                iterator iter(_data + n);
                for (; iter != end(); ++iter) {
                    _alloc.destroy(iter.base());
                }
                _size = n;
            } else if (n > _size) {
                if (n > _capacity) {
                    _expansion();
                }
                for (int i = 0; i < n - _size; ++i) {
                    if (B) {
                        push_back(value);
                    } else {
                        push_back(value_type());
                    }
                }
                _size = n;
            }
        }

        // 不重置长度的清空
        void _clear(iterator begin, iterator end) {
            for (iterator temp = end - 1; temp != begin - 1; temp = --temp) {
                _alloc.destroy(temp.base());
            }
        }

        // 扩容
        void _expansion() {
            // 旧数据迭代器
            iterator begin = this->begin();
            iterator end = this->end();
            // 扩容并复制旧值
            _capacity = _capacity * 2;
            _data = _alloc.allocate(_capacity);
            copy(begin, end, this->begin());
            // 析构原地址
            _clear(begin, end);
            _alloc.deallocate(begin.base(), 0);
        }

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

        vector(vector &&v) noexcept: _alloc(v._alloc), _capacity(v._capacity),
                                     _size(v._size), _data(v._data) {
            // 防止move后的vector被析构
            v._data = nullptr;
            v._capacity = 0;
            v._size = 0;
        }

        template<typename Iterator, typename = RequireInputIter<Iterator>>
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
                    vector temp = vector(v);
                    this->swap(temp);
                } else if (this->size() > v.size()) {
                    auto end = mystl::copy(v.cbegin(), v.cend(), this->begin());
                    this->_alloc = v._alloc;
                    for (auto i = end; i != this->end(); ++i) {
                        _alloc.destroy(i.base());
                    }
                    this->_size = v.size();
                } else {
                    mystl::copy(v.cbegin(), v.cbegin() + this->size(), this->begin());
                    mystl::uninitialized_copy(v.cbegin() + this->size(), v.cend(), this->end());
                }
            }
            return *this;
        }

        vector &operator=(vector &&v) noexcept {
            if (this != &v) {
                _alloc = v._alloc;
                _capacity = v._capacity;
                _size = v._size;
                _data = v._data;

                // 防止move后的vector被析构
                v._data = nullptr;
                v._capacity = 0;
                v._size = 0;
            }
            return *this;
        }

        vector &operator=(std::initializer_list<value_type> list) noexcept {
            vector temp(list.begin(), list.end());
            this->swap(temp);
            return *this;
        }

        size_type size() const noexcept {
            return _size;
        }

        size_type max_size() const noexcept {
            return _alloc.max_size();
        }

        // 使用value_type的默认值
        void resize(size_type n) {
            _resize<false>(n);
        }

        void resize(size_type n, const value_type &value) {
            _resize<true>(n, value);
        }

        void reserve(size_type n) {
            if (n > max_size()) {
                throw std::bad_alloc();
            }
            if (n > _capacity) {
                // 旧数据迭代器
                iterator begin = this->begin();
                iterator end = this->end();
                // 扩容并复制旧值
                _capacity = n;
                _data = _alloc.allocate(_capacity);
                copy(begin, end, this->begin());
                // 析构原地址
                _clear(begin, end);
                _alloc.deallocate(begin.base(), 0);
            }
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

        const_iterator begin() const noexcept {
            return const_iterator(_data);
        }

        iterator end() noexcept {
            return iterator(_data + _size);
        }

        const_iterator end() const noexcept {
            return const_iterator(_data + _size);
        }

        const_iterator cbegin() const noexcept {
            return const_iterator(_data);
        }

        const_iterator cend() const noexcept {
            return const_iterator(_data + _size);
        }

        reverse_iterator rbegin() noexcept {
            return reverse_iterator(end());
        };

        const_reverse_iterator rbegin() const noexcept {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() noexcept {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const noexcept {
            return const_reverse_iterator(begin());
        }

        const_reverse_iterator crbegin() const noexcept {
            return const_reverse_iterator(end());
        }

        const_reverse_iterator crend() const noexcept {
            return const_reverse_iterator(begin());
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

        void swap(vector &v) noexcept {
            mystl::swap(this->_capacity, v._capacity);
            mystl::swap(this->_data, v._data);
            mystl::swap(this->_size, v._size);
            mystl::swap(this->_alloc, v._alloc);
        }

        // 重置长度的清空
        void clear() noexcept {
            _clear(this->begin(), this->end());
            _size = 0;
        }

        template<typename ...Args>
        void emplace_back(Args &&...args) {
            if (_size == _capacity) {
                _expansion();
            }

            // 构造
            _alloc.construct(this->end().base(), forward<Args>(args)...);
            ++_size;
        }

        void push_back(const value_type &x) {
            if (_size == _capacity) {
                _expansion();
            }

            // 构造
            _alloc.construct(this->end().base(), x);
            ++_size;
        }

        void push_back(value_type &&x) {
            emplace_back(move(x));
        }

    };

}

#endif //MYSTL_VECTOR_H
