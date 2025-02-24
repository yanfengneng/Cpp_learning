#include <mutex>
#include <thread>
#include <iostream>

std::mutex my_mu;

// 加锁
void thread1_func() {
  for (int i = 0; i < 5; ++i) {
    my_mu.lock();
    std::cout << "thread1 lock mutex succeed!" << std::endl;
    std::this_thread::yield();
  }
}

// 解锁
void thread2_func() {
  for (int i = 0; i < 5; ++i) {
    my_mu.unlock();
    std::cout << "thread2 unlock mutex succeed!" << std::endl;
    std::this_thread::yield();
  }
}

void simulateBlocking() {
  std::thread thread1(thread1_func);
  std::thread thread2(thread2_func);
  thread1.join();
  thread2.join();
}

int main() {
  simulateBlocking();
  return 0;
}