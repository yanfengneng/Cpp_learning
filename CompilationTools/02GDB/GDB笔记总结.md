- [一、GDB 概念](#一gdb-概念)
  - [1.1 调试程序](#11-调试程序)
  - [1.2 GDB 的作用](#12-gdb-的作用)
  - [1.3 安装 GDB](#13-安装-gdb)
  - [二、GDB 的用法](#二gdb-的用法)
  - [2.1 调试步骤](#21-调试步骤)
  - [2.2 常用的调试命令](#22-常用的调试命令)
    - [2.2.1 断点调试](#221-断点调试)
    - [2.2.2 数据相关的命令](#222-数据相关的命令)
    - [2.2.3 调试运行环境相关的命令](#223-调试运行环境相关的命令)
    - [2.2.4 堆栈相关的命令](#224-堆栈相关的命令)
    - [2.2.5 跳转执行](#225-跳转执行)
- [三、调试具体程序](#三调试具体程序)
  - [3.1 调试  core 文件](#31-调试--core-文件)
  - [3.2 调试多线程程序](#32-调试多线程程序)
    - [3.2.1 程序阻塞问题排查](#321-程序阻塞问题排查)
    - [3.2.2 数据篡改问题排查](#322-数据篡改问题排查)
    - [3.2.3 堆内存重复释放问题排查](#323-堆内存重复释放问题排查)
  - [3.3 GDB 调试多进程](#33-gdb-调试多进程)


参考：[GDB调试命令详解](https://blog.csdn.net/qq_28351609/article/details/114855630)、[gdb 调试命令](https://www.cnblogs.com/wuyuegb2312/archive/2013/03/29/2987025.html)、[Linux 高级编程 - 15 个 gdb 调试基础命令](https://dlonng.com/posts/gdb)

# 一、GDB 概念

## 1.1 调试程序

程序中出现的语法错误可以借助编译器来进行解决；但是逻辑错误则只能靠自己解决。实际场景中解决逻辑错误最高效的方法就是借助调试工具对程序进行调试了。

通过调试程序，可以监控程序执行的每一个细节，包括变量的值、函数的调用过程、内存中的数据、线程的调度等，从而发现隐藏的错误或者低效的代码。



## 1.2 GDB 的作用

GDB 调试器可以用来实现以下几个功能：

* 程序启动时，可以按照我们自定义的要求运行程序，如设置参数、环境变量；
* 可使被调试程序在指定代码处暂停运行，并查看当前程序的运行状态（如当前变量的值、函数的执行结果等），即支持断点调试；
* 程序在执行过程中，可以改变某个变量的值，还可以改变代码的执行顺序，从而修改程序中出现的逻辑错误；

## 1.3 安装 GDB

```shell
# 安装 gdb
sudo apt-get install gdb
# 安装必要的编译工具
sudo apt-get install build-essential

# 查看 gdb 版本
gdb -v
```



## 二、GDB 的用法

使用 `g++ -g` 编译程序，生成带调试信息的可执行文件，就能使用 `gdb` 进行断点调试了。

```
g++ -g hello.cpp -o hello.out
```

## 2.1 调试步骤

**在 Windows 的 IDE 下调试程序，例如使用 VS，一般都有下面这几个操作：**

* 1）Debug 模式编译并启动程序。
* 2）程序运行出错，打**断点**分析出错的地方。
* 3）单步运行程序，包括：`step over` 单步执行；`step into` 跳入函数；`step return` 跳出函数。
* 4）还有全速运行，打印或者监视变量，冻结或解冻线程等调试技术。

在 IDE 中上面的这些步骤一般都**有固定的按钮**提供给我们使用，非常的简单方便，我们只要多练习练习，在图形界面调试程序不会很难，但是在 Linux 下用命令来调试程序就比图形界面要复杂很多了。

***

在 Linux 下既然是使用命令行来调试，顾名思义就是**手敲命令来调试程序**，也就是**使用 GDB 进行调试，大体分为下面几个步骤**：

* 1）编译可以调试的程序；
* 2）运行程序，打断点；
* 3）单步调试，监控变量；
* 4）可视化调试；
* 5）其他调试技术；

上述步骤虽然与 IDE 调试差不多，但是实际上是需要自己敲调试命令的，而不是直接点击按钮了。



## 2.2 常用的调试命令

![image-20240930205901509](Image/GDB调试命令.png)



**具体执行步骤如下：**

1. **载入要调试的程序**：`gdb hello.out`；输入 `q` 退出 `gdb` 调试程序；
2. **查看调试程序**：`list` 或者 `l`;
3. **添加断点**：在 `gdb` 下输入 `break` 或者简写 `b`，以下有几个常见用法：

```shell
b function_name
b row_num
b file_name:row_num
b row_num if condition
```

4. **查看断点**：`info break` 或者简写 `i b`；
5. **禁用断点**：`disable Num`；
6. **删除断点**：`delete Num` 或者简写 `d Num`；
7. **运行程序**：使用 `run` 或者简写 `r` 来运行当前载入的程序；
8. **单步调试**：使用 `next` 或者简写 `n` 来单步执行下一步；
9. **跳入、跳出函数**：使用 `step` 或者简写 `s` 来跳入一个函数，使用 `finish` 或者简写 `fi` 来跳出一个函数。
10. **打印变量值**：使用 `print val` 或者简写 `p val` 来打印一个变量或者函数的返回值；
11. **监控变量**：使用 `watch val` 来监控一个变量，使用 `info watch` 来查看监控的变量。**注意：程序必须先运行才能进行监控。**
12. **查看变量类型**：使用 `whatis val` 来查看一个变量的类型。
13. **在 `gbd` 下进入 shell**：输入命令 `shell`。
14. **在 `gdb` 下实现可视化调试**：输入命令 `wi`。

### 2.2.1 断点调试

![image-20240930214508296](Image/断点调试.png)

### 2.2.2 数据相关的命令

![image-20240930214627325](Image/数据命令.png)

### 2.2.3 调试运行环境相关的命令

![image-20240930214746969](Image/调试运行相关命令.png)

### 2.2.4 堆栈相关的命令

![image-20240930214859148](Image/堆栈相关命令.png)

### 2.2.5 跳转执行

![image-20240930215721832](Image/跳转命令.png)



# 三、调试具体程序

`Crash` 指的是**程序因意外错误或异常而突然终止运行**，常见原因有：

1. **空指针解引用**：访问未初始化或已释放的内存。
2. **数组越界**：访问超出数组范围的元素。
3. **内存泄漏**：未释放不再使用的内存，导致内存耗尽。
4. **除零错误**：进行除零操作。
5. **栈溢出**：递归过深或局部变量过多导致栈空间耗尽。
6. **竞态条件**：多线程环境下，资源访问顺序不当。
7. **硬件故障**：内存损坏、磁盘错误等硬件问题。

**主要影响：**

- **数据丢失**：未保存的数据可能丢失。
- **用户体验**：程序突然关闭，影响用户使用。
- **系统稳定性**：严重时可能导致操作系统不稳定。

**调试方法：**

1. **日志记录**：通过日志定位问题。
2. **调试工具**：使用调试器逐步执行代码，检查变量和调用栈。
3. **代码审查**：通过人工检查发现潜在问题。
4. **单元测试**：编写测试用例，验证代码的正确性。



以下两部分主要参考：[程序调试利器GDB – 使用指南](https://zhuanlan.zhihu.com/p/611654345)

## 3.1 调试  core 文件

1）默认情况下，程序 Crash 是不生成 core 文件的，因为默认允许的 core 文件大小为0。在 WSL 中需要使用以下命令中的一个来使程序崩溃时产生 core 文件，参考：[WSL 生成 core 文件命令](https://blog.csdn.net/asitMJ/article/details/135234133)。

```bash
// 指定文件
sudo sysctl -w kernel.core_pattern=<desired-file-path>/<desired-file-name>

// 或者保持默认, 哪里段错误，哪里出现core文件
sudo sysctl -w kernel.core_pattern=core 
```

2）修改生成 core 文件的大小

```bash
# ulimit 命令
man ulimit

# 如果 core 文件没有生成，则需要查看 ulimit 限制
# 显示目前资源限制的设定
ulimit -a

# 将 core file 文件大小设置为无限制的
# -c 表示设置大小的参数，也可以设置为 0
ulimit -c unlimited

# 来查看 coredump 崩溃的地方
gdb 二进制文件 core文件
```



## 3.2 调试多线程程序

[如何使用gdb调试多线程死锁问题，并定位触发死锁的线程](https://blog.csdn.net/buknow/article/details/125184246)、[线程的查看以及利用gdb调试多线程](https://blog.csdn.net/zhangye3017/article/details/80382496)、[GDB 调试多线程程序的总结 ](https://www.cnblogs.com/WindSun/p/12785322.html)

```bash
# 查看当前运行的进程
#  ps （英文全拼：process status）命令用于显示当前进程的状态，类似于 windows 的任务管理器
# -e：显示所有进程；-f：以完整格式显示进程信息。
ps aux | grep a.out
ps -ef | grep a.out

# 查看所有进程
ps aux    # BSD 风格：显示所有进程的详细信息（用户、PID、CPU、内存等）
ps -ef    # Unix 风格：显示所有进程的完整命令行

# 查看当前运行的轻量级进程
ps -aL | grep a.out

# 查看进程的线程
ps -L -p 1234   # 显示 PID 1234 的所有线程

# 查看主线程和新线程的关系
pstree -p 主线程id
```

### 3.2.1 程序阻塞问题排查



### 3.2.2 数据篡改问题排查



### 3.2.3 堆内存重复释放问题排查



![image-20250220210557033](Image/GDB调试多线程命令.png)



## 3.3 GDB 调试多进程

>[GDB调试多进程的命令介绍和演示](https://www.cnblogs.com/liuhanxu/p/17011777.html)、[Linux——gdb调试时多进程切换方法(attach/follow-fork-mode)](https://blog.csdn.net/weixin_61857742/article/details/127241996)

```cpp
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
using namespace std;

int main() {
  // 子进程中fork()函数返回 0，在父进程中fork()函数返回子进程的进程ID
  pid_t pid = fork();
  if (pid == 0) {  // 子进程
    printf("I am child, my pid = %d, my parent pid = %d\n", getpid(),
           getppid());
  } else if (pid > 0) {  // 父进程
    printf("I am parent, my pid = %d, my child pid = %d\n", getpid(), pid);
    wait(NULL);  // 等待子进程退出
  } else {       // fork失败
    perror("fork error!\n");
    return -1;
  }
  return 0;
}
```

![image-20250226211339940](Image/GDB调试多进程命令.png)

**进程操作命令 inferiors：**

* `info inferiors`：**查看所有进程，带 `*` 号表示当前进程**。
* `inferiors 2`：切换到编号为 2 的进程。
* `detach inferiors 2`：detach掉编号为2的进程，注意这个进程还存在，可以再次用run命令执行它。
* `kill inferiors 2`：kill掉编号为2的进程，注意这个进程还存在，可以再次用run命令执行它。
* `add-inferior [-copies n] [-exec executable]`：添加新的调试进程。

***

**只调试子进程 set follow-fork-mode child：**

默认设置下，在调试多进程程序时 GDB 只会调试主进程，在高版本的 GDB  中支持多进程的同时调试。 **换句话说， `GDB` 可以同时调试多个程序. 只需要设置 `follow-fork-mode` (默认值 `parent`) 和 `detach-on-fork` (默认值 `on` )即可。**

* `set follow-fork-mode parent`：只调试父进程，子进程继续运行（GDB默认）。
* `set follow-fork-mode child`：只调试子进程，父进程继续运行。
* `show follow-fork-mode`：查看follow-fork-mode当前值，也就是查看当前调试的进程。

***

**同时调试父子进程 set detach-on-fork off：**

* `set detach-on-fork on`：只调试一个进程，可以是父进程或子进程（GDB默认）。
* <font color=alice>`set detach-on-fork off`：同时调试父子进程，如果 follow-fork-mode是 parent，则 gdb 跟踪父进程，子进程阻塞在 fork 位置。如果 follow-fork-mode 是 child，则 gdb 跟踪子进程，父进程阻塞在 fork 位置。此时用户可以根据调试情况在父进程和子进程之间来回切换调试。</font>
* `show detach-on-fork`：查看detach-on-fork当前值，也就是查看当前调试的进程模式。

***

**所有进程同步调试：**

* **在调试多进程时，默认情况下，除了当前调试的进程，其他进程都处于挂起状态，所以，如果需要在调试当前进程的时候，其他进程也能正常执行，那么通过设置`set schedule-multiple on`即可**。

* `set schedule-multiple off`：gdb 发出执行命令后，只有当前进程会执行，其他进程挂起（GDB默认）。

* `set schedule-multiple on`：当 `gdb` 发出执行命令后，所有的进程都会正常执行。
* `show schedule-multiple`：查看schedule-multiple当前值。