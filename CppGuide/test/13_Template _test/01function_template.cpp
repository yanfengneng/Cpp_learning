#include <iostream>
using namespace std;

/* 函数模板 */
template <typename T>
T const& Max(T const& a, T const& b) {
  return a < b ? b : a;
}

int main() {
  int i = 39;
  int j = 20;
  // 编译到这一句时，编译器自动生成 int Max(int, int)函数，并调用
  cout << "Max(i, j): " << Max(i, j) << endl;

  double f1 = 13.5;
  double f2 = 20.7;
  // 编译到这句时，编译器自动生成 double Max(double, double)函数，并调用
  cout << "Max(f1, f2): " << Max(f1, f2) << endl;

  string s1 = "Hello";
  string s2 = "World";
  // 编译到这句时，编译器自动生成 string Max(string, string)函数，并调用
  cout << "Max(s1, s2): " << Max(s1, s2) << endl;

  cout << Max<float>(1.2, 3.4) << endl;
  return 0;
}
