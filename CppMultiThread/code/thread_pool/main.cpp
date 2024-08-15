#include <cmath>
#include <string>

#include "thread_pool.h"
using namespace std;

class Task {
 public:
  void process() {
    // cout << "run........." << endl;
    // 测试任务数量
    long i = 1000000;
    while (i != 0) {
      int j = sqrt(i);
      i--;
    }
  }
};

int main(void) {
  threadPool<Task> pool(6);  // 6个线程，vector
  std::string str;
  while (1) {
    Task *tt = new Task();
    // 使用智能指针
    pool.append(tt);  // 不停的添加任务，任务是队列queue，因为只有固定的线程数
    cout << "添加的任务数量： " << pool.tasks_queue.size() << endl;
    ;
    delete tt;
  }
}
