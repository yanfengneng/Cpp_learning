#include <chrono>
#include <iostream>
#include <stop_token>
#include <thread>

// std::thread 示例
void thread_func() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "Thread completed (std::thread)\n";
}

// std::jthread 示例
void jthread_func(std::stop_token stoken) {
  while (!stoken.stop_requested()) {/* 直到线程请求停止操作了，才会跳出循环 */
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << "Working... (std::jthread)\n";
  }
  std::cout << "Thread stopped (std::jthread)\n";
}

/**
 * C++20 只有 g++10 编译器才支持，所以需要下载g++-10，使用以下命令进行编译运行！
 * sudo apt-get update
 * sudo apt-get install g++-10
 * g++-10 -o jthread.out -g jthread.cpp -std=c++20 -lpthread
 * ./jthread.out
 */
int main() {
  // 使用 std::thread
  std::thread t(thread_func);
  t.join();  // 手动 join

  // 使用 std::jthread
  std::jthread jt(jthread_func);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  jt.request_stop();  // 请求线程停止

  return 0;
}
