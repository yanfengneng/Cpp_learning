#include <iostream>

class Base {
 public:
  virtual void func() {}  // 必须有虚函数
};

class Derived : public Base {};

int main() {
  Base *base = new Derived();
  // 安全转换，成功，本质上还是派生类对象
  Derived *d1 = dynamic_cast<Derived *>(base);
  if (d1) {
    std::cout << "Cast successful." << std::endl;
  }

  Base *base2 = new Base();
  // Derived *d2 = (Derived*)base2; // 可以进行强转，但是是不安全的
  // 将基类使用 dynamic_cast 强转为派生类会失败，最后返回 nullptr
  Derived *d2 = dynamic_cast<Derived *>(base2);
  if (!d2) {
    std::cout << "Cast failed." << std::endl;
  }

  delete base;
  delete base2;
  return 0;
}