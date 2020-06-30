#include <iostream>
#include <random>
#include <set>
#include <cstdio>
#include <stdio.h>
#include "alloc_with_pool.h"

/*This is a test of usability of out allocator in set.*/

template<class T>
using MyAllocator = Allocator<T>; 

int main()
{
    using IntSet = std::set<int, std::less<int>, MyAllocator<int> >;
    typedef IntSet::iterator IT;
    IntSet setints;//create set with our allocator
    std::cout << sizeof(setints) << std::endl;

    return 0;
}