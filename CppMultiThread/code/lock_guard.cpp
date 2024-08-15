#include <iostream>
#include <mutex>
#include <thread>

int g_i = 0;
std::mutex g_i_mutex;  // protects g_i，用来保护g_i

void safe_increment() {
  const std::lock_guard<std::mutex> lock(g_i_mutex);
  ++g_i;
  std::cout << std::this_thread::get_id() << ": " << g_i << '\n';
  // g_i_mutex自动解锁
}

int main() {
  std::cout << "main id: " << std::this_thread::get_id() << std::endl;
  std::cout << "main: " << g_i << '\n';

  std::thread t1(safe_increment);
  std::thread t2(safe_increment);

  // 子线程 t1 的资源在 join() 或 detach() 调用后才会被释放
  t1.join(); // 运行子线程 t1
  t2.join(); // 运行子线程 t2

  std::cout << "main: " << g_i << '\n';
}
