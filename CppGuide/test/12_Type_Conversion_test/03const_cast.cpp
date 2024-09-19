#include <iostream>
using namespace std;

void func(const int *p) {
  int *modifiable = const_cast<int *>(p);  // 移除 const 属性
  *modifiable = 20;                        // 修改值
}

int main() {
  const int a = 10;
  func(&a);  // 虽然不推荐，但这是 const_cast 的用途之一
  // 输出编译时确定的值 10，但是实际运行时已经被改变为 20 了
  std::cout << a << std::endl;  // a 的值在未定义行为的情况下可能会改变

  int val = 100;
  // 定义一个常量指针
  const int *cpi = &val;
  // *cpi = 20; // 不通过常量指针来修改指向的值

  // 1. 将常量指针转换为非常量指针，然后就可以修改指针所指向变量的值了
  int *p1 = const_cast<int *>(cpi);
  // 修改过后：val, *cpi, *p1 的值都为 200 了
  *p1 = 200;
  cout << val << " " << *p1 << " " << val << endl;  // 输出：200 200 200

  // 2. 将非常量指针转换为常量指针
  const int *cpi2 = const_cast<const int *>(p1);

  const int val1 = 500;
  const int &c_val1 = val1;  // 定义一个常量引用

  // 3. 将常量引用转换为非常量引用
  int &r_val1 = const_cast<int &>(c_val1);
  cout << r_val1 << endl;
  // 修改过后：c_val1, r_val1, val1 的值都为 20 了
  r_val1 = 20;
  cout << r_val1 << " " << c_val1 << " " << val1 << endl;  // 输出：20 20 500

  // 4. 将非常量引用转换为常量引用
  const int &c_val2 = const_cast<const int &>(r_val1);
  cout << c_val2 << endl;
  return 0;
}