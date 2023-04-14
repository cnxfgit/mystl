//
// Created by hlx on 2023-04-14.
//

#ifndef MYSTL_BASE_H
#define MYSTL_BASE_H

namespace mystl {

    const size_t DEFAULT_SIZE = 8;

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

    template<typename T>
    constexpr typename remove_reference<T>::type &&move(T &&t) noexcept {
        return static_cast<typename remove_reference<T>::type &&>(t);
    }


}

#endif //MYSTL_BASE_H
