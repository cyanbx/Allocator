#include <iostream>
#include <random>
#include <set>
#include <cstdio>
#include <stdio.h>
#include "alloc_with_pool.h"
#include "sample_allocator.h"


template<class T>
using MyAllocator = Allocator<T>; // replace the std::allocator with your allocator
using Point2D = std::pair<int, int>;

const int TestSize = 10000;//创建set个数;set在resize时的范围
const int PickSize = 10000;//进行resize次数
const int SmallSize = 100;//在测试小数据量时使用，表示set进行resize的范围

int main()
{
    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_int_distribution<> dis(1, TestSize);
    // std::uniform_int_distribution<> dis_small(1, SmallSize);

    // set creation
    using IntSet = std::set<int, MyAllocator<int> >;
    std::set<IntSet, MyAllocator<IntSet> > setints;
    printf("%d", sizeof(setints));

    // set resize
    // for (int i = 0; i < PickSize; i++) {
    //     int idx  = dis(gen) - 1;
    //     int size = dis(gen);
    //     //vecints[idx].resize(size);
    //     vecpts[idx].resize(size);
    // }



  // set element assignment
  // {
  //   int val = 10;
  //   int idx1 = dis(gen) - 1;
  //   int idx2 = vecints[idx1].size() / 2;
  //   vecints[idx1][idx2] = val;
  //   if (vecints[idx1][idx2] == val)
  //     std::cout << "correct assignment in vecints: " << idx1 << std::endl;
  //   else
  //     std::cout << "incorrect assignment in vecints: " << idx1 << std::endl;
  // }
  // {
  //   Point2D val(11, 15);
  //   int idx1 = dis(gen) - 1;
  //   int idx2 = vecpts[idx1].size() / 2;
  //   vecpts[idx1][idx2] = val;
  //   if (vecpts[idx1][idx2] == val)
  //     std::cout << "correct assignment in vecpts: " << idx1 << std::endl;
  //   else
  //     std::cout << "incorrect assignment in vecpts: " << idx1 << std::endl;
  // }

    // std::chrono::duration<double> elapsed = end - start;
    // std::cout << "Elapsed time: " << elapsed.count() << " seconds."
    //           << std::endl;

    return 0;
}