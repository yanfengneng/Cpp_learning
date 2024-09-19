#include <iostream>
using namespace std;

int main() {
  int a = 65;
  // 1. 在任意指针（或引用）类型之间的转换
  char* p = reinterpret_cast<char*>(&a);  // int* 转 char*
  std::cout << "char = " << *p << std::endl; // 打印字符 'A'

  // double *pd = reinterpret_cast<double*>(&a);
  // std::cout << "double = " << *pd << std::endl; // 输出：-nan
  // 报错了：丢失精度 cast from ‘char*’ to ‘int’ loses precision
  // int b = reinterpret_cast<int>(p);  // char* 转 int
  // std::cout << b << std::endl;  // 打印指针值（通常为内存地址）

  int *pv = &a;
  // 现在编译器已经不让这样转换了，会导致精度丢失，因此会报错
  // int pvaddr = reinterpret_cast<int>(pv);
  // std::cout << "pvaddr = " << hex << pvaddr << std::endl;
  std::cout << "pv = " << pv << endl;
  return 0;
}