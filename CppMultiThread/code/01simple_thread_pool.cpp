#include <unistd.h>

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
using namespace std;

class threadPool {
 private:
  int threadNum;
  int cnt;
  bool started;
  condition_variable m_condition;
  mutex m_mutex;
  vector<thread*> threadList;
  queue<int> q;

 public:
  threadPool(int num = 4) : threadNum(num), cnt(0), started(true) {
    for (int i = 0; i < threadNum; ++i) {
      thread* pthread = new thread(&threadPool::threadFunc, this);
      threadList.push_back(pthread);
    }
  }

  ~threadPool() {
    for (int i = 0; i < threadNum; ++i) {
      threadList[i]->join();
    }
    for (int i = 0; i < threadNum; ++i) {
      delete threadList[i];
    }
    threadList.clear();
    cout << "threadPool destroy" << endl;
  }

  void threadFunc() {
    thread::id tid = this_thread::get_id();  // 临时添加，为不影响行数加在这
    {
      unique_lock<mutex> lock(m_mutex);
      ++cnt;
      cout << "my pos is: " << cnt << " and thread id is: " << tid << endl;
    }
    while (started) {
      {
        unique_lock<mutex> lock(m_mutex);
        while (q.empty() && started) {
          m_condition.wait(lock);
        }
        if (!started) break;
        int i = q.front();
        cout << "q's front is : " << i << " and I am " << tid << endl;
        q.pop();
      }
      sleep(1);
    }
  }

  void stop() {
    started = false;
    m_condition.notify_all();
  }

  void addTask(int num) {
    unique_lock<mutex> lock(m_mutex);
    q.push(num);
    m_condition.notify_one();
  }
};

int main(int argc, char* argv[]) {
  printf("func begin\n");

  threadPool myPool;
  sleep(1);
  for (int i = 0; i < 4; ++i) {
    myPool.addTask(i);
  }
  sleep(1);
  printf("stop\n");
  myPool.stop();
  printf("bye~~\n");
  return 0;
}
