//
// Created by hlx on 2023-05-16.
//

#include <doctest/doctest.h>
#include <iterator>
#include <vector>
#include "vector.h"

TEST_CASE("mystl begin() end()") {
    std::vector<int> v = {1, 2, 3};
    mystl::vector<int> mv = {1, 2, 3};;

    auto vb = std::begin(v);
    auto mvb = mystl::begin(mv);
    CHECK_EQ(*vb, *mvb);

    int array[] = {4, 5, 6};
    auto vb1 = std::begin(array);
    auto mvb1 = mystl::begin(array);
    CHECK_EQ(*vb1, *mvb1);

    const std::vector<int> v2 = {7, 8, 7};
    const mystl::vector<int> mv2 = {7, 8, 7};;

    auto vb2 = std::begin(v2);
    auto mvb2 = mystl::begin(mv2);
    CHECK_EQ(*vb2, *mvb2);
}

