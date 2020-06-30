#include <iostream>
#include <random>
#include <list>
#include <cstdio>
#include <stdio.h>
#include "alloc_with_pool.h"

/*This is a test of usability of out allocator in list.*/

template<class T>
using MyAllocator = Allocator<T>; 

const int TestSize = 1000;//Number of list when creating

int main()
{
    using IntList = std::list<int, MyAllocator<int> >;
    IntList listints(TestSize);//create list of size TestSize
    for (int i = 1000; i > 0;i--)
        listints.push_back(i);//push_back operation test

    listints.sort();//sort operation test
    for (auto ii = listints.begin(); ii != listints.end(); ++ii)//iterator test
        std::cout << *ii << std::endl;

    return 0;
}