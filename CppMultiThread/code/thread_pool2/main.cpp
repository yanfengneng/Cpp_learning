#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "task.h"
#include "threadpool.h"

void executeTask_1(void* size) {
  int* s = static_cast<int*>(size);
  int value = *s;
  long sum = 0;
  for (int i = 0; i < value; i++) {
    sum += i;
  }
  std::cout << "计算完成, sum = " << sum << std::endl;
}

int main() {
  long* n = new long;
  *n = 1000000000;
  // 获取当前时间
  auto start = std::chrono::system_clock::now();
  executeTask_1(n);
  executeTask_1(n);
  executeTask_1(n);
  executeTask_1(n);
  // 获取操作完成后的时间
  auto end = std::chrono::system_clock::now();
  // 计算时间差
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  // 输出时间差（以毫秒为单位）
  std::cout << "一般流程执行所有任务所需时间: " << duration.count() << "毫秒"
            << std::endl;

  ThreadPool pool(4);
  Task* t1 = new Task("Task1");
  t1->createTask(executeTask_1, n);
  Task* t2 = new Task("Task2");
  t2->createTask(executeTask_1, n);
  Task* t3 = new Task("Task3");
  t3->createTask(executeTask_1, n);
  Task* t4 = new Task("Task4");
  t4->createTask(executeTask_1, n);

 // 获取当前时间
  auto now = std::chrono::system_clock::now();
  auto now_c = std::chrono::system_clock::to_time_t(now);
  std::cout << "线程池执行任务开始时间: "
            << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << std::endl;
            
  pool.taskPost(t1);
  pool.taskPost(t2);
  pool.taskPost(t3);
  pool.taskPost(t4);

  return 0;
}