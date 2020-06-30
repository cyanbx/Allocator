#include <iostream>
#include <random>
#include <set>
#include <queue>
#include <stack>
#include <cstdio>
#include <stdio.h>
#include "alloc_with_pool.h"

/*This is a test of usability of out allocator in Stack.*/

template<class T>
using MyAllocator = Allocator<T>; 

  const int TestSize = 1000;//Number of stack members when creating

int main()
{
    using IntDeq = std::deque<int, MyAllocator<int> >;
    using IntStack = std::stack<int, IntDeq>;
    IntStack staints;//create stack with our allocator
    for (int i = 0; i < TestSize;i++)
        staints.push(i);//push operation test
    std::cout << staints.top() << std::endl;//top operation test

    return 0;
}