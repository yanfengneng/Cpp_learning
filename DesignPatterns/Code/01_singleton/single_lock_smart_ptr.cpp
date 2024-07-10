#include <iostream>
#include <memory>
#include <mutex>

using namespace std;
class Singleton {
 public:
  static std::shared_ptr<Singleton> getSingleton();

  void print() { std::cout << "Hello World." << std::endl; }

  /* 因为该单例对象是在类外析构，所以析构函数需要声明为 public 的 */
  ~Singleton() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

 private:
  Singleton() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

/* 静态全局变量 */
static std::shared_ptr<Singleton> singleton = nullptr;
static std::mutex singletonMutex;

std::shared_ptr<Singleton> Singleton::getSingleton() {
  if (singleton == nullptr) {
    // std::unique_lock<std::mutex> lock(singletonMutex);
    // std::lock_guard: 是一个简单的、RAII
    // 风格的锁类，它在构造时锁定互斥锁，并在析构时自动释放锁。
    // 它适用于锁定范围明确且不需要手动控制锁状态的场景。
    // std::lock_guard:
    // 只能在构造时锁定互斥锁，析构时自动释放锁；而且没有其他开销
    // std::unique_lock: 
    // 是一个更灵活的锁类，它提供了更多的功能和控制选项。除了基本的锁定和解锁外，它还支持延迟锁定、尝试锁定和锁的转移等操作。
    lock_guard<mutex> lock(singletonMutex);  // 使用lock_guard简化锁操作
    if (singleton == nullptr) {
      // 使用 volatile 关键字编译会报错
      // 在 C++ 中，volatile
      // 关键字用于指示对象的状态可以在没有明显方式的情况下被改变，通常用于硬件访问或多线程编程中，以告知编译器不应优化涉及这些对象的代码。
      // 而此时将将一个带有 volatile 修饰符的 std::shared_ptr 赋值给一个普通的
      // std::shared_ptr，编译不通过。 volatile auto temp =
      // std::shared_ptr<Singleton>(new Singleton());
      auto temp = std::shared_ptr<Singleton>(new Singleton());

      singleton = temp;
    }
  }
  return singleton;
}
int main() {
  std::shared_ptr<Singleton> s1 = Singleton::getSingleton();
  s1->print();
  return 0;
}
