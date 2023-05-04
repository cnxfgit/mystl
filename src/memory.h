//
// Created by hlx on 2023-04-27.
//

#ifndef MYSTL_MEMORY_H
#define MYSTL_MEMORY_H

namespace mystl {

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
