#include <iostream>
#include <mcheck.h>  // 包含 mtrace 所需的头文件

void memoryLeakExample() {
  int* leakArray = new int[100];  // 动态分配内存
  for (int i = 0; i < 100; ++i) {
    leakArray[i] = i;
  }

  std::cout << "Array values: " << leakArray[0] << ", " << leakArray[99]
            << std::endl;

  // 忘记释放内存，导致泄漏
  // delete[] leakArray;  // 如果加上这一行，就不会有内存泄漏了
}

int main() {
  mtrace();  // 启用内存跟踪
  memoryLeakExample();
  return 0;
}
