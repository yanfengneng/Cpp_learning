#include <chrono>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

std::mutex cout_mutex;  // 控制到 std::cout 的访问
std::timed_mutex mutex;  // 用于控制共享资源的访问，带超时功能的互斥锁

void job(int id) {
  std::ostringstream stream;

  /**
   * 线程尝试三次锁定 mutex，若在 100ms 内锁定成功，则 stream 记录成功
   */
  for (int i = 0; i < 3; ++i) {
    if (mutex.try_lock_for(100ms)) {
      stream << "成功 ";
      // 保持锁定 100ms，然后进行解锁
      std::this_thread::sleep_for(100ms);
      mutex.unlock();
    } else
      stream << "失败 ";

    std::this_thread::sleep_for(100ms);
  }

  // 锁定 cout_mutex，确保在将结果输出到 cout 时，不会与其他线程的输出交错
  std::lock_guard<std::mutex> lock{cout_mutex};
  std::cout << "[" << id << "] " << stream.str() << "\n";
}

int main() {
  std::vector<std::thread> threads;  // 线程数组
  // 通过循环创建了 4 个线程，每个线程都执行 job 函数
  for (int i = 0; i < 4; ++i) {
    threads.emplace_back(job, i);
  }

  // 使用 i.join() 等待每个线程完成执行，确保主线程在所有子线程执行完毕后才退出
  for (auto& i : threads) {
    i.join();
  }
  return 0;
}