#include <iostream>
#include <thread>
using namespace std;

void thread_1() { cout << "子线程1" << endl; }

void thread_2(int x) {
  cout << "x:" << x << endl;
  cout << "子线程2" << endl;
}

void threadFunction() {
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << "Thread finished" << std::endl;
}

void func(int a, int b, int c){
  cout << "a: " << a << ", b: " << b << ", c: " << c << endl;
}

int main() {
  thread t1(func, 1, 2, 3);
  t1.join();

  // thread t2(func(1, 2, 3));
  // t2.join();
  // thread first(thread_1);        // 开启线程，调用：thread_1()
  // thread second(thread_2, 100);  // 开启线程，调用：thread_2(100)
  // // thread third(thread_2,3);// 开启第3个线程，共享thread_2函数。
  // std::cout << "主线程\n";

  // first.join();  // 必须说明添加线程的方式
  // second.join();
  // std::cout << "子线程结束.\n";  // 必须join完成
  // std::thread t(threadFunction);
  // // t.join();  // 主线程会等待 t 线程结束
  // t.detach(); // t 线程被分离，主线程不会等待 t 线程结束
  // std::cout << "Main thread finished" << std::endl;
  // std::this_thread::sleep_for(std::chrono::seconds(3));

  // using std::chrono::system_clock;
  // std::time_t tt = system_clock::to_time_t(system_clock::now());

  // struct std::tm* ptm = std::localtime(&tt);
  // cout << "Waiting for the next minute to begin...\n";
  // ++ptm->tm_min;    // 加一分钟
  // ptm->tm_sec = 0;  // 秒数设置为0
  // // 暂停执行，到下一整分执行
  // this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));

  return 0;
}
