#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

int fun_int(int n) {
  std::this_thread::sleep_for(std::chrono::seconds(10));
  std::cout << "in fun_int n = " << n << std::endl;

  return 0;
}

int fun_string(const std::string& s) {
  std::this_thread::sleep_for(std::chrono::seconds(10));
  std::cout << "in fun_string s = " << s << std::endl;

  return 0;
}

int main() 
{
  std::vector<int> v;
  v.emplace_back(1);
  v.emplace_back(2);
  v.emplace_back(3);

  std::cout << v.size() << std::endl;

  std::thread t1(fun_int, 1); // 创建并启动子线程 t1
  std::thread t2(fun_string, "test");

  std::cout << "after thread create." << std::endl;
  t1.join();
  t2.join();
  return 0;
}