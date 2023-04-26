//
// Created by hlx on 2023-04-25.
//

#ifndef MYSTL_ALGORITHM_H
#define MYSTL_ALGORITHM_H

#include <iterator>

namespace mystl {

    template<typename InputIterator, typename OutputIterator>
    inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
        static_assert(std::is_same<typename std::iterator_traits<InputIterator>::iterator_category,
                              std::input_iterator_tag>::value,
                      "InputIterator must be an input iterator");

        static_assert(std::is_same<typename std::iterator_traits<OutputIterator>::iterator_category,
                              std::output_iterator_tag>::value,
                      "OutputIterator must be an output iterator");

        while (first != last) {
            *result = *first;
            ++result;
            ++first;
        }
        return result;
    }

}

#endif //MYSTL_ALGORITHM_H
