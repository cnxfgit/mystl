//
// Created by hlx on 2023-05-16.
//

#include <doctest/doctest.h>
#include <list>
#include "list.h"
#include "memory.h"
#include <iostream>

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

    std::list<int, std::allocator<int>> l1;
    mystl::list<int, mystl::allocator<int>> ml1;
    CHECK(list_eq(l1, ml1));

    std::list<int> l2(5);
    mystl::list<int> ml2(5);
    CHECK(list_eq(l2, ml2));

}