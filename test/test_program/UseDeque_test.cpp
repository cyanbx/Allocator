#include <iostream>
#include <random>
#include <deque>
#include <cstdio>
#include <stdio.h>
#include "alloc_with_pool.h"

/*This is a test of usability of out allocator in deque.*/

template<class T>
using MyAllocator = Allocator<T>; 

const int TestSize = 10000;//Number of deque when creating


int main()
{
    using IntDeq = std::deque<int, MyAllocator<int> >;
    IntDeq deqints(TestSize);//create deque of size TestSize
    for (int i = 0; i < TestSize; i++)
        deqints.push_front(i);//push_front operation test

    std::cout << deqints.front() << std::endl;//front operation test

    return 0;
}