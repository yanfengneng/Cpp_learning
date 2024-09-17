#include <semaphore.h>

#include <iostream>
#include <thread>

sem_t sem;

void print(int num) {
  sem_wait(&sem);  // P 操作

  std::cout << "Thread " << num << " is printing." << std::endl;

  sem_post(&sem);  // V 操作
}

int main() {
  sem_init(&sem, 0, 1);  // 初始化信号量
  std::thread t1(print, 1);
  std::thread t2(print, 2);
  t1.join();
  t2.join();
  sem_destroy(&sem);  // 销毁信号量
  return 0;
}
