#include <chrono>
#include <iostream>
#include <thread>

// 建议其他线程运行一小段时间的“忙睡眠”
void little_sleep(std::chrono::microseconds us/* 微妙 */) {
  auto start = std::chrono::high_resolution_clock::now();
  auto end = start + us;
  do {
    std::this_thread::yield();
  } while (std::chrono::high_resolution_clock::now() < end);
}

int main() {
  // 获得当前时间
  auto start = std::chrono::high_resolution_clock::now();

  // 等待 100 微妙
  little_sleep(std::chrono::microseconds(100));

  // 计算时间间隔
  auto elapsed = std::chrono::high_resolution_clock::now() - start;
  std::cout
      << "等待 "
      << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
      << " 微秒\n";
  return 0;
}