#include <iostream>
#include <thread>
using namespace std;
void thread_1() {
  while (1) {
    cout << "子线程1111" << endl;
  }
}
void thread_2(int x) {
  while (1) {
    cout << "子线程2222" << endl;
  }
}
int main() {
  thread first(thread_1);        // 开启线程，调用：thread_1()
  thread second(thread_2, 100);  // 开启线程，调用：thread_2(100)

  first.detach();
  second.detach();
  for (int i = 0; i < 10; i++) {
    std::cout << "主线程\n";
  }
  return 0;
}
