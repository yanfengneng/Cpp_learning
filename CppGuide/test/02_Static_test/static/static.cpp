#include "static.h"

using namespace std;

// void print()
// {
//   cout << ".cpp test." << endl;
// }

class A {
 public:
  // 报错：静态成员变量不能在类中进行初始化，只能进行声明
  // static int a = 1;
  static int a;
  // 报错：error: member ‘fun’ cannot be declared both ‘virtual’ and ‘static’
  // virtual static void fun() {}
  // static void funA() const() {}
};

// int A::a = 1;
// 定义
int A::a; // 不赋初始值，则进行默认初始化为0

class B
{
public:
  /* 编译器将其转换为一个外部的、非成员的、普通的函数 */
  /* this做为隐式参数传递给函数fun() */
  /* void fun1(const B* const this)*/
  void fun1() const {};
  /* void fun2(volatile B* const this) */
  void fun2() volatile {};
  /* void fun2(const volatile B* const this) */
  void fun3() const volatile {};
};

int main() {
  cout << gloab_var << endl;
  cout << A::a << endl;
  print();
  return 0;
}
