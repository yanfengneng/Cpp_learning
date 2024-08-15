#include <iostream>
#include <mutex>
#include <shared_mutex>
// #include <syncstream>
#include <thread>

class ThreadSafeCounter {
 public:
  ThreadSafeCounter() = default;

  // 多个线程/读者能同时读计数器的值。
  unsigned int get() const {
    // 读--共享
    std::shared_lock lock(mutex_);
    return value_;
  }

  // 只有一个线程/写者能增加/写计数器的值。
  void increment() {
    // 写--独占
    std::unique_lock lock(mutex_);
    ++value_;
  }

  // 只有一个线程/写者能重置/写计数器的值。
  void reset() {
    // 重置--独占
    std::unique_lock lock(mutex_);
    value_ = 0;
  }

 private:
  mutable std::shared_mutex mutex_;
  unsigned int value_{};
};

int main() {
  ThreadSafeCounter counter;

  // lambda 函数
  auto increment_and_print = [&counter]() {
    for (int i{}; i != 3; ++i) {
      counter.increment(); // 写线程
      // std::osyncstream确保了多个线程同时向同一个输出流（例如std::cout）写入时，数据不会交错，从而避免混乱输出
      std::cout << "id: " <<std::this_thread::get_id() << " count: " << counter.get() << '\n';
    }
  };

  std::thread thread1(increment_and_print);
  std::thread thread2(increment_and_print);

  thread1.join(); // 执行线程1
  thread2.join(); // 执行线程2

  return 0;
}
