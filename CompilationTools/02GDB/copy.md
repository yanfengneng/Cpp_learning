```bash
# 一个最基本的调试 gdb 步骤

# 1. 编译出带调试信息的可执行文件
g++ -g test.cpp -o test.out

# 2. 进入 gdb 调试
gdb ./test.out

# 3. 基本命令介绍
# 查看所有的 gdb 命令
man gdb

# 查看源代码
list

run(r) # 运行程序
quit(q) # 退出 gdb 模式

# 打断点的两种方式
break(b) 函数名 # 给函数打断点
break(b) 行号 # 在具体行号处打断点

# 查看断点情况
info break(b)

# 打印变量
print(p) 变量名
print(p) 地址

# 进入某一个具体的函数调试
step(s)

# 日志功能，记录gdb调试日志
set logging on

# 观察变量是否变化 watchpoint
watch 变量名/地址
info watchpoints # 查看观察变量

# 还有个 checkpoint 可以学下
```

**调试 core 文件：**

```bash
# ulimit 命令
man ulimit

# 如果 core 文件没有生成，则需要查看 ulimit 限制
# 显示目前资源限制的设定
ulimit -a

# 将 core file 文件大小设置为无限制的
ulimit -c unlimited

# 来查看 coredump 崩溃的地方
gdb 二进制文件 core文件
```



**调试正在运行的文件：**

```bash
# 编译程序
# 只要条件允许，建议使用-O0来关闭编译优化，用来避免调试时，源代码和符号表对应不上的奇怪问题
# -g 生成带调试信息的可执行文件
g++ -g test_run.cpp -o test_run.out

# 让程序后台运行并返回一个进程号
./test_run.out &

# 查程序的进程号
#  ps （英文全拼：process status）命令用于显示当前进程的状态，类似于 windows 的任务管理器
# -e：显示所有进程
# -f：以完整格式显示进程信息
ps -ef | grep test_run.out

# 调试正在运行的程序
gdb -p 进程号
```

要将 `a.out` 程序在后台运行，可以使用以下方法：

**1）在命令末尾加上 `&`，程序将在后台运行**。输出：程序的输出仍会显示在终端；返回：会显示后台任务中的作业ID和进程ID。

2）`nohup ./a.out &`可以让程序在后台运行，且不受终端关闭的影响。**输出**：默认将输出重定向到 `nohup.out` 文件。**重定向**：可以自定义输出文件，如 `nohup ./a.out > output.log 2>&1 &`。

**3）使用 `disown` 命令**。

```bash
./a.out
Ctrl+Z
bg
disown
```

- **Ctrl+Z**：暂停程序。
- **bg**：将暂停的程序放入后台。
- **disown**：使程序与终端分离，终端关闭后程序继续运行。

[小神仙讲 GDB](https://www.bilibili.com/video/BV1EK411g7Li?spm_id_from=333.788.player.switch&vd_source=93d2c7cab25a2966d2b5d0ccf80348c8&p=7)



# 一、启动 GDB

## 1.1 使用 GDB 加载程序，在 GDB 命令行启动运行

使用 GDB 加载可执行文件后，在 GDB 中可以设置断点，调试运行程序。

```bash
# 使用GDB加载可执行程序
gdb [program]
# 使用GDB加载可执行程序并传递命令行参数
gdb --args [program] [arguments]

# 开始调试程序
(gdb) run
# 传递命令行参数并开始调试程序
(gdb) run arg1 arg2
# 开始调试程序并在main函数入口中断
(gdb) start
# 传递命令行参数，开始调试程序并在main函数入口中断
(gdb) start arg1 arg2
```

## 1.2 使用 GDB 调试正在运行的程序

GDB 可以通过进程号，附加到一个运行中的进程中。也可以在进入 GDB 控制台后，通过 attach 命令附加到进程中。

需要注意的是：一个进程只允许附加一个调试进程，如果被调试的进程当前已经处于被调试状态，那么此时要么通过 detach 命令来解除另一个 GDB 进程的附加状态，要么强行结束当前进行的 GDB 进行，否则不能通过 GDB 附加到另一个调试进程。

```bash
# 通过GDB命令附加到进程
gdb -p [pid]
gdb --pid [pid]

# 在GDB控制台内，通过attach命令附加的进程
gdb
(gdb) attach [pid]
```

## 1.3 调试 core 文件

>https://blog.csdn.net/asitMJ/article/details/135234133

**WSL 生成 core 文件命令：**

```bash
// 指定文件
sudo sysctl -w kernel.core_pattern=<desired-file-path>/<desired-file-name>

// 或者保持默认, 哪里段错误，哪里出现core文件
sudo sysctl -w kernel.core_pattern=core 
```



当程序崩溃后，如果生成了 core 文件，就可以通过 GDB 加载 core 文件来调试发生异常时的程序信息。core 文件并没有限制当前机器相关信息的，可以拷贝 core 文件到另一台机器进行 core 分析，但前提是产生 core 文件的程序的符号表，需要和分析 core 文件时加载的程序的符号表保持一致。

```bash
# 使用GDB加载core文件进行异常调试
gdb --core [core file] [program]
```

## 1.4 使用 GDB 加载程序并自动运行

在自动化测试场景中，需要程序能够以非中断的方式流畅地运行，同时又希望附加 GDB，以便随时可以了解程序的状态。这时可以使用 `--ex` 参数，指定 GDB 完成程序加载后，自动运行的命令。

```bash
# 使用GDB加载程序，并在加载完成后自动运行run命令
gdb --ex r --args [program] [arguments]
```

# 二、使用 GDB

## 2.1 断点调试 GDB



## 2.2 Segmentation Fault 问题排查

在实际开发中，使用了未初始化的指针、空指针、已经被回收了内存的指针、栈溢出、堆溢出等方式，都会引发 Segmentation Fault。

如果使用了 core 文件生成，当程序崩溃时，会在指定位置生成一个 core 文件。通过使用 GDB 对 core 文件的分析，可以帮助我们定位引发 Segmentation Fault 的原因。

