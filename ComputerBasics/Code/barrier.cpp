#include <barrier>
#include <iostream>
#include <thread>

std::barrier bar(2);

void print(int num) {
  std::cout << "Thread " << num << " is waiting." << std::endl;
  // 让多个线程在这个点上等待，直到所有的线程都到达这个点后才继续执行
  bar.wait(); 
  std::cout << "Thread " << num << " is printing." << std::endl;
}

int main() {
  std::thread t1(print, 1);
  std::thread t2(print, 2);
  t1.join();
  t2.join();
  return 0;
}
