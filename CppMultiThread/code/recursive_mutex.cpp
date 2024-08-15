#include <iostream>
#include <mutex>
#include <thread>

class X {
 private:
  std::recursive_mutex m;
  std::string shared;

 public:
  void fun1() {
    std::lock_guard<std::recursive_mutex> lk(m);
    shared = "fun1";
    std::cout << "fun1 中，共享变量现在为 " << shared << '\n';
  }
  void fun2() {
    std::lock_guard<std::recursive_mutex> lk(m);
    shared = "fun2";
    std::cout << "fun2 中，共享变量现在为 " << shared << '\n';
    fun1();  // 递归锁在此处变得有用
    std::cout << "回到 fun2, 共享变量为 " << shared << '\n';
  };
};

int main() {
  X x;
  std::thread t1(&X::fun1, &x);
  std::thread t2(&X::fun2, &x);
  t1.join();
  t2.join();
}

/*
运行结果：
fun1 中，共享变量现在为 fun1
fun2 中，共享变量现在为 fun2
fun1 中，共享变量现在为 fun1
回到 fun2, 共享变量为 fun1
*/