#ifndef _TANK_H
#define _TANK_H

#include <chrono>
#include <iostream>
#include <string>

class Task {
 public:
  Task();
  Task(std::string name);
  Task(void *arg);
  // 用于创建任务，传入任务处理函数和参数
  void createTask(void (*hander)(void *arg), void *arg);
  ~Task();

  void (*hander)(void *arg);  // 函数指针，用来指向任务处理函数
  void *arg;                  // 处理任务函数的参数
  // Task* next; // 指向下一个任务
  std::string name;    // 任务名
  static int taskNum;  // 任务数量
};

// task.cpp
int Task::taskNum = 0;

Task::Task() {
  // next = nullptr;
  this->arg = nullptr;
  taskNum++;
}

Task::Task(std::string name) {
  this->name = name;
  this->arg = nullptr;
  taskNum++;
}

Task::Task(void *arg) {
  // next = nullptr;
  this->arg = arg;
  taskNum++;
}

inline void Task::createTask(void (*hander)(void *arg), void *arg) {
  this->hander = hander;
  this->arg = arg;
}

/* 在任务销毁时减少任务数量 */
Task::~Task() {
  if (--taskNum == 0) {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "所有任务执行完成, 完成时间："
              << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S")
              << std::endl;
  }
  free(this->arg);
}

#endif  // _TANK_H
