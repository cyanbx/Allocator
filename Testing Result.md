[TOC]

# Test

The test is done on the MacOS Catalina Version 10.15.5 with processor of 2.4 GHz Quad-Core Intel Core i5 and memory 8 GB 2133 MHz LPDDR3. The translater is clang++ version 11.0.3 .All the original data are generated in the /Data file and all the graphs are in the /test/graph file.

## Extreme case test

The extreme case is a test example (TestExtreme) created specifically for the MemoryPool allocator mechanism.

By reasonably arranging the order and size of resize, a large number of memory blocks are recovered in time in the MemoryPool. Each time memory needs to be allocated, **<u>the memory can be directly called from the free_list without Malloc</u>**. This arrangement can reflect the characteristics of the memory pool to the greatest extent.

### Experimental conditions

* Int1

    * When creating a vector ,it is equally divided into two blocks, one block is larger, accounting for 128 int, and the other block only occupies 32 int. These two numbers are chosen because the 4 byte int puts 128 small block upper bounds that can be lower than memorypool management memory (here set to 1024 bytes). When resize, it can be handled by memorypool through the free_list mechanism.

    * When resizing, first reduce the larger vector to 64 ints, to **ensure that the free_list of memorypool recovers the free blocks of sufficient size and number**.

        Then enlarge the smaller vector to 64 ints. At this time, the **int block that has just been recovered  happens to come in handy**. memorypool directly reallocates the recovered memory to the resize vector, and there is **no repeated operation of** **malloc and free**, thus ensuring that the efficiency is greatly improved.

        

* Point2D

    * The pair class's member functions are stored distinctly from the objects, so theoretically every Point2D objects occupies the space of two int members.

    * When creating a Point2D ,it is equally divided into two blocks, one block is larger, accounting for 64 Point2D , and the other block only occupies 16 Point2D. 

    * When resizing , first reduce the larger vector to 32 Point2D, to **ensure that the free_list of memorypool recovers the free blocks of sufficient size and number**.

        Then enlarge the smaller vector to 32 Point2D



* Int2

    * At this time, we set the smallest block size in Memory Pool to 8 bytes, the Max_Bytes to 4096 to enlarge the memory pool size. 

    * When creating a vector, it is equally divided into two blocks, one block is larger, accounting for 1024 int, and the other block only occupies 256 int. 

    * When reisizing ,first reduce the larger list to 512 int, to **ensure that the free_list of memorypool recovers the free blocks of sufficient size and number**.

        Then enlarge the smaller list to 512 int

        

* Int3

    * Under the condition of Int2, we discover that the difference between malloc and memory_pool is not distinct. Even we find that malloc is faster than memory_pool

    * So we use the size in Int1, When creating a vector ,it is equally divided into two blocks, one block is larger, accounting for 128 int, and the other block only occupies 32 int. When resizing, first reduce the larger vector to 64 ints, to **ensure that the free_list of memorypool recovers the free blocks of sufficient size and number**.

        

### Results

|                 | Std::allocator | Malloc_alloc | MemoryPool_alloc |
| --------------- | -------------- | ------------ | ---------------- |
| Resize, int1    | 0.002894       | 0.002822     | 0.001427         |
| Resize, Point2D | 0.002911       | 0.002853     | 0.001739         |
| Resize, int2    | 0.016888       | 0.008885     | 0.009843         |
| Resize, int3    | 0.004952       | 0.004718     | 0.002473         |

* Resize_int1

    <img src="assets/extreme_resize_int1.png" alt="extreme_resize_int1" style="zoom:67%;" />

* Resize_Point2D

    <img src="assets/extreme_resize_Point2D.png" alt="extreme_resize_Point2D" style="zoom:67%;" />

* Resize_int2

    <img src="assets/extreme_resize_int2.png" alt="extreme_resize_int2" style="zoom:67%;" />

* Resize_int3

    <img src="assets/extreme_resize_int3.png" alt="extreme_resize_int3" style="zoom:67%;" />

### Analysis

From the test_graph above, we find that

* In Case1, the performance of memorypool is overwhelming due to its tailor-made characteristics. There is no repeated malloc() and free().

    

* Comparing Case2 and Case1, we find that the performance of MemoryPool is still better in average. However, the advantage is reducing. 

    We guess the reason is that Point2D object is not exactly the size of 2 ints, so when resizing the vector may exceeds  the upper bound of MemoryPool Block size. Under this circumstance, it needs to malloc() instead of using pool, which needs more time.

    

* In Case3, we enlarge the max size of MemoryPool Block and shrink the gap between blocks , so the List we maintain in our pool is getting longer. When we still use the MemoryPool management upper bound in testing, we find that the time consuming of MemoryPool and Malloc is nearly the same. Malloc is even slightly faster. 

    We guess the reason is that when the size of vector getting larger, the memory we need for resizing each vector is larger. Pool needs  more time for List operations, so it is slightly slower than Malloc.



* With the analysis of Case3, we reduce the reszing size of vector to the same as Case 1 to form Case 4. We can tell the advantage of using MemoryPool is obvious again, and the difference is getting larger than Case 1.

    The reason is that the smaller memory framentation can be used efficiently.

    

**Generally speaking, we find that the MemoryPool is doing a great job in resizing small size of memory, and the performance will get better if the Pool block is finely cut into small pieces.**

 **However, the best arrangement of Block size and Max size is different according to actual situation and still needs to be explored.**

## Given test

The test given by PTA (TestGiven.cpp) is a case with resize size radomly given in the range of TestSize( 1e4 ). 

### Experimental conditions

* Vector
    * Create: Create 1e4 vectors. The range of allocation is between [1, 1e4].
    * Resize: Radomly pick 1e3 vectors and each vector resizes in the range [1, 1e4].
* List
    * Create: Create 1e4 vectors. The range of allocation is between [1, 1e4].
    * Resize: Radomly pick 1e4 vectors and each vector resizes in the range [1, 1e4].

### Results

|                 | Std::allocator | Malloc_alloc | MemoryPool_alloc |
| :-------------- | -------------- | ------------ | ---------------- |
| Create, int     | 0.0925         | 0.092        | 0.0911           |
| Create, Point2D | 0.1751         | 0.1745       | 0.1805           |
| Resize, int     | 0.0511         | 0.0513       | 0.0489           |
| Resize, Point2D | 0.0998         | 0.0928       | 0.0961           |

* Create_int

    <img src="assets/given_create_int.png" alt="given_create_int" style="zoom:67%;" />

* Create_Point2D

    <img src="assets/given_create_Point2D.png" alt="given_create_Point2D" style="zoom:67%;" />

* Resize_int

    <img src="assets/given_resize_int.png" alt="given_resize_int" style="zoom:67%;" />

* Resize_Point2D

    <img src="assets/given_resize_Point2D.png" alt="given_resize_Point2D" style="zoom:67%;" />

### Analysis

From out test_graph above, we find that 

* It's hard to tell which allocator does the best job in create int or create Point2D. 

    * MemoryPool's performance is similar to that of Malloc, which implies that initially, MemoryPool itself has few free blocks in free_list, and most of them are allocated directly through malloc.

    * Std's performance is not distinctly great, we guess the reason is that the new() and other operations consume a lot of time in C++ compared with malloc() operation in C.

        

* When resizing ,the performance of MemoryPool is slightly better than the other two, but the advantage is not obvious.

    * When resizing, the size of the vector becomes larger and smaller randomly, the overall total memory basically remains the same, which is more in line with the efficient scenario of MemoryPool.  MemoryPool omits the work of free() and malloc() to the greatest extent, which improves efficiency and can effectively reduce the generation of memory fragments.
    * However, because of the radomly setting size, the MemoryPool may need to malloc() most of the time without using pool. So the difference is not very obvious.

## Usability test

Test if this allocator is usable in other containers.

### Experimental conditions

* List

    Create list with size 1e3

    Push_back ,sort operation test

* Deque

    Create Deque with size 1e4

    Push_front , front operation test

* Set

* Stack 

### Results

* List

    Pass

    <img src="assets/Screen Shot 2020-06-30 at 4.51.19 PM.png" alt="Screen Shot 2020-06-30 at 4.51.19 PM" style="zoom:50%;" />

    

* Deque 

    Pass

    <img src="assets/Screen Shot 2020-06-30 at 4.45.31 PM.png" alt="Screen Shot 2020-06-30 at 4.45.31 PM" style="zoom:50%;" />

* Set

    Pass

### Analysis

Our allocator is widely used in all kinds of container including associated container, sequential container and container adapter.



