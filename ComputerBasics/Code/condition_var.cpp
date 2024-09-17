#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print(int num) {
  std::unique_lock<std::mutex> lock(mtx);
  // 调用 wait 之后，该线程被阻塞，互斥锁被释放，允许其他线程获得互斥锁，但是其他线程也会陷入等待
  while (!ready) {
    cv.wait(lock);
  }
  std::cout << "Thread " << num << " is printing." << std::endl;
}

int main() {
  std::thread t1(print, 1); // 创建线程并立即执行
  std::thread t2(print, 2); // 创建线程并立即执行
  std::this_thread::sleep_for(std::chrono::seconds(1));
  ready = true;
  cv.notify_all(); // 唤醒等待该条件变量的所有线程
  t1.join();
  t2.join(); 
  return 0;
}