#include "tsalloc.hpp"

#include <thread>

#include <gtest/gtest.h>

TEST(AllocTest, SimpleAlloc) {
    tsa::word_t* m;
    m = tsa::alloc(8);
    tsa::printBlocks();
    tsa::free(m);
}

TEST(AllocTest, DiffrentTypeSizes) {
    size_t arrSize = 3;
    tsa::word_t* m[arrSize] {};
    for (int i = 0, j = 1; i < arrSize; ++i, j *= 2) {
        m[i] = tsa::alloc(8 * j);
    }
    tsa::printBlocks();
    for (int i = 0; i < arrSize; ++i) {
        tsa::free(m[i]);
    }
}

void threadFun1() {
    size_t arrSize = 40;
    tsa::word_t* m[arrSize] {};
    for (int i = 0; i < arrSize; ++i) {
        m[i] = tsa::alloc(8);
    }

    for (int i = 0; i < arrSize; ++i) {
        tsa::free(m[i]);
    }
}

void threadFun2() {
    size_t arrSize = 20;
    tsa::word_t* m[arrSize] {};
    for (int i = 0; i < arrSize; ++i) {
        m[i] = tsa::alloc(8);
    }

    for (int i = 0; i < arrSize; ++i) {
        tsa::free(m[i]);
    }
}

TEST(ThreadTest, CheckPosition) {
    std::thread th1(threadFun1);
    std::thread th2(threadFun2);
    th1.join();
    th2.join();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}