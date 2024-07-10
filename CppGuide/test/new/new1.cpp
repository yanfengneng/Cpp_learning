#include <iostream>
#include <new>  // std::bad_alloc

int main() {
  long long num =
      0x7fffffff;  // 0x7fffffff = 2,147,483,647 = 2047*1024*1024 = 2047M
  char *p = nullptr;

  try {
    // vs2015 x86 error C2148: 数组的总大小不得超过 0x7fffffff 字节
    // 使用 new 来申请内存分配时，分配异常会报 bad_alloc
    // 的异常，而且此时申请内存分配的指针 p 不为空
    p = new char[2047 * 1024 * 1024];  /// 1024 * 1024 * 1024
  } catch (std::bad_alloc &ba) {
    std::cerr << "bad_alloc caught: " << ba.what()
              << '\n';  // bad_alloc caught: bad allocation
  }
  delete[] p;
  return 0;
}