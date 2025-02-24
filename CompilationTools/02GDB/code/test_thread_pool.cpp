#include <bits/stdc++.h>
using namespace std;

using WorkItem = std::function<void()>;

// * 线程安全队列
template <typename T>
class SafeQueue {
 public:
  void push(const T &item) {
    {
      std::scoped_lock lock(mtx_);
      queue_.push(item);
    }
    cond_.notify_one();
  }
  
  void push(T &&item) {  // 两个push方法，此处不是万能引用而是单纯右值
    {
      std::scoped_lock lock(mtx_);
      queue_.push(std::move(item));
    }
    cond_.notify_one();
  }

  bool pop(T &item) {
    std::unique_lock lock(mtx_);
    cond_.wait(lock, [&]() { return !queue_.empty() || stop_; });
    if (queue_.empty()) return false;
    item = std::move(queue_.front());
    queue_.pop();
    return true;
  }

  std::size_t size() const {
    std::scoped_lock lock(mtx_);
    return queue_.size();
  }

  bool empty() const {
    std::scoped_lock lock(mtx_);
    return queue_.empty();
  }

  void stop() {
    {
      std::scoped_lock lock(mtx_);
      stop_ = true;
    }
    cond_.notify_all();
  }

 private:
  std::condition_variable cond_;
  mutable std::mutex mtx_;
  std::queue<T> queue_;
  bool stop_ = false;
};

// * 简易多线程单任务队列线程池，使用SafeQueue线程安全队列。
class SimplePool {
 public:
  explicit SimplePool(size_t threads = std::thread::hardware_concurrency()) {
    for (size_t i = 0; i < threads; ++i) {
      workers_.emplace_back([this]() {
        for (;;) {
          std::function<void()> task;
          if (!queue_.pop(task)) return;
          if (task) task();
        }
      });
    }
  }

  void enqueue(WorkItem item) { queue_.push(std::move(item)); }

  ~SimplePool() {
    queue_.stop();
    for (auto &thd : workers_) thd.join();
  }

 private:
  SafeQueue<WorkItem> queue_;
  std::vector<std::thread> workers_;
};

void exampleTask(int n) {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::cout << "Task " << n << " executed" << std::endl;
}

int main() {
  // 创建一个线程池，使用默认的线程数
  SimplePool pool;

  // 向线程池中添加任务
  for (int i = 0; i < 10; ++i) {
    pool.enqueue([i]() { exampleTask(i); });
  }

  // 等待一段时间以确保所有任务都被执行
  std::this_thread::sleep_for(std::chrono::seconds(2));

  return 0;
}