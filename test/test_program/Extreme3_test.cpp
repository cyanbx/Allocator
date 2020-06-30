#include <iostream>
#include <random>
#include <vector>
#include <cstdio>
#include <chrono>
#include "alloc_with_pool.h"
#include "sample_allocator.h"

template <class T>
using MyAllocator = std::allocator<T>;  // replace the std::allocator with your allocator
using Point2D = std::pair<int, int>;

const int TestSize = 30000;//Number of vector when creating; Range of vector resizing
const int PickSize = 10000;//Number of vector resizing

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, TestSize);

    //auto start = std::chrono::high_resolution_clock::now();
    using IntDeq = std::vector<int, MyAllocator<int> >;
    std::vector<IntDeq, MyAllocator<IntDeq> > vecints1(TestSize);
    for (int i = 0; i < TestSize; i++) vecints1[i].resize(1024);

    std::vector<IntDeq, MyAllocator<IntDeq> > vecints2(TestSize);
    for (int i = 0; i < TestSize; i++) vecints2[i].resize(256);
    //auto end = std::chrono::high_resolution_clock::now();

     auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < PickSize; i++) {
        int idx = i;

        vecints1[idx].resize(512);
        vecints2[idx].resize(512);
    }
     auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds."
        << std::endl;

    return 0;
}
