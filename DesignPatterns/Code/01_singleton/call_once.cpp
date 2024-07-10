#include <iostream>
#include <memory>
#include <mutex>

class Singleton {
 public:
  static std::shared_ptr<Singleton> getSingleton();

  void print() { std::cout << "Hello World." << std::endl; }

  ~Singleton() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

 private:
  Singleton() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  // 禁止拷贝和赋值操作
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
};

static std::shared_ptr<Singleton> singleton = nullptr;
static std::once_flag singletonFlag;

int main() {
  std::shared_ptr<Singleton> s = Singleton::getSingleton();
  s->print();
  return 0;
}
std::shared_ptr<Singleton> Singleton::getSingleton() {
  // 用来保证线程安全的，只被执行一次
  std::call_once(singletonFlag, [] {
    singleton = std::shared_ptr<Singleton>(new Singleton());
    // singleton.reset(new Singleton());
  });
  return singleton;
}
