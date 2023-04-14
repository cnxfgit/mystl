//
// Created by hlx on 2023-04-13.
//

#include <doctest/doctest.h>
#include <vector>
#include "vector.h"
#include <iostream>
#include <memory>


template<typename T>
static bool vector_eq(std::vector<T> v, mystl::vector<T> mv) {
    if (v.capacity() != mv.capacity()) {
        return false;
    }
    if (v.empty() != mv.empty()) {
        return false;
    }
    if (v.size() != mv.size()) {
        return false;
    }

    for (int i = 0; i < v.size(); ++i) {
        if (v[i] != mv[i]) return false;
    }

    return true;
}

TEST_CASE("vector constructor()") {
    std::vector<int> v1;
    mystl::vector<int> mv1;
    CHECK(vector_eq(v1, mv1));

}

TEST_CASE("test") {
    std::vector<int> v1 = {1, 2, 3};
    int &i = *(v1.begin());
    i = 19;
    std::cout << v1.capacity() << v1.size() << std::endl;

    mystl::vector<int> mv1 = {1, 2, 10086};
    std::cout << mv1[2] << std::endl;


    std::vector<int>::iterator iterator;

    mystl::vector<int>::iterator iter;
    // todo iterator.base()函数没搞懂
}

class A {
    A() {
        std::cout << "A()" << std::endl;
    }
    ~A() {
        std::cout << "~A()" << std::endl;
    }
};

TEST_CASE("begin") {
    int i[] = {1, 2, 3};
    int *p = std::begin(i);
    std::allocator<int> allocator;
    int *b = allocator.allocate(10);


    ::operator new(sizeof(int));

    mystl::allocator<int> a1;

}