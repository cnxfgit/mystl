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


    // void_t
    template<typename ...>
    using void_t = void;


    template<typename From, typename To>
    struct is_convertible : public
            std::integral_constant<bool, std::__is_convertible_helper<From, To>::value> {
    };


}

#endif //MYSTL_TYPE_TRAITS_H
