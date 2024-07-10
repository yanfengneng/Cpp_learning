#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void print_thread_id(int id) {
  std::lock_guard<std::mutex> guard(mtx);
  std::cout << "Thread " << id << std::endl;
}

int main() {
  std::thread t1(print_thread_id, 1);
  std::thread t2(print_thread_id, 2);

  t1.join();
  t2.join();

  return 0;
}

/*
运行结果：
Thread 1
Thread 2
*/