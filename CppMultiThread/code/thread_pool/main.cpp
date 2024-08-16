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
    // Task *tt = new Task();
    // 使用智能指针
    std::shared_ptr<Task> tt = std::make_shared<Task>();
    // 将任务 tt 添加到线程池的任务队列 tasks_queue
    // 中。当线程池中的某个线程空闲时，它将从任务队列中取出一个任务并执行。
    // 不停的添加任务，任务是队列 queue，因为只有固定的线程数
    pool.append(tt.get());
    // 输出当前任务队列中的任务数量。由于任务被立即删除，因此每次输出的队列大小会保持不变或增长得非常慢。
    cout << "添加的任务数量： " << pool.tasks_queue.size() << endl;
    // delete tt;  // 立即删除指针，避免内存泄漏
  }
}
