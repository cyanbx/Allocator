# Allocator

A toy allocator for std::vector. Written for OOP course of ZJU.

----------------------------

* bin.sh为MacOS下使用clang++编译时的编译脚本。同时，我们也在test/test_program文件夹下提供了.exe程序，便于在windows环境下测试。

* include文件夹包含实现allocator的头文件。
  * alloc_with_pool.h为本次设计的使用Memory Pool的allocator
  * sample_allocator.h为测试使用的对 `new` 和 `delete` 进行封装的测试用allocator
* test文件夹包含本次测试用程序
  * test_program为测试allocator的程序代码和.exe文件
  * graph_program为绘制测试结果折线图的Python代码
* Data文件夹中为测试程序输出的数据
* bin文件夹中包含MacOS下测试代码编译成的可执行文件
* report.pdf为实验报告 （已移除）

