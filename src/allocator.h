//
// Created by hlx on 2023-04-14.
//

#ifndef MYSTL_ALLOCATOR_H
#define MYSTL_ALLOCATOR_H

#include <limits>

namespace mystl {

    template<typename T>
    class allocator {
        typedef T value_type;
        typedef T *pointer;

    public:
        allocator() noexcept = default;

        allocator(const allocator &) noexcept = default;

        template<typename U>
        explicit allocator(const allocator<U> &) noexcept {};

        ~allocator() noexcept = default;

        size_t max_size() noexcept {
            return std::numeric_limits<size_t>::max() / sizeof(value_type);
        }


    };

}

#endif //MYSTL_ALLOCATOR_H
