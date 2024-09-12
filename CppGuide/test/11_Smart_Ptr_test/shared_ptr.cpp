#include <iostream>
#include <memory>
#include <string>

class Test {
 private:
  std::string _str;

 public:
  Test(std::string str) : _str(str) {
    std::cout << "Test create." << std::endl;
  }
  ~Test() { std::cout << "Test delete" << std::endl; }
  std::string &getStr() { return _str; }
  void setStr(std::string s) { _str = s; }

  void print() { std::cout << _str << std::endl; }
};

void fun() {
  // 使用 make_shared 创建空对象
  std::shared_ptr<int> p1 = std::make_shared<int>();
  *p1 = 78;
  std::cout << "p1 = " << *p1 << std::endl;  // 输出78

  // 打印引用个数：1
  std::cout << "p1 Reference count = " << p1.use_count() << std::endl;

  // 第2个 shared_ptr 对象指向同一个指针
  std::shared_ptr<int> p2(p1);

  // 下面两个输出都是：2
  std::cout << "p2 Reference count = " << p2.use_count() << std::endl;
  std::cout << "p1 Reference count = " << p1.use_count() << std::endl;

  // 比较智能指针，p1 等于 p2
  if (p1 == p2) {
    std::cout << "p1 and p2 are pointing to same pointer\n";
  }

  std::cout << "Reset p1 " << std::endl;

  // 无参数调用reset，无关联指针，引用个数为0
  p1.reset();
  std::cout << "p1 Reference Count = " << p1.use_count() << std::endl;

  // 带参数调用reset，引用个数为1
  p1.reset(new int(11));
  std::cout << "p1  Reference Count = " << p1.use_count() << std::endl;

  // 把对象重置为NULL，引用计数为0
  p1 = nullptr;
  std::cout << "p1  Reference Count = " << p1.use_count() << std::endl;
  if (!p1) {
    std::cout << "p1 is NULL" << std::endl;  // 输出
  }
}

int main() {
  std::shared_ptr<Test> p1 = std::make_shared<Test>("hello world!");
  fun();
  return 0;
}