//
// Created by hlx on 2023-04-23.
//

#ifndef MYSTL_TYPE_TRAITS_H
#define MYSTL_TYPE_TRAITS_H

namespace mystl {

    // remove_reference
    template<typename T>
    struct remove_reference {
        typedef T type;
    };

    template<typename T>
    struct remove_reference<T &> {
        typedef T type;
    };

    template<typename T>
    struct remove_reference<T &&> {
        typedef T type;
    };


    // enable_if
    template<bool, typename T = void>
    struct enable_if {
    };

    template<typename T>
    struct enable_if<true, T> {
        typedef T type;
    };

}

#endif //MYSTL_TYPE_TRAITS_H
