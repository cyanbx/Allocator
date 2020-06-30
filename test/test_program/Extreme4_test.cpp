#include <iostream>
#include <random>
#include <vector>
#include <cstdio>
#include <chrono>
#include "alloc_with_pool.h"
#include "sample_allocator.h

/*With the analysis of Case3, we reduce the reszing size of vector to the same as Case 1 to form Case 4.*/
/*This case can prove the good performance of MemoryPool when allocating smaller blocks*/

template <class T>
using MyAllocator =std::allocator<T>;  // replace the std::allocator with your allocator
using Point2D = std::pair<int, int>;

const int TestSize = 30000;//Number of vector when creating; Range of vector resizing
const int PickSize = 10000;//Number of vector resizing

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, TestSize);

    /* The vector is departed into two parts, 
    however this time the size is not the memorypool management memory upper bound*/
    using IntVec = std::vector<int, MyAllocator<int> >;
    std::vector<IntVec, MyAllocator<IntVec> > vecints1(TestSize);
    for (int i = 0; i < TestSize; i++) vecints1[i].resize(128);

    std::vector<IntVec, MyAllocator<IntVec> > vecints2(TestSize);
    for (int i = 0; i < TestSize; i++) vecints2[i].resize(32);

     auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < PickSize; i++) {
        int idx = i;

        vecints1[idx].resize(64);//reduce the larger vector to 64 ints
                                // ensure that the free_list of memorypool recovers the free blocks of sufficient size and number
        vecints2[idx].resize(64);//enlarge the smaller vector to 64 ints
                                //the int block that has just been recovered happens to come in handy
    }
     auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds."
        << std::endl;

    return 0;
}
