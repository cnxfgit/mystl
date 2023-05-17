//
// Created by hlx on 2023-05-16.
//

#include <doctest/doctest.h>
#include <list>
#include "list.h"

template<typename T>
static bool list_eq(std::list<T> &l, mystl::list<T> &ml) {
    if (l.empty() != ml.empty()) {
        return false;
    }
    if (l.size() != ml.size()) {
        return false;
    }

    auto li = l.begin();
    auto mli = ml.begin();
    while (li != l.end()) {
        if (*mli != *li) {
            return false;
        }
        ++li;
        ++mli;
    }

    return true;
}


TEST_CASE("list constructor()") {
    std::list<int> l;
    mystl::list<int> ml;
    CHECK(list_eq(l, ml));

}