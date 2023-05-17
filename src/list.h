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
            return *this;
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
    };

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

    private:
        list_node<T> *_head;
        list_node<T> *_tail;
        size_type _size;

    public:

        list() : _head(nullptr), _tail(nullptr), _size(0) {}


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
            return iterator();
        }

        const_iterator begin() const noexcept {
            return iterator();
        }


    };

}

#endif //MYSTL_LIST_H
