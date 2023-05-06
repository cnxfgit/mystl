//
// Created by hlx on 2023-04-23.
//

#ifndef MYSTL_TYPE_TRAITS_H
#define MYSTL_TYPE_TRAITS_H

#include <cstddef>

namespace mystl {

    // remove_reference
    template<typename T>
    struct remove_reference {
        using type = T;
    };

    template<typename T>
    struct remove_reference<T &> {
        typedef T type;
    };

    template<typename T>
    struct remove_reference<T &&> {
        typedef T type;
    };

    // remove_reference type直接类型
    template<typename T>
    using remove_reference_t = typename remove_reference<T>::type;


    // enable_if
    template<bool, typename T = void>
    struct enable_if {
    };

    template<typename T>
    struct enable_if<true, T> {
        typedef T type;
    };

    template<bool B, typename T = void>
    using enable_if_t = typename enable_if<B, T>::type;

    // void_t
    template<typename ...>
    using void_t = void;

    // is_convertible
    template<typename From, typename To>
    struct is_convertible : public std::integral_constant<bool, std::__is_convertible_helper<From, To>::value> {
    };


    // conditional
    template<bool B, typename T, typename F>
    struct conditional {
        using type = T;
    };

    template<typename T, typename F>
    struct conditional<false, T, F> {
        using type = F;
    };

    template<bool B, typename T, typename F>
    using conditional_t = typename conditional<B, T, F>::type;

}

#endif //MYSTL_TYPE_TRAITS_H
