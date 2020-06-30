#include <iostream>
#include <random>
#include <vector>
#include <cstdio>
#include <chrono>
#include "alloc_with_pool.h"
#include "sample_allocator.h"

/* In this testing case, we set the smallest block size in Memory Pool to 8 bytes, 
the Max_Bytes to 4096 to enlarge the memory pool size. */
/* Compared with Case1, this case is testing for smaller block arrangement.*/

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

    using IntDeq = std::vector<int, MyAllocator<int> >;
    std::vector<IntDeq, MyAllocator<IntDeq> > vecints1(TestSize);
    for (int i = 0; i < TestSize; i++) vecints1[i].resize(1024);//one block is larger, accounting for 1024 int

    std::vector<IntDeq, MyAllocator<IntDeq> > vecints2(TestSize);
    for (int i = 0; i < TestSize; i++) vecints2[i].resize(256);//the other block only occupies 256 int
    /* The two numbers are chosen because the 4 byte int puts 1024 small block upper bounds that can be lower than memorypool management memory (here set to 4096 bytes)*/

     auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < PickSize; i++) {
        int idx = i;

        vecints1[idx].resize(512);//reduce the larger vector to 512 ints
                                // ensure that the free_list of memorypool recovers the free blocks of sufficient size and number
        vecints2[idx].resize(512);//enlarge the smaller vector to 512 ints
                                //the int block that has just been recovered happens to come in handy
    }
     auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds."
        << std::endl;

    return 0;
}
