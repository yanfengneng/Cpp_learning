#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void print(int num) {
  mtx.lock();
  std::cout << "Thread " << num << " is printing." << std::endl;
  mtx.unlock();
}

int main() {
  std::thread t1(print, 1);  // 创建线程就立即开始执行
  std::thread t2(print, 2);  // 创建线程就立即开始执行

  t1.join();  // 阻塞主线程，等待该子线程执行完成
  t2.join();  // 阻塞主线程，等待该子线程执行完成
  return 0;
}