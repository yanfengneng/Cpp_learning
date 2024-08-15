#include <condition_variable>  // std::condition_variable
#include <iostream>            // std::cout
#include <mutex>               // std::mutex, std::unique_lock
#include <thread>              // std::thread, std::this_thread::yield

std::mutex mtx;
std::condition_variable cv;

int cargo = 0;  // 表示货物的数量
/* 当 cargo 不为 0 时，则表示有货物可供消费。
  true 表示有货物，false 表示没有货物。
 */
bool shipment_available() { return cargo != 0; }

/* 消费货物 */
void consume(int n) {
  // 循环 n 次，每次都尝试消耗一个货物
  for (int i = 0; i < n; ++i) {
    std::unique_lock<std::mutex> lck(mtx);  // 自动上锁
    // 若第二个参数为 false，则线程进入阻塞状态，直到第二个参数返回
    // true，才会结束阻塞
    // wait()
    // 调用之后消费者线程被阻塞，互斥锁被释放，允许生产者线程获取互斥锁并生成货物
    cv.wait(lck, shipment_available);
    std::cout << cargo << '\n';
    cargo = 0;
  }
}

/* 生产者-消费者模式 */
int main() {
  // 尝试 10 次消费
  std::thread consumer_thread(consume, 10);  // 创建并启动消费者线程

  /* 主线程（生产者）生成货物 cargo， */
  for (int i = 0; i < 10; ++i) {
    // 若 cargo 为 0，则生产者线程会使用 std::this_thread::yield()
    // 让出cpu，等待消费者线程完成消费
    while (shipment_available()) {
      // 放弃本线程执行
      std::this_thread::yield();
    }
    // 生产者获得互斥锁，然后生成货物，调用 notify_one
    // 来通知消费者线程货物已经可以消费了。
    // 消费者线程在被唤醒后，重新获取互斥锁，并继续执行 wait() 之后的代码。
    std::unique_lock<std::mutex> lck(mtx);  // 加锁，作用域结束就释放锁
    // 生产货物
    cargo = i + 1;
    // 解锁消费者线程，让其消费货物
    cv.notify_one();
  }

  consumer_thread.join();  // 阻塞主线程，等待子线程执行结束
  return 0;
}
