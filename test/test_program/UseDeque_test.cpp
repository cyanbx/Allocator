#include <iostream>
#include <random>
#include <deque>
#include <cstdio>
#include <stdio.h>
#include "alloc_with_pool.h"


template<class T>
using MyAllocator = std::allocator<T>; // replace the std::allocator with your allocator
using Point2D = std::pair<int, int>;

const int TestSize = 10000;//Number of deque when creating


int main()
{
    // freopen("Given.txt", "a", stdout);
    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_int_distribution<> dis(1, TestSize);
    // std::uniform_int_distribution<> dis_small(1, SmallSize);

    // deque creation
    using IntDeq = std::deque<int, MyAllocator<int> >;
    IntDeq deqints(TestSize);
    for (int i = 0; i < TestSize; i++)
        deqints.push_front(i);

    std::cout << deqints.front() << std::endl;

    // auto start = std::chrono::high_resolution_clock::now();

    // using PoIntDeq = std::deque<Point2D, MyAllocator<Point2D> >;
    // std::deque<PoIntDeq, MyAllocator<PoIntDeq> > deqpts(TestSize);
    // for (int i = 0; i < TestSize; i++)
    //     deqpts[i].resize(dis(gen));

    // auto end = std::chrono::high_resolution_clock::now();

    // deque resize
    // for (int i = 0; i < PickSize; i++) {
    //     int idx  = dis(gen) - 1;
    //     int size = dis(gen);
    //     // deqints[idx].resize(size);
    //     deqpts[idx].resize(size);
    //     }



  // deque element assignment
  // {
  //   int val = 10;
  //   int idx1 = dis(gen) - 1;
  //   int idx2 = deqints[idx1].size() / 2;
  //   deqints[idx1][idx2] = val;
  //   if (deqints[idx1][idx2] == val)
  //     std::cout << "correct assignment in deqints: " << idx1 << std::endl;
  //   else
  //     std::cout << "incorrect assignment in deqints: " << idx1 << std::endl;
  // }
  // {
  //   Point2D val(11, 15);
  //   int idx1 = dis(gen) - 1;
  //   int idx2 = deqpts[idx1].size() / 2;
  //   deqpts[idx1][idx2] = val;
  //   if (deqpts[idx1][idx2] == val)
  //     std::cout << "correct assignment in deqpts: " << idx1 << std::endl;
  //   else
  //     std::cout << "incorrect assignment in deqpts: " << idx1 << std::endl;
  // }

    // std::chrono::duration<double> elapsed = end - start;
    // std::cout << "Elapsed time: " << elapsed.count() << " seconds."
    //           << std::endl;

    return 0;
    // fclose(stdout);
}