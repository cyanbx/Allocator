#include <iostream>
#include <random>
#include <list>
#include <cstdio>
#include <stdio.h>
#include "alloc_with_pool.h"
#include "sample_allocator.h"


template<class T>
using MyAllocator = Allocator<T>; // replace the std::allocator with your allocator
using Point2D = std::pair<int, int>;

const int TestSize = 1000;//Number of list when creating

int main()
{
    // freopen("Use.txt", "a", stdout);
    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_int_distribution<> dis(1, TestSize);
    // std::uniform_int_distribution<> dis_small(1, SmallSize);

    // auto start = std::chrono::high_resolution_clock::now();
    // list creation
    using IntList = std::list<int, MyAllocator<int> >;
    IntList listints(TestSize);
    for (int i = 1000; i > 0;i--)
        listints.push_back(i);

    listints.sort();
    for (auto ii = listints.begin(); ii != listints.end(); ++ii)
        std::cout << *ii << std::endl;
    // for (auto i = 0; i < TestSize; i++)
    //     listints[i].resize(dis(gen));
    // auto end = std::chrono::high_resolution_clock::now();

    //     using PoIntList = std::list<Point2D,
    //     MyAllocator<Point2D>>;
    // std::list<PoIntList, MyAllocator<PoIntList> >
    // listpts(TestSize); for (int i = 0; i < TestSize; i++)
    //     vecpts[i].resize(dis(gen));

    // list resize
    // for (int i = 0; i < PickSize; i++) {
    //     int idx  = dis(gen) - 1;
    //     int size = dis(gen);
    //     //listints[idx].resize(size);
    //     vecpts[idx].resize(size);
    //}

    // list element assignment
    // {
    //   int val = 10;
    //   int idx1 = dis(gen) - 1;
    //   int idx2 = listints[idx1].size() / 2;
    //   listints[idx1][idx2] = val;
    //   if (listints[idx1][idx2] == val)
    //     std::cout << "correct assignment in listints: " << idx1
    //     << std::endl;
    //   else
    //     std::cout << "incorrect assignment in vecints: " << idx1
    //     << std::endl;
    // }
    // {
    //   Point2D val(11, 15);
    //   int idx1 = dis(gen) - 1;
    //   int idx2 = vecpts[idx1].size() / 2;
    //   vecpts[idx1][idx2] = val;
    //   if (vecpts[idx1][idx2] == val)
    //     std::cout << "correct assignment in vecpts: " << idx1 <<
    //     std::endl;
    //   else
    //     std::cout << "incorrect assignment in vecpts: " << idx1
    //     << std::endl;
    // }

    // std::chrono::duration<double> elapsed = end - start;
    // std::cout << "Elapsed time: " << elapsed.count() << " seconds."
    //           << std::endl;

    return 0;
    fclose(stdout);
}