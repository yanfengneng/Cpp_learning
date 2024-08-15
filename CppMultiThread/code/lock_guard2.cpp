#include <iostream>
#include <mutex>
#include <string_view>
// #include <syncstream>
#include <thread>

volatile int g_i = 0;
std::mutex g_i_mutex;  // 保护 g_i

void safe_increment(int iterations) {
  const std::lock_guard<std::mutex> lock(g_i_mutex);
  while (iterations-- > 0) g_i = g_i + 1;
  std::cout << "线程 #" << std::this_thread::get_id() << ", g_i: " << g_i
            << '\n';

  // g_i_mutex 在锁离开作用域时自动释放
}

void unsafe_increment(int iterations) {
  // 以下 g_i 自增，没加锁，会导致数据不一致的情况
  while (iterations-- > 0) g_i = g_i + 1;
  std::cout << "线程 #" << std::this_thread::get_id() << ", g_i: " << g_i
            << '\n';
}

int main() {
  auto test = [](std::string_view fun_name, auto fun) {
    g_i = 0;
    std::cout << fun_name << ":\n前, g_i: " << g_i << '\n';
    {
      // 使用 jthread 管理线程，则该作用域借宿，自动 join 来等待子线程执行完成
      // thread(函数名，参数值)
      std::thread t1(fun, 1'000'000);
      std::thread t2(fun, 1'000'000);

      t1.join();
      t2.join();
    }
    std::cout << "后, g_i: " << g_i << "\n\n";
  };
  test("safe_increment", safe_increment);
  test("unsafe_increment", unsafe_increment);
}