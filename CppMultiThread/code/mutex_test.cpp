#include <iostream>  // std::cout
#include <mutex>     // std::mutex
#include <thread>    // std::thread

std::mutex mtx;  // mutex for critical section

void print_block(int n, char c) {
  // critical section (exclusive access to std::cout signaled by locking mtx):
  mtx.lock();
  for (int i = 0; i < n; ++i) {
    std::cout << c;
  }
  std::cout << '\n';
  mtx.unlock();
}

int main() {
  std::thread th1(print_block, 50, '*');  // 线程1：打印*
  std::thread th2(print_block, 50, '$');  // 线程2：打印$

  th1.join(); // 运行线程 th1，直到 th1 运行结束才继续执行主线程
  th2.join(); // 运行线程 th2，直到 th2 运行结束才继续执行主线程

  return 0;
}
