[TOC]

## BigSize

### 实验条件

* vector create过程，创建vector数量N=1e4，每一vector分配的范围在[1，1e4]之间。
* vector resize过程，resize 1e3次，每一vector进行resize的大小范围在[1, 1e4]之间。

### 实验结果

所有测试经历过10次重复测试取平均，具体数据见\Data\Data_Big.txt

* Create

    |                | Std::allocator | Malloc_alloc | MemoryPool_alloc |
    | -------------- | :------------: | :----------: | :--------------: |
    | Create,int     |                |              |                  |
    | Create,point2D |                |              |                  |
    | Resize,int     |                |              |                  |
    | Resize,point2D |                |              |                  |

* Resize

### 结果分析



## SmallSize

### 实验条件

* vector create过程，创建vector数量N=1e4，每一vector分配的范围在[1，1e4]之间。
* vector resize过程，每一vector进行resize的大小范围在[1, 100]之间。

### 实验结果

### 结果分析



## extreme scenario

### 实验条件

### 实验结果

### 结果分析

