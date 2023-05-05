//
// Created by hlx on 2023-04-13.
//

#include <doctest/doctest.h>
#include <vector>
#include "vector.h"
#include <iostream>
#include "utility.h"

class Ref {
public:
    bool copyFlag;

    Ref() : copyFlag(false) {
        std::cout << "init" << std::endl;
    }

    Ref(const Ref &ref) : copyFlag(true) {
        std::cout << "copy" << std::endl;
    }

    ~Ref() {
        std::cout << "~Ref()" << std::endl;
    }

    bool operator==(Ref &other) const {
        return other.copyFlag == this->copyFlag;
    }
};

class Ptr {
public:
    int i;

    Ptr() : i(0) {
        std::cout << "init(0)" << std::endl;
    }

    explicit Ptr(int i) : i(i) {
        std::cout << "init(" << i << ")" << std::endl;
    }

    Ptr(const Ptr &ref) : i(ref.i) {
        std::cout << "copy(" << i << ")" << std::endl;
    }

    Ptr(Ptr &&ref) noexcept: i(ref.i) {
        std::cout << "move(" << i << ")" << std::endl;
    }

    ~Ptr() {
        std::cout << "~Ptr(" << i << ")" << std::endl;
    }

    bool operator==(Ptr &other) const {
        return other.i == this->i;
    }

    bool operator!=(Ptr &other) const {
        return other.i != this->i;
    }

    Ptr &operator=(Ptr &&ref) noexcept {
        this->i = ref.i;
        return *this;
    }

    Ptr &operator=(const Ptr &ref) = default;
};

template<typename T>
static bool vector_eq(std::vector<T> &v, mystl::vector<T> &mv) {
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

    SUBCASE("constructor() initializer_list copy") {
        std::vector<Ref> iv1 = {Ref()};
        mystl::vector<Ref> imv1 = {Ref()};
        std::cout << iv1[0].copyFlag << "--" << imv1[0].copyFlag << std::endl;
        CHECK_EQ(iv1[0].copyFlag, imv1[0].copyFlag);
    }
    std::vector<int> v4, v5{9, 8, 7};
    mystl::vector<int> mv4, mv5{9, 8, 7};
    CHECK(vector_eq(v4, mv4));
    CHECK(vector_eq(v5, mv5));

    std::vector<int> v6(5, 666);
    mystl::vector<int> mv6(5, 666);
    CHECK(vector_eq(v6, mv6));

    SUBCASE("constructor(size,value) copy") {
        std::vector<Ref> iv2(3, Ref());
        mystl::vector<Ref> imv2(3, Ref());
    }

    std::vector<int> v7(5, std::allocator<int>());
    mystl::vector<int> mv7(5, mystl::allocator<int>());
    std::fill(v7.begin(), v7.end(), 0);
    std::fill(mv7.begin(), mv7.end(), 0);
    CHECK(vector_eq(v7, mv7));

    // 交换分配器能通过编译
    std::vector<int, mystl::allocator<int>> v8;
    mystl::vector<int, std::allocator<int>> mv8;

    std::vector<int> v9(std::move(v7));
    mystl::vector<int> mv9(mystl::move(mv7));
    CHECK(vector_eq(v9, mv9));

    int iter[] = {1, 2, 3, 4, 5};
    std::vector<int> v10(iter, iter + 5);
    mystl::vector<int> mv10(iter, iter + 5);
    CHECK(vector_eq(v10, mv10));

}

TEST_CASE("vector::iterator") {
    std::vector<int> vec1 = {1, 2, 3};
    mystl::vector<int> vec2 = {1, 2, 3};
    auto iter1 = vec1.begin();
    auto iter2 = vec2.begin();
    iter2 - iter2;

    int *base1 = iter1.base();
    int *base2 = iter2.base();
    CHECK_EQ(*base1, *base2);

    int *p1 = iter1.operator->();
    int *p2 = iter2.operator->();
    CHECK_NE(p1, p2);

    int &r1 = iter1.operator*();
    int &r2 = iter2.operator*();
    CHECK_EQ(r1, r2);

    auto ir1 = iter1++;
    auto ir2 = iter2++;
    CHECK_EQ(*ir1.base(), *ir2.base());

    std::vector<int>::iterator &ir3 = ++iter1;
    mystl::vector<int>::iterator &ir4 = ++iter2;
    CHECK_EQ(*ir3.base(), *ir4.base());

    int &r3 = iter1.operator[](0);
    int &r4 = iter2.operator[](0);
    CHECK_EQ(r3, r4);

    auto ir5 = iter1--;
    auto ir6 = iter2--;
    CHECK_EQ(*ir5.base(), *ir6.base());

    std::vector<int>::iterator &ir7 = --iter1;
    mystl::vector<int>::iterator &ir8 = --iter2;
    CHECK_EQ(*ir7.base(), *ir8.base());

    auto r5 = iter1.operator+(1);
    auto r6 = iter2.operator+(1);
    CHECK_EQ(*r5.base(), *r6.base());

    std::vector<int>::iterator &ir9 = iter1.operator+=(1);
    mystl::vector<int>::iterator &ir10 = iter2.operator+=(1);
    CHECK_EQ(*ir9.base(), *ir10.base());

    auto r7 = iter1.operator-(1);
    auto r8 = iter2.operator-(1);
    CHECK_EQ(*r7.base(), *r8.base());

    std::vector<int>::iterator &ir11 = iter1.operator-=(1);
    mystl::vector<int>::iterator &ir12 = iter2.operator-=(1);
    CHECK_EQ(*ir11.base(), *ir12.base());

    CHECK(iter2 == ir8);
    CHECK(r8 != ir6);
}

TEST_CASE("vector get_allocator()") {
    std::vector<int> v;
    mystl::vector<int> mv;
    std::allocator<int> a1 = v.get_allocator();
    mystl::allocator<int> a2 = mv.get_allocator();
    CHECK(a1.max_size() == a2.max_size());
}

TEST_CASE("vector swap") {
    std::vector<Ptr> v = {Ptr(1), Ptr(2)};
    std::vector<Ptr> v1 = {Ptr(3), Ptr(4)};

    mystl::vector<Ptr> mv = {Ptr(1), Ptr(2)};
    mystl::vector<Ptr> mv1 = {Ptr(3), Ptr(4)};
    CHECK(vector_eq(v, mv));
    CHECK(vector_eq(v1, mv1));

    v.swap(v1);
    mv.swap(mv1);

    CHECK(vector_eq(v, mv));
    CHECK(vector_eq(v1, mv1));
}

TEST_CASE("vector cbegin() cend()") {
    std::vector<int> v = {1, 2, 3};
    mystl::vector<int> mv = {1, 2, 3};
    const std::vector<int>::const_iterator &vi = v.cbegin();
    const mystl::vector<int>::const_iterator &mvi = mv.cbegin();

//     *vi = 45;   不可变
//     *mvi = 123;
    std::vector<int> v1 = std::vector<int>(v.cbegin(), v.cend());
    mystl::vector<int> mv1 = mystl::vector<int>(mv.cbegin(), mv.cend());
    CHECK(vector_eq(v1, mv1));
}

TEST_CASE("vector operator=") {
    std::cout << "================== vector operator= ===================" << std::endl;
    std::vector<Ptr> v = {Ptr(1), Ptr(2)};
    std::vector<Ptr> v1 = {Ptr(3), Ptr(4)};
    v1 = v;

    mystl::vector<Ptr> mv = {Ptr(1), Ptr(2)};
    mystl::vector<Ptr> mv1 = {Ptr(3), Ptr(4)};
    mv1 = mv;
    CHECK(vector_eq(v1, mv1));

    std::vector<int> v2 = {6, 7, 8};
    std::vector<int> v3;
    v3 = std::move(v2);

    mystl::vector<int> mv2 = {6, 7, 8};
    mystl::vector<int> mv3;
    mv3 = mystl::move(mv2);
    CHECK(vector_eq(v3, mv3));

    std::vector<Ptr> v4 = {Ptr(456)};
    v4 = {Ptr(789)};

    mystl::vector<Ptr> mv4 = {Ptr(123)};
    mv4 = {Ptr(789)};
    CHECK(vector_eq(v4, mv4));

    std::cout << "================== vector operator= ===================" << std::endl;
}

TEST_CASE("vector clear()") {
    std::vector<int> v = {1, 2, 3};
    mystl::vector<int> mv = {1, 2, 3};

    CHECK(vector_eq(v, mv));

    v.clear();
    mv.clear();
    CHECK(vector_eq(v, mv));

    v.emplace_back(1);
    mv.emplace_back(1);
    v.emplace_back(2);
    mv.emplace_back(2);
    CHECK(vector_eq(v, mv));
}

TEST_CASE("vector push_back()") {
    std::vector<int> v;
    mystl::vector<int> mv;

    int i = int(66);
    v.push_back(1);
    v.push_back(i);
    v.emplace_back(i);
    v.emplace_back(2);

    mv.push_back(1);
    mv.push_back(i);
    mv.emplace_back(i);
    mv.emplace_back(2);

    CHECK(vector_eq(v, mv));

    mv.clear();
    v.clear();
}


TEST_CASE("vector reverse_iterator") {
    std::vector<int> vec1 = {1, 2, 3};
    mystl::vector<int> vec2 = {1, 2, 3};

    auto iter1 = vec1.rbegin();
    auto iter2 = vec2.rbegin();
    iter2 - iter2;

    int base1 = *iter1;
    int base2 = *iter2;
    CHECK_EQ(base1, base2);

    int *p1 = iter1.operator->();
    int *p2 = iter2.operator->();
    CHECK_NE(p1, p2);

    int &r1 = iter1.operator*();
    int &r2 = iter2.operator*();
    CHECK_EQ(r1, r2);

    auto ir1 = iter1++;
    auto ir2 = iter2++;
    CHECK_EQ(*ir1, *ir2);

    auto &ir3 = ++iter1;
    auto &ir4 = ++iter2;
    CHECK_EQ(*ir3, *ir4);

    int &r3 = iter1.operator[](0);
    int &r4 = iter2.operator[](0);
    CHECK_EQ(r3, r4);

    auto ir5 = iter1--;
    auto ir6 = iter2--;
    CHECK_EQ(*ir5, *ir6);

    auto &ir7 = --iter1;
    auto &ir8 = --iter2;
    CHECK_EQ(*ir7, *ir8);

    auto r5 = iter1.operator+(1);
    auto r6 = iter2.operator+(1);
    CHECK_EQ(*r5, *r6);

    auto &ir9 = iter1.operator+=(1);
    auto &ir10 = iter2.operator+=(1);
    CHECK_EQ(*ir9, *ir10);

    auto r7 = iter1.operator-(1);
    auto r8 = iter2.operator-(1);
    CHECK_EQ(*r7, *r8);

    auto &ir11 = iter1.operator-=(1);
    auto &ir12 = iter2.operator-=(1);
    CHECK_EQ(*ir11, *ir12);

    CHECK(iter2.base() == ir8.base());
    CHECK(r8.base() != ir6.base());
}
