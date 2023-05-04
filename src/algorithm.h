//
// Created by hlx on 2023-04-25.
//

#ifndef MYSTL_ALGORITHM_H
#define MYSTL_ALGORITHM_H

#include <iterator>

namespace mystl {

    template<typename InputIterator, typename OutputIterator>
    inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
        while (first != last) {
            *result = *first;
            ++result;
            ++first;
        }
        return result;
    }

}

#endif //MYSTL_ALGORITHM_H
