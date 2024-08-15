#include <chrono>              // std::chrono::seconds
#include <condition_variable>  // std::condition_variable, std::cv_status
#include <iostream>            // std::cout
#include <mutex>               // std::mutex, std::unique_lock
#include <thread>              // std::thread

std::condition_variable cv;

int value;

void read_value() {
  std::cin >> value;
  // 当用户输入整数并按下回车键之后，子线程通知条件变量 cv，解除主线程的阻塞状态
  cv.notify_one();
}

int main() {
  std::cout << "Please, enter an integer (I'll be printing dots): \n";
  std::thread th(read_value);  // 创建并启动线程

  std::mutex mtx;
  std::unique_lock<std::mutex> lck(mtx);
  // 超时就打印dots
  // 调用 cv.wait_for(lck, std::chrono::seconds(1))，等待条件变量 cv 在 1
  // 秒内被通知（通过 notify_one()）
  // 如果在 1 秒内没有收到通知（即 cv_status::timeout），while
  // 循环的条件为真，主线程会打印一个 "."（点）并再次等待
  while (cv.wait_for(lck, std::chrono::seconds(1)) == std::cv_status::timeout) {
    std::cout << '.' << std::endl;
  }
  std::cout << "You entered: " << value << '\n';

  th.join();  // 阻塞主线程，等待子线程执行完成

  return 0;
}
