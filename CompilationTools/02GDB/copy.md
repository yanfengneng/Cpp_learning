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
g++ -g test_run.cpp -o test_run.out

# 让程序后台运行并返回一个进程号
./test_run.out &

# 查程序的进程号
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