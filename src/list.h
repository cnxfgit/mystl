//
// Created by hlx on 2023-05-16.
//

#ifndef MYSTL_LIST_H
#define MYSTL_LIST_H

#include <cstddef>
#include "memory.h"
#include "iterator.h"

namespace mystl {

    template<typename T>
    class list_node {
    public:
        T _data;
        list_node *_prev;
        list_node *_next;
    };

    template<typename T>
    class list_iterator {
        using Node = list_node<T>;
        using Self = list_iterator<T>;

    private:
        Node *_node;

    public:
        using difference_type = std::ptrdiff_t;
        using iterator_category = bidirectional_iterator_tag;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        list_iterator() : _node(nullptr) {}

        explicit list_iterator(Node *node) : _node(node) {}

        reference operator*() const {
            return _node->_data;
        }

        pointer operator->() const {
            return &(_node->_data);
        }

        Self &operator++() {
            _node = _node->_next;
            return *this;
        }

        Self operator++(int) {
            Self tmp = *this;
            _node = _node->_next;
            return tmp;
        }

        Self &operator--() {
            _node = _node->_prev;
            return *this;
        }

        Self operator--(int) {
            Self tmp = *this;
            _node = _node->_prev;
            return tmp;
        }

        bool operator==(const Self &x) const {
            return _node == x._node;
        }

        bool operator!=(const Self &x) const {
            return _node != x._M_node;
        }

    };

    template<typename T>
    class const_list_iterator {
        using Node = list_node<T>;
        using Self = const_list_iterator<T>;

    public:
        using difference_type = std::ptrdiff_t;
        using iterator_category = bidirectional_iterator_tag;
        using value_type = T;
        using pointer = const T *;
        using reference = const T &;

    private:
        const Node *_node;

    public:

        const_list_iterator() : _node(nullptr) {}

        explicit const_list_iterator(const Node *node) : _node(node) {}

        explicit const_list_iterator(const list_iterator<T> &x) : _node(x._node) {}

        reference operator*() const {
            return _node->_data;
        }

        pointer operator->() const {
            return &(_node->_M_data);
        }

        Self &operator++() {
            _node = _node->_next;
            return *this;
        }

        Self operator++(int) {
            Self tmp = *this;
            _node = _node->_next;
            return tmp;
        }

        Self &operator--() {
            _node = _node->_prev;
            return *this;
        }

        Self
        operator--(int) {
            Self tmp = *this;
            _node = _node->_prev;
            return tmp;
        }

        bool operator==(const Self &x) const { return _node == x._node; }

        bool operator!=(const Self &x) const { return _node != x._node; }
    };

    template<typename Val>
    inline bool
    operator==(const list_iterator<Val> &x, const const_list_iterator<Val> &y) {
        return x._node == y._node;
    }

    template<typename Val>
    inline bool
    operator!=(const list_iterator<Val> &x, const const_list_iterator<Val> &y) {
        return x._node != y._node;
    }


    template<typename T, typename A = allocator<T>>
    class list {
    public:
        using value_type = T;
        using pointer = T *;
        using const_pointer = const T *;
        using reference = T &;
        using const_reference = const T &;
        using size_type = size_t;
        using allocator_type = A;

        using iterator = list_iterator<T>;
        using const_iterator = const_list_iterator<T>;

        using node_allocator_type = typename A::template rebind<list_node<T>>::
        other;

    private:
        list_node<T> *_head;
        list_node<T> *_tail;
        size_type _size;
        allocator_type _alloc;
        node_allocator_type _node_alloc;

    public:

        list() : _head(nullptr), _tail(nullptr), _size(0) {}

        explicit list(const allocator_type &alloc) : _head(nullptr),
                                                     _tail(nullptr), _size(0), _alloc(alloc) {
            typename allocator_type::template rebind<list_node<T>>
                    node_alloc;
            _node_alloc = node_alloc;
        }

        explicit list(size_type n) : _size(n) {
            list_node<T> *prev = nullptr;
            for (int i = 0; i < n; ++i) {
                list_node<T> *node = _node_alloc.allocate(1);
                node->_data = T();
                if (i == 0) {
                    _head = node;
                }
                if (prev != nullptr) {
                    prev->_next = node;
                    node->_prev = prev;
                }
                prev = node;
            }
            if (prev != nullptr) {
                _tail = prev;
            }
        }

        size_type max_size() const noexcept {
            return 0;
        }

        size_type size() const noexcept {
            return _size;
        }

        bool empty() const noexcept {
            return _size == 0;
        }

        iterator begin() noexcept {
            return iterator(_head);
        }

        const_iterator begin() const noexcept {
            return const_iterator(_head);
        }


    };

}

#endif //MYSTL_LIST_H
