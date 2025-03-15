#include <bits/stdc++.h>
using namespace std;

// MyClass.h
class MyClass {
 public:
  void func1();
  void func2();

 private:  // private中表示不想暴露出去的函数或字段
  class Impl;
  std::shared_ptr<Impl> impl_;
};

MyClass::Impl {
 public:
  void func1();
  void func2();

 private:
  int a;
  int b;
  void func3();
  void func4();
};

// MyClass.cpp
MyClass::MyClass() : impl_(make_shared<Impl>()) {}
MyClass::~MyClass() = default;

// 实现接口与实现的分离
void MyClass::func1() { impl_->func1(); }
void MyClass::func2() { impl_->func2(); }

// MyClassImpl.h
// 将类的实现细节隐藏起来，只暴露必要的接口给用户
void MyClass::
    Impl::func1() { cout << "func1" << endl; }
void MyClass::
    Impl::func2() { cout << "func2" << endl; }
void MyClass::
    Impl::func3() { cout << "func3" << endl; }
void MyClass::
    Impl::func4() { cout << "func4" << endl; }
MyClass::Impl::Impl() : a(0), b(0) {}
MyClass::Impl::~Impl() = default;

int main()
{
  return 0;
}