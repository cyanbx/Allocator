#include <iostream>
#include <random>
#include <vector>
#include "sample_allocator.h"


template<class T>
using MyAllocator = Allocator<T>; // replace the std::allocator with your allocator
using Point2D = std::pair<int, int>;

const int TestSize = 10000;
const int PickSize = 1000;
const int SmallSize = 100;

int main()
{
  freopen("Data_Big.txt", "a", stdout);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, TestSize);
  std::uniform_int_distribution<> dis_small(1, SmallSize);

  auto start = std::chrono::high_resolution_clock::now(); 
  // vector creation
  using IntVec = std::vector<int, MyAllocator<int> >;
  std::vector<IntVec, MyAllocator<IntVec> > vecints(TestSize);
  for (int i = 0; i < TestSize; i++)
    vecints[i].resize(dis(gen));
  auto end = std::chrono::high_resolution_clock::now();

  using PointVec = std::vector<Point2D, MyAllocator<Point2D> >;
  std::vector<PointVec, MyAllocator<PointVec> > vecpts(TestSize);
  for (int i = 0; i < TestSize; i++)
    vecpts[i].resize(dis(gen));

  // vector resize
  for (int i = 0; i < PickSize; i++)
  {
    int idx = dis(gen) - 1;
    int size = dis(gen);
    //vecints[idx].resize(size);
    vecpts[idx].resize(size);
  }
  


  // vector element assignment
  {
    int val = 10;
    int idx1 = dis(gen) - 1;
    int idx2 = vecints[idx1].size() / 2;
    vecints[idx1][idx2] = val;
    if (vecints[idx1][idx2] == val)
      std::cout << "correct assignment in vecints: " << idx1 << std::endl;
    else
      std::cout << "incorrect assignment in vecints: " << idx1 << std::endl;
  }
  {
    Point2D val(11, 15);
    int idx1 = dis(gen) - 1;
    int idx2 = vecpts[idx1].size() / 2;
    vecpts[idx1][idx2] = val;
    if (vecpts[idx1][idx2] == val)
      std::cout << "correct assignment in vecpts: " << idx1 << std::endl;
    else
      std::cout << "incorrect assignment in vecpts: " << idx1 << std::endl;
  }

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds."
              << std::endl;

  return 0;
  fclose(stdout);
}