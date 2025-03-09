#include <iostream>
#include <memory>
#include <string>
#include <utility>  // for std::forward

/* 1.用完美转发实现委托构造函数 */
class MyString {
 public:
  // Args 是一个类型参数包，Args... 表示任意数量和类型的模板参数
  // args 是一个函数形参包，args... 表示任意数量和类型的函数形参
  // Args&&... args... 是一个万能引用，用于接收任意数量、任意类型的参数
  // std::forward<Args>(args)... 是一个展开包，表示将 args 中的参数完美转发给
  // _data
  template <typename... Args>
  MyString(Args&&... args) : _data(std::forward<Args>(args)...) {}

 private:
  std::string _data;
};

/* 2.用完美转发实现可变参数模板函数 */
// Func 是一个单一类型参数，Args...
// 是一个类型参数表，表示任意数量和类型的模板参数 args 是一个函数形参包，args...
// 表示任意数量和类型的函数形参 Func&& func
// 是一个万能引用，用于接收任意类型的函数对象 Args&&... args...
// 是一个万能引用，用于接收任意数量、任意类型的参数 std::forward<Args>(args)...
// 是一个展开包，表示将 args 中的参数完美转发给 func
// -> decltype(func(std::forward<Args>(args)...))：使用尾随返回类型（trailing
// return type）来指定返回类型。decltype(func(std::forward<Args>(args)...))
// 用于推导 func 调用后的返回类型。
template <typename Func, typename... Args>
auto bind_and_call(Func&& func, Args&&... args)
    -> decltype(func(std::forward<Args>(args)...)) {
  return func(std::forward<Args>(args)...);
}
int sum(int a, int b, int c) { return a + b + c; }

/* 3.用完美转发实现智能指针 */
// new T(std::forward<Args>(args)...)：使用 new 运算符创建一个 T
// 类型的对象，并将参数 args... 完美转发给 T 的构造函数。
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class MyClass {
 public:
  MyClass(int x, double y) : _x(x), _y(y) {}

 private:
  int _x;
  double _y;
};

int main() {
  MyString s1("hello");
  MyString s2(std::string("world"));
  MyString s3(5, 'a');

  std::cout << bind_and_call(sum, 1, 2, 3) << std::endl;

  auto p = make_unique<MyClass>(1, 2.0);

  return 0;
}