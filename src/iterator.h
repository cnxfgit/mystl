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



    template<class Category, class T, class Distance = ptrdiff_t,
            class Pointer = T *, class Reference = T &>
    struct iterator {
        typedef Category iterator_category;
        typedef T value_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Distance difference_type;
    };


    template<typename T>
    struct iterator_traits {
    };


}

#endif //MYSTL_ITERATOR_H
