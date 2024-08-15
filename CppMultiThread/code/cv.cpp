#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [] { return ready; });  // 等待 ready 为 true
  std::cout << "Thread " << id << std::endl;
}

void set_ready() {
  std::unique_lock<std::mutex> lock(mtx);
  ready = true;
  cv.notify_all();  // 通知所有等待的线程
}

int main() {
  std::thread t1(print_id, 1);
  std::thread t2(print_id, 2);

  std::this_thread::sleep_for(std::chrono::seconds(1));
  set_ready();  // 设置 ready 并通知线程

  t1.join();
  t2.join();

  return 0;
}
