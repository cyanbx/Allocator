#include <iostream>
#include <random>
#include <vector>
#include <cstdio>
#include <chrono>
#include "alloc_with_pool.h"
#include "sample_allocator.h"

/* This is a extreme case specially provided for MemoryPool using Point2D to compare with int*/

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

    using PoIntDeq = std::vector<Point2D, MyAllocator<Point2D> >;
    std::vector<PoIntDeq, MyAllocator<PoIntDeq> > vecpts1(TestSize);
    for (int i = 0; i < TestSize; i++)
        vecpts1[i].resize(64);//one block is larger, accounting for 64 Point2D

    std::vector<PoIntDeq, MyAllocator<PoIntDeq> > vecpts2(TestSize);
    for (int i = 0; i < TestSize; i++)
        vecpts2[i].resize(16);////the other block only occupies 16 Point2D
    /* The two numbers are chosen because the 8 byteS Point2D puts 64 small block upper bounds that can be lower than memorypool management memory (here set to 1024 bytes)*/

     auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < PickSize; i++) {
        int idx = i;

        vecpts1[idx].resize(32);//reduce the larger vector to 32 Point2D
                                //ensure that the free_list of memorypool recovers the free blocks of sufficient size and number
        vecpts2[idx].resize(32);//enlarge the smaller vector to 32 Point2D
                                //the block that has just been recovered happens to come in handy
    }
     auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds."
        << std::endl;

    return 0;
    fclose(stdout);
}
