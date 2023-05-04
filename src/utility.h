//
// Created by hlx on 2023-04-23.
//

#ifndef MYSTL_UTILITY_H
#define MYSTL_UTILITY_H

#include "type_traits.h"

namespace mystl {

    template<typename T>
    constexpr typename remove_reference<T>::type &&move(T &&t) noexcept {
        return static_cast<typename remove_reference<T>::type &&>(t);
    }

    template<typename T>
    void swap(T &a, T &b) noexcept {
        T temp = move(a);
        a = move(b);
        b = move(temp);
    }

    template<typename T, size_t N>
    void swap(T (&a)[N], T (&b)[N]) noexcept {
        for (size_t i = 0; i < N; ++i) swap(a[i], b[i]);
    }

    template<typename T>
    constexpr T &&forward(typename remove_reference<T>::type &t) noexcept {
        return static_cast<T &&>(t);
    }
}

#endif //MYSTL_UTILITY_H
