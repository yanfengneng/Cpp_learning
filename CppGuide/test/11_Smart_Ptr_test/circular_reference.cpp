#include <iostream>
#include <memory>
#include <functional>

class B;

class A {
 public:
  std::shared_ptr<B> b_ptr;
  ~A() { std::cout << "A destroyed." << std::endl; }
};

class B {
 public:
  // std::shared_ptr<A> a_ptr;
  std::weak_ptr<A> a_ptr;  // 使用 weak_ptr 避免循环引用
  ~B() { std::cout << "B destroyed." << std::endl; }
};

int main() {
  {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();

    a->b_ptr = b;
    b->a_ptr = a;
    // 此时 a 和 b 相互引用，a 持有 b 的 shared_ptr，b 持有 a 的 weak_ptr
    std::cout << a.use_count() << " " << b.use_count() << std::endl;
  }

  // 此处 a 和 b 应该被销毁，但由于循环引用，析构函数不会被调用
  std::cout << "End of main\n";
  // std::cout << sizeof(int*) << std::endl; // 输出 8
  // std::cout << sizeof(std::unique_ptr<int>) << std::endl; // 输出 8
  // std::cout << sizeof(std::unique_ptr<FILE, std::function<void(FILE*)>>)
  //           << std::endl;  // 输出 40

  // std::cout << sizeof(std::shared_ptr<int>) << std::endl;  // 输出 16
  std::shared_ptr<FILE> sptr(fopen("test_file.txt", "w"), [](FILE* fp) {
    std::cout << "close " << fp << std::endl;
    fclose(fp);
  });
  // std::cout << sizeof(sptr) << std::endl;  // 输出 16
  return 0;
}
