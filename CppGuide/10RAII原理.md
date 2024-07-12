- [一、RAII 概念及原理](#一raii-概念及原理)
- [二、应用场景](#二应用场景)
  - [2.1 文件操作](#21-文件操作)
  - [2.2 线程锁](#22-线程锁)
- [三、示例](#三示例)

[C++RAII机制](https://blog.csdn.net/quinta_2018_01_09/article/details/93638251)、[RAII机制](https://www.cnblogs.com/chen-cs/p/13027205.html)、[C++ RAII机制](https://blog.csdn.net/qq_28087491/article/details/130711859)、[C++ 中的 RAII 机制](https://oxnz.github.io/2015/07/23/cpp-raii/)、[c++经验之谈一：RAII原理介绍](https://zhuanlan.zhihu.com/p/34660259)

# 一、RAII 概念及原理

**RAII** 是 Resource Acquisition Is Initialization 的简称，即**资源获取就是初始化**，是 C++ **管理资源、避免内存泄露**的一种惯用法。利用的就是 **C++ 构造的对象最终都会被销毁**的原则。RAII的做法是使用一个对象，在其构造时获取对应的资源，在对象生命期内控制对资源的访问，使之始终保持有效，最后在对象析构的时候，释放构造时获取的资源。因为 C++ 的语言机制保证了：**当一个对象创建的时候，自动调用构造函数，当对象超出作用域的时候会自动调用析构函数。**

使用系统资源时，遵循一个步骤：<font color=alice>1. 申请资源；2. 使用资源；3. 释放资源。</font>

RAII，它充分的利用了C++语言**局部对象自动销毁的特性**来控制资源的生命周期。

那么就可以将初始化和资源都包装到一个类中，在构造函数中进行初始化，在析构函数进行资源的释放。总结为以下四个步骤：**1. 设计一个类封装资源；2. 在构造函数中进行初始化；3. 在析构函数中执行销毁操作；4. 使用时声明一个该类的对象。**

系统资源有**网络套接字、互斥锁、文件句柄和内存**等等。使用 RAII 对这些资源进行管理。智能指针（`std::shared_ptr` 和 `std::unique_ptr`）即RAII最具代表的实现，使用智能指针，可以实现自动的内存管理，再也不需要担心忘记 `delete` 造成的内存泄漏。

* **资源的获取**：RAII的核心思想是，将资源（如内存、文件句柄、互斥锁等）的获取操作放在对象的构造函数中。**这意味着在创建对象时，资源将被自动获取，并且只有在对象的构造函数成功完成后，资源才会被获取**。<font color=alice>这样可以确保资源在有效的对象生命周期内一直可用。</font>

* **资源的释放**：相应地，将资源的释放操作放在对象的析构函数中。**当对象超出其作用域、程序退出或者显式地销毁对象时，析构函数会被自动调用，从而释放资源**。<font color=alice>这种方式可以确保在任何情况下都会正确地释放资源，避免资源泄漏。</font>

* **作用域和自动化**：利用 C++ 的作用域规则，RAII可以确保资源的获取和释放与对象的生命周期相一致。**资源在对象的作用域内是可见的，因此只有在该作用域内才能访问该资源。一旦对象超出作用域，就会被销毁，析构函数会被调用，从而释放资源**。<font color=alice>这种自动化的过程使得资源管理变得简单、安全且可靠。</font>

* **异常安全性**：RAII也提供了异常安全性。**如果在对象的构造函数中获取资源时发生异常，对象将无法被完全创建，从而资源不会被泄漏。析构函数会被自动调用，用于释放已获取的资源，确保不会发生资源泄漏。**



# 二、应用场景

## 2.1 文件操作

```cpp
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

/* FileRAII 封装了文件句柄管理的逻辑 */
class FileRAII {
 public:
  /* 构造函数打开指定的文件，并在构造过程中获得文件句柄 */
  FileRAII(const std::string& filename) : file(filename) {
    file.open(filename);
    if (!file.is_open()) {
      throw std::runtime_error("Failed to open file: " + filename);
    }
    std::cout << "File opened: " << filename << std::endl;
  }

  /* 析构函数在对象销毁时自动调用，关闭文件句柄，确保文件资源被释放 */
  ~FileRAII() {
    if (file.is_open()) {
      file.close();
      std::cout << "File closed." << std::endl;
    }
  }

  /* 用于向文件写入内容，通过文件句柄 file 来实现 */
  void write(const std::string& text) {
    if (file.is_open()) {
      file << text;
    }
  }

 private:
  std::ofstream file;
};

int main() {
  try {
    FileRAII file("example.txt");
    file.write("Hello, RAII!");
    // 当 file 对象离开作用域时，即使在异常情况下，也会自动调用 FileRAII
    // 的析构函数，关闭文件句柄，确保文件资源的正确释放。 file will be
    // automatically closed when leaving scope
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
/*
运行结果：
File opened: example.txt
File closed.
*/
```

## 2.2 线程锁

```cpp
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class LockGuardRAII {
 public:
  // 构造函数，获取锁
  explicit LockGuardRAII(std::mutex& mtx) : mutex_(mtx) {
    mutex_.lock();
    std::cout << "Lock acquired\n";
  }

  // 析构函数，释放锁
  ~LockGuardRAII() {
    mutex_.unlock();
    std::cout << "Lock released\n";
  }

 private:
  std::mutex& mutex_;  // 引用传递的互斥锁
};

// 共享资源
int counter = 0;          // 计时器
std::mutex counterMutex;  // 用于保护共享资源

// 线程函数，增加计数器
void incrementCounter() {
  for (int i = 0; i < 10; ++i) {
    // 在 LockGuardRAII对象的生命周期内，锁被获取
    // 在循环结束或异常发生时，锁会被自动释放
    LockGuardRAII lock(counterMutex);  // 使用 RAII 技术管理锁
    ++counter;
    std::cout << "Counter: " << counter << "\n";
  }
}

int main() {
  std::vector<std::thread> threads;

  // 创建多个线程
  for (int i = 0; i < 5; ++i) {
    threads.emplace_back(incrementCounter);
  }

  // 等待所有线程完成
  for (auto& th : threads) {
    th.join();
  }

  std::cout << "Final counter value: " << counter << "\n";
  return 0;
}
```



# 三、示例

* **智能指针（Smart Pointers）**：C++标准库提供了几种智能指针类，包括std::unique_ptr、std::shared_ptr和std::weak_ptr。这些智能指针类利用了RAII的概念，用于管理动态分配的内存资源。它们在对象的构造函数中获取内存资源，而在析构函数中自动释放内存资源。智能指针的使用避免了手动管理内存，减少了内存泄漏的风险。
* **文件和流处理**：C++标准库中的文件和流处理类，例如std::fstream、std::ifstream和std::ofstream，利用RAII来管理文件资源。当创建这些对象时，在构造函数中打开文件，并在析构函数中关闭文件。这样可以确保文件资源在对象的生命周期结束时被正确释放。
* **互斥锁和资源锁**：多线程编程中，为了保护共享资源的访问，常常使用互斥锁（std::mutex）或资源锁（std::lock_guard、std::unique_lock等）。这些锁对象的构造函数在获取锁资源时被调用，而析构函数在离开作用域时自动释放锁资源。这种方式避免了忘记释放锁的情况，提高了多线程代码的安全性。
* **动态内存管理**：RAII非常适用于管理动态分配的内存资源。除了智能指针之外，可以自定义类来实现RAII，以管理动态内存。在类的构造函数中分配内存，在析构函数中释放内存，确保动态内存资源的正确管理。
* **资源管理类**：RAII的思想也可以应用于自定义的资源管理类。例如，可以创建一个数据库连接管理类，在构造函数中建立数据库连接，在析构函数中关闭连接。这样，通过对象的生命周期来管理数据库连接，可以确保连接在不再需要时被正确释放。