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

}

#endif //MYSTL_UTILITY_H
