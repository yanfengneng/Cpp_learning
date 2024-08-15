#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include <assert.h>

#include <condition_variable>
#include <iostream>
#include <memory>  //unique_ptr
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

const int MAX_THREADS = 1000;  // 最大线程数目

/**
 * 实现了一个简单的线程池类，用于管理多个工作线程并处理任务队列中的任务。
 * 线程池通过工作线程并发地执行任务，以提高系统的并发能力和资源利用效率。
 */
template <typename T>
class threadPool {
 public:
  threadPool(int number = 1);  // 默认开一个线程
  ~threadPool();
  std::queue<T *> tasks_queue;  // 任务队列

  bool append(T *request);  // 往请求队列＜task_queue＞中添加任务<T *>

 private:
  // 工作线程需要运行的函数，不断的从任务队列中取出并执行
  static void *worker(void *arg);
  void run();

 private:
  std::vector<std::thread> work_threads;  // 工作线程

  std::mutex queue_mutex;
  std::condition_variable condition;  // 必须与unique_lock配合使用
  bool stop;
};  // end class

// 构造函数，创建线程
template <typename T>
threadPool<T>::threadPool(int number) : stop(false) {
  if (number <= 0 || number > MAX_THREADS) throw std::exception();
  for (int i = 0; i < number; i++) {
    std::cout << "created Thread num is : " << i << std::endl;
    work_threads.emplace_back(worker, this);  // 添加线程
    // 直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程。
  }
}

template <typename T>
inline threadPool<T>::~threadPool() {
  std::unique_lock<std::mutex> lock(queue_mutex);
  stop = true;

  condition.notify_all();
  for (auto &ww : work_threads) ww.join();  // 可以在析构函数中join
}

// 添加任务
template <typename T>
bool threadPool<T>::append(T *request) {
  /*操作工作队列时一定要加锁，因为他被所有线程共享*/
  queue_mutex.lock();  // 同一个类的锁
  tasks_queue.push(request);
  queue_mutex.unlock();
  condition.notify_one();  // 线程池添加进去了任务，自然要通知等待的线程
  return true;
}

// 单个线程
template <typename T>
void *threadPool<T>::worker(void *arg) {
  threadPool *pool = (threadPool *)arg;
  pool->run();  // 线程运行
  return pool;
}

template <typename T>
void threadPool<T>::run() {
  while (!stop) {
    std::unique_lock<std::mutex> lk(this->queue_mutex);
    /*　unique_lock() 出作用域会自动解锁　*/
    this->condition.wait(lk, [this] { return !this->tasks_queue.empty(); });
    // 如果任务为空，则wait，就停下来等待唤醒
    // 需要有任务，才启动该线程，不然就休眠
    if (this->tasks_queue.empty())  // 任务为空，双重保障
    {
      assert(0 &&
             "断了");  // 实际上不会运行到这一步，因为任务为空，wait就休眠了。
      continue;
    } else {
      T *request = tasks_queue.front();
      tasks_queue.pop();
      if (request)  // 来任务了，开始执行
        request->process();
    }
  }
}
#endif
