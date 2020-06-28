#include <iostream>
#include <random>
#include <vector>
#include <cstdio>
#include <chrono>
#include "test_alloc.h"
#include "sample_allocator.h"


template<class T>
using MyAllocator = Allocator<T>; // replace the std::allocator with your allocator
using Point2D = std::pair<int, int>;

const int TestSize = 300000;//����vector����;vector��resizeʱ�ķ�Χ
const int PickSize = 10000;//����resize����
const int SmallSize = 100;//�ڲ���С������ʱʹ�ã���ʾvector����resize�ķ�Χ

int main()
{
    freopen("Data_Big.txt", "a", stdout);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, TestSize);
    std::uniform_int_distribution<> dis_small(1, SmallSize);

    
    using IntVec = std::vector<int, MyAllocator<int>>;
    std::vector<IntVec, MyAllocator<IntVec>> vecints1(TestSize);
    for (int i = 0; i < TestSize; i++) vecints1[i].resize(128);

    std::vector<IntVec, MyAllocator<IntVec>> vecints2(TestSize);
    for (int i = 0; i < TestSize; i++) vecints2[i].resize(32);
    
    auto start = std::chrono::high_resolution_clock::now();
    // auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < PickSize; i++) {
        int idx = i;

        vecints1[idx].resize(64);
        vecints2[idx].resize(64);
    }
    // auto end = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds."
        << std::endl;

    return 0;
    fclose(stdout);
}