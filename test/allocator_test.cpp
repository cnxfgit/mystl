//
// Created by hlx on 2023-04-17.
//

#include <doctest/doctest.h>
#include <memory>
#include <vector>
#include "vector.h"

class AllocatorRef {
public:
    int i;

    AllocatorRef() : i(0) {};

    explicit AllocatorRef(int i) : i(i) {};

    ~AllocatorRef() {
        i = -1;
    };
};


TEST_CASE("allocator constructor()") {
    std::allocator<int> sa;
    std::allocator<int> sa1 = sa;
    std::allocator<double> sa2(sa1);
    std::allocator<void> sa3;

    mystl::allocator<int> ma;
    mystl::allocator<int> ma1 = ma;
    mystl::allocator<double> ma2(ma1);
    mystl::allocator<void> ma3;
}

TEST_CASE("allocator construct() destroy()") {
    std::allocator<AllocatorRef> sa;
    mystl::allocator<AllocatorRef> ma;
    AllocatorRef sa_ref;
    sa.construct(&sa_ref);

    AllocatorRef ma_ref;
    ma.construct(&ma_ref);
    CHECK_EQ(sa_ref.i, ma_ref.i);

    sa.construct(&sa_ref, 66);
    ma.construct(&ma_ref, 66);
    CHECK_EQ(sa_ref.i, ma_ref.i);

    sa.destroy(&sa_ref);
    ma.destroy(&ma_ref);
    CHECK_EQ(sa_ref.i, ma_ref.i);
}

TEST_CASE("allocator<void>") {
    // c++11 已经废弃allocator<void> 仅仅作为适配
    std::allocator<void> sa;
    mystl::allocator<void> ma;
}

TEST_CASE("allocator max_size()") {
    std::allocator<int> sa;
    mystl::allocator<int> ma;
    CHECK_EQ(ma.max_size(), sa.max_size());

    std::allocator<char> sa1;
    mystl::allocator<long> ma1;
    CHECK_NE(ma1.max_size(), sa1.max_size());
}

TEST_CASE("allocator operator()") {
    std::allocator<int> sa;
    mystl::allocator<int> ma;
    std::allocator<char> sa1;
    mystl::allocator<char> ma1;
    CHECK_EQ(sa == sa, ma == ma);
    CHECK_EQ(sa == sa1, ma1 == ma1);

    CHECK_EQ(sa != sa, ma != ma);
    CHECK_EQ(sa != sa1, ma1 != ma1);
}

TEST_CASE("allocator rebind()") {
    std::allocator<char>::rebind<int>::other sa;
    std::vector<int, std::allocator<char>::rebind<int>::other> vector1(sa);

    mystl::allocator<char>::rebind<int>::other ma;
    mystl::vector<int, mystl::allocator<char>::rebind<int>::other> vector2(ma);
}

TEST_CASE("allocator address()") {
    std::allocator<int> sa;
    mystl::allocator<int> ma;
    int i = 0;
    int &r = i;

    CHECK_EQ(sa.address(i), ma.address(i));
    CHECK_EQ(sa.address(r), ma.address(r));

    std::allocator<AllocatorRef> sa1;
    mystl::allocator<AllocatorRef> ma1;
    auto *ref = new AllocatorRef();
    const AllocatorRef &rr = *ref;
    CHECK_EQ(sa1.address(rr), ma1.address(rr));

    delete ref;
}


TEST_CASE("allocator allocate() deallocate()") {
    std::allocator<int> sa;
    mystl::allocator<int> ma;

    bool e1 = false;
    bool e2 = false;
    int *i1 = nullptr;
    int *i2 = nullptr;
    try {
        i1 = sa.allocate(SIZE_MAX);
    } catch (std::bad_alloc &e) {
        e1 = true;
    }
    try {
        i2 = ma.allocate(SIZE_MAX);
    } catch (std::bad_alloc &e) {
        e2 = true;
    }

    CHECK_EQ(e1, e2);

    sa.deallocate(i1, 1);
    ma.deallocate(i2, 1);

    std::allocator<AllocatorRef> sa1;
    mystl::allocator<AllocatorRef> ma1;

    AllocatorRef *r1 = sa1.allocate(10);
    AllocatorRef *r2 = ma1.allocate(10);

    AllocatorRef *t1 = r1;
    AllocatorRef *t2 = r2;
    for (int i = 0; i < 3; ++i) {
        sa1.construct(t1, i);
        ma1.construct(t2, i);
        CHECK_EQ(t1->i, i);
        CHECK_EQ(t2->i, i);
        t1++;
        t2++;
    }

    sa1.deallocate(r1, 10);
    ma1.deallocate(r2, 0);
}