#include <chrono>
#include <iostream>
#include <thread>

int main() {
  using namespace std::chrono_literals;

  std::cout << "你好，等待者\n" << std::flush;

  const auto start = std::chrono::high_resolution_clock::now();
  std::this_thread::sleep_for(2000ms);
  const auto end = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<double, std::milli> elapsed = end - start;

  std::cout << "等待了 " << elapsed.count() <<  " ms\n";
}

/*
运行结果：
你好，等待者
等待了 2000.21 ms
*/
