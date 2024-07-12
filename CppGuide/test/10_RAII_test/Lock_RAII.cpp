#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class LockGuardRAII {
 public:
  // 构造函数，获取锁
  explicit LockGuardRAII(std::mutex& mtx) : mutex_(mtx) {
    mutex_.lock();
    std::cout << "Lock acquired\n";
  }

  // 析构函数，释放锁
  ~LockGuardRAII() {
    mutex_.unlock();
    std::cout << "Lock released\n";
  }

 private:
  std::mutex& mutex_;  // 引用传递的互斥锁
};

// 共享资源
int counter = 0;          // 计时器
std::mutex counterMutex;  // 用于保护共享资源

// 线程函数，增加计数器
void incrementCounter() {
  for (int i = 0; i < 10; ++i) {
    // 在 LockGuardRAII对象的生命周期内，锁被获取
    // 在循环结束或异常发生时，锁会被自动释放
    LockGuardRAII lock(counterMutex);  // 使用 RAII 技术管理锁
    ++counter;
    std::cout << "Counter: " << counter << "\n";
  }
}

int main() {
  std::vector<std::thread> threads;

  // 创建多个线程
  for (int i = 0; i < 5; ++i) {
    threads.emplace_back(incrementCounter);
  }

  // 等待所有线程完成
  for (auto& th : threads) {
    th.join();
  }

  std::cout << "Final counter value: " << counter << "\n";
  return 0;
}
