#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_thread_id(int id) {
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [] { return ready; });

  std::cout << "Thread " << id << std::endl;
}

void set_ready() {
  {
    std::lock_guard<std::mutex> lock(mtx);
    ready = true;
  }
  cv.notify_all();
}

int main() {
  std::thread t1(print_thread_id, 1);
  std::thread t2(print_thread_id, 2);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  set_ready();

  t1.join();
  t2.join();

  return 0;
}

/*
运行结果：
Thread 1
Thread 2
*/