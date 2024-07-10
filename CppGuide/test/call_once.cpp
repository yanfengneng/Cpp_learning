#include <iostream>
#include <mutex>
#include <thread>

/* std::once_flag：用于标记是否已经调用过 */
std::once_flag initFlag;

void initialize() { std::cout << "Initialized." << std::endl; }

void worker() {
  /* std::call_once: 用于执行一次性初始化操作 */
  std::call_once(initFlag, initialize);
  std::cout << "Worker is running." << std::endl;
}

int main() {
  /* 无论多少个线程调用 worker() 函数，initialize() 函数只会被执行一次 */
  std::thread t1(worker);
  std::thread t2(worker);
  std::thread t3(worker);

  t1.join();
  t2.join();
  t3.join();

  return 0;
}
