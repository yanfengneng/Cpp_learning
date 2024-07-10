#include <iostream>
#include <mutex>
#include <thread>

class Singleton {
 public:
  static Singleton& getInstance() {
    /* 使用std::call_once 来保证只创建一次实例对象 */
    std::call_once(initFlag, []() { instance.reset(new Singleton); });
    return *instance;
  }

  void print() {
    std::cout << "Singleton instance address: " << this << std::endl;
  }
  ~Singleton() { std::cout << "Singleton Destructor." << std::endl; }

 private:
  Singleton() { std::cout << "Singleton Constructor." << std::endl; }

  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

  static std::unique_ptr<Singleton> instance;
  static std::once_flag initFlag;
};

std::unique_ptr<Singleton> Singleton::instance;
std::once_flag Singleton::initFlag;

void worker() { Singleton::getInstance().print(); }

int main() {
  std::thread t1(worker);
  std::thread t2(worker);
  std::thread t3(worker);

  t1.join();
  t2.join();
  t3.join();

  return 0;
}
