#include <iostream>
#include <mutex>
#include <thread>

std::recursive_mutex rm;
int count = 0;

void recursive_function(int loop_count) {
  if (loop_count <= 0) return;

  rm.lock();  // 加锁
  std::cout << "Lock acquired: " << ++count << " times\n";

  // 递归调用，进一步加锁
  recursive_function(--loop_count);

  rm.unlock();  // 解锁
  std::cout << "Lock released: " << count-- << " times\n";
}

int main() {
  std::thread t1(recursive_function, 5);
  t1.join();
  return 0;
}
