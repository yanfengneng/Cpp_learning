#include <iostream>

/* 左值是可以取地址的变量，右值是不能取地址的字面值、临时对象、即将销毁的对象 */
/* T& t = a; a 是左值，t 表示左值引用 */
template <typename T>
void print(T& t) {
  std::cout << "左值" << std::endl;
}

/* T&& t = 5; 5是不能取地址的字面值，其表示右值，则 t 表示右值引用， */
template <typename T>
void print(T&& t) {
  std::cout << "右值" << std::endl;
}

template <typename T>
void testForward(T&& v) {
  // 直接传递 v，此时 v 被视为左值（可以取地址的变量为左值）
  print(v);
  // 使用 std::forward<T> 进行完美转发 v，保留其原始值的类别（左值或右值）
  print(std::forward<T>(v));
  // 使用 std::move 进行右值转换，将左值转换为右值
  print(std::move(v));
}

int main() {
  testForward(1);
  std::cout << "======================" << std::endl;
  int x = 1;
  testForward(x);
  return 0;
}

/*
左值 ==> 在函数内部 v 被视为左值，因此输出 "左值"
右值 ==> std::forward 保持 v 的右值属性，因此输出 "右值"
右值 ==> std::move 将 v 转换为右值，因此输出 "右值"
======================
左值 ==> v 是左值，因此输出 "左值"
左值 ==> std::forward 保持 v 的左值属性，因此输出 "左值
右值 ==> std::move 将 v 转换为右值，因此输出 "右值"
*/
