//
// Created by hlx on 2023-04-13.
//

#include <doctest/doctest.h>
#include <vector>
#include "vector.h"
#include <iostream>
#include <memory>

class Ref {
public:
    bool copyFlag;

    Ref() : copyFlag(false) {
        std::cout << "init" << std::endl;
    }

    Ref(const Ref &ref) : copyFlag(true) {
        std::cout << "copy" << std::endl;
    }
    ~Ref(){
        std::cout << "~Ref()" << std::endl;
    }
};

template<typename T>
static bool vector_eq(std::vector<T> &v, mystl::vector<T> &mv) {
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

    std::vector<int> v2 = {1, 2, 3};
    mystl::vector<int> mv2 = {1, 2, 3};
    CHECK(vector_eq(v2, mv2));

    std::vector<int, std::allocator<int>> v3(v2);
    mystl::vector<int, mystl::allocator<int>> mv3(mv2);
    CHECK(vector_eq(v3, mv3));

    SUBCASE("constructor() inner copy") {
        std::vector<Ref> iv1 = {Ref()};
        mystl::vector<Ref> imv1 = {Ref()};
        std::cout << iv1[0].copyFlag << "--" << imv1[0].copyFlag << std::endl;
        CHECK_EQ(iv1[0].copyFlag, imv1[0].copyFlag);
    }


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
public:
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
    CHECK(1 == 1);

    ::operator new(sizeof(int));

    mystl::allocator<int> a1;

}