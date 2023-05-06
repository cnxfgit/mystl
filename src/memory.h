//
// Created by hlx on 2023-04-27.
//

#ifndef MYSTL_MEMORY_H
#define MYSTL_MEMORY_H

#include <limits>

namespace mystl {

    template<typename T>
    class allocator {
    public:
        typedef T value_type;
        typedef size_t size_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;

        // 重绑定一个真实分配类型U
        template<typename U>
        struct rebind {
            using other = allocator<U>;
        };

        allocator() noexcept = default;

        allocator(const allocator &alt) noexcept {}

        template<typename U>
        explicit allocator(const allocator<U> &) noexcept {}

        ~allocator() noexcept = default;

        size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max() / sizeof(value_type);
        }

        template<typename U, typename... Args>
        void construct(U *p, Args &&... args) {
            ::new((void *) p) U(std::forward<Args>(args)...);
        }

        template<typename U>
        void destroy(U *p) {
            p->~U();
        }

        pointer address(reference x) const noexcept {
            return &x;
        }

        const_pointer address(const_reference x) const noexcept {
            return &x;
        }

        // new出来的内存强转为T 所以不管分配多少都是一块 只需要对应new delete 不需要 new[] delete[]
        pointer allocate(size_type n, const void * = static_cast<const void *>(nullptr)) {
            if (n > this->max_size())
                throw std::bad_alloc();

            return static_cast<T *>(::operator new(n * sizeof(T)));
        }

        // 同上 size 没啥作用 传啥都一样
        void deallocate(pointer p, size_type)
        {
            ::operator delete(p);
        }
    };

    template<typename T1, typename T2>
    inline bool operator==(const allocator<T1> &, const allocator<T2> &) noexcept {
        return true;
    }

    template<typename T1, typename T2>
    inline bool operator!=(const allocator<T1> &, const allocator<T2> &) noexcept {
        return false;
    }

    template<>
    class allocator<void> {
    public:
        template<typename U>
        struct rebind {
            typedef allocator<U> other;
        };
    };



    template<typename InputIterator, typename ForwardIterator>
    inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
        while (first != last) {
            new (static_cast<void*>(&*result)) typename ForwardIterator::value_type(*first);
            ++result;
            ++first;
        }
        return result;
    }

}

#endif //MYSTL_MEMORY_H
