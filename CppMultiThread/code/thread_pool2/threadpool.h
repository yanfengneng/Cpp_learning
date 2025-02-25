#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include <chrono>
#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "task.h"

/* 该结构体是用来表示任务队列的，对指针特性用的很巧妙，比较难理解。
现使用 STL 中的 queue 来表示任务队列，更好理解代码 */
typedef struct {
  Task* first;  // 队列头：指向第一个任务
  Task** last;  // rear指针的地址：指向最后一个任务的next指针
} threadPool_Queue;

class ThreadPool {
 public:
  ThreadPool(unsigned long maxNum);
  ~ThreadPool();
  // 添加任务
  void taskPost(Task* task);

  // 工作线程函数，使用循环不断地从任务队列中取出任务并执行
  static void worker(void* arg);

 private:
  std::queue<Task*> taskQueue;         // 任务队列
  std::condition_variable cond;        // 条件变量，用于唤醒线程和挂起线程
  std::mutex mutexPool;                // 线程互斥锁，用于保护线程安全
  unsigned long m_maxNum;              // 线程池最大线程数
  unsigned long m_minNum;              // 线程池最小线程数
  int busyNum;                         // 线程是否繁忙，用于管理线程
  int aliveNum;                        // 活跃线程数，即繁忙线程数
  std::vector<std::thread> m_threads;  // 线程队列
};

ThreadPool::ThreadPool(unsigned long maxNum) {
  m_maxNum = maxNum;
  m_minNum = 1;

  busyNum = 0;
  aliveNum = maxNum;  // 初始化活跃线程数
  m_threads.resize(maxNum);
  // 创建并启动 maxNum 个工作线程 worker
  for (unsigned long i = 0; i < maxNum; i++) {
    // this 传入 worker 函数作为形参
    m_threads[i] = std::thread(worker, this);
  }
}

ThreadPool::~ThreadPool() {
  // 唤醒等待的工作线程
  cond.notify_all();
  // 等待所有工作线程结束
  for (unsigned long i = 0; i < m_maxNum; ++i) {
    if (m_threads[i].joinable()) {
      m_threads[i].join();  // 主线程等待子线程i结束
    }
  }
}

// 向线程池中添加任务
// 通过主线程 main.cpp 来添加任务，用来通知阻塞线程进行工作
void ThreadPool::taskPost(Task* task) {
  std::unique_lock<std::mutex> lk(mutexPool);
  // task->next = nullptr;
  // *queue.last = task;
  // queue.last = &task->next;
  taskQueue.push(task);
  // 通知一个等待的工作线程处理任务
  cond.notify_one();
  lk.unlock();
}

// 工作线程函数，使用循环不断地从任务队列中取出任务并执行
// 静态成员函数，将该函数加入到线程中执行表示一个工作线程worker_n
void ThreadPool::worker(void* arg) {
  // 获取线程池对象
  ThreadPool* pool = static_cast<ThreadPool*>(arg);

  while (1) {
    // unique_lock在构造时或者构造后（std::defer_lock）获取锁
    std::unique_lock<std::mutex> lk(pool->mutexPool);
    // while (!pool->queue.first) { //没有任务时，线程挂起
    // 如果任务队列为空，线程进入等待状态，直到被通知有新任务到来
    while (pool->taskQueue.empty()) {  // 没有任务时，线程挂起
      // 挂起，直到收到主线程的事件通知
      pool->cond.wait(lk);
    }
    /*Task* task = pool->queue.first;
    pool->queue.first = task->next;
    lk.unlock();
    if(pool->queue.first==nullptr )  {
        pool->queue.last=&pool->queue.first;
    }*/
    // 从任务队列中取出第一个任务
    Task* task = pool->taskQueue.front();
    pool->taskQueue.pop();  // 从队列中移除
    // 当访问完线程池队列时，线程池解锁
    lk.unlock();
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "执行任务任务开始时间: "
              << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S")
              << std::endl;

    // 执行任务函数
    task->hander(task->arg); // task->arg 为任务函数的参数，与形参 arg 是不一样的
    std::cout << task->name << " finish!" << std::endl;
    delete task;
  }
}

#endif  // _THREADPOOL_H
