#include <bits/stdc++.h>
using namespace std;

class Array {
 private:
  int data[10];

 public:
  // 返回引用，允许修改数组元素
  int& operator[](int index) { return data[index]; }
};

class Printer {
 public:
  Printer& print(const std::string& msg) {
    std::cout << msg;
    return *this;
  }
};

int main() {
  // 通过引用完成链式调用
  Printer().print("Hello ").print("World!");

  // Array a;
  // // 通过引用直接修改 data[3]
  // cout << (a[3] = 42) << endl;
  return 0;
}