- [1、基本命令](#1基本命令)
- [echo](#echo)
- [tar 解压文件](#tar-解压文件)
- [Ubuntu 远程桌面连接](#ubuntu-远程桌面连接)
- [2、ubutnu 挂载磁盘](#2ubutnu-挂载磁盘)
- [grep 命令](#grep-命令)
- [3、ubuntu 终止进程](#3ubuntu-终止进程)
- [4、telnet 命令](#4telnet-命令)
- [5、netstat 命令](#5netstat-命令)
    - [示例输出](#示例输出)
    - [各列的含义](#各列的含义)
    - [常见连接状态](#常见连接状态)
    - [用途](#用途)


# 1、基本命令

```bash
# 更新软件
sudo apt update
sudo apt upgrade

# 在 files 中搜索字符串
grep [options] pattern [files]
# 例子
grep -i "Save HPP file success" ./*

# 在一个新的 shell 中执行一个命令，command 表示要执行的命令
sudo sh -c 'command'
```

```bash
# 终止进程
# 1. 使用 ps 命令来列出当前运行的进程，并找到想要终止的进程的 PID
ps aux | grep <进程名或关键字>
# 2. 立即终止进程，使用 -9 选项
kill -9 <PID>
```

# echo

```bash
# echo 命令用于在终端或脚本中打印文本
echo "Hello, World!"
```

# tar 解压文件

```bash
# tar 表示用来处理归档文件的命令，-x表示提取文件，-v表示详细显示解压的过程，-f后面跟着要解压的文件名
tar -xvf 文件名.tar

# 解压tar.gz 或 .tgz 结尾的gzip压缩的tar文件
tar -xzvf 文件名.tar.gz

# 解压 .tar.bz2格式的bzip2压缩的tar文件
tar -xjvf 文件名.tar.bz2

# 命令后添加 -C 目标文件夹 的方式来指定解压到的目标文件夹
tar -xvf 文件名.tar -C 目标文件夹
```

# Ubuntu 远程桌面连接

```bash
# 1.客户端/本地主机安装 Remmina
sudo apt update
sudo apt install remmina

# 2.远程主机/服务器安装xrdp
sudo apt update
sudo apt install xrdp
# 启动XRDP服务并使其开机自启
sudo systemctl enable xrdp
sudo systemctl start xrdp

# 2.1 黑屏问题
# https://zhuanlan.zhihu.com/p/519648451
# https://blog.csdn.net/m0_38101947/article/details/131010297
# 打开startwm.sh 
sudo vim /etc/xrdp/startwm.sh
# 添加配置文件
unset DBUS_SESSION_BUS_ADDRESS
unset XDG_RUNTIME_DIR
.$ HOME/.profile

# 2.2 桌面优化
vim ~/.xsessionrc

添加：

export GNOME_SHELL_SESSION_MODE=ubuntu
export XDG_CURRENT_DESKTOP=ubuntu:GNOME
export XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg
# 重启 xrdp 服务
sudo systemctl restart xrdp.service

要关闭xrdp服务并在Ubuntu系统上禁用其自动启动，请按照以下步骤操作：
1. **停止xrdp服务**：
   首先，停止xrdp服务。这可以通过以下命令完成：
   ```bash
   sudo systemctl stop xrdp
   sudo systemctl stop xrdp-sesman
   ```
2. **禁用xrdp服务**：
   禁用xrdp服务，以防止它在系统启动时自动运行：
   ```bash
   sudo systemctl disable xrdp
   sudo systemctl disable xrdp-sesman
   ```
3. **确认服务状态**：
   为了确认xrdp服务已经停止并且禁用，可以使用以下命令检查其状态：
   ```bash
   sudo systemctl status xrdp
   sudo systemctl status xrdp-sesman
   ```
   如果服务已经停止并且禁用，你将看到指示这些状态的信息。
关闭并禁用xrdp服务后，它将不会在系统启动时自动运行，也不会监听远程桌面连接。如果你以后需要重新启动服务，可以使用以下命令：
```bash
sudo systemctl start xrdp
sudo systemctl start xrdp-sesman
```
并且如果你想要再次启用自动启动，可以使用：
```bash
sudo systemctl enable xrdp
sudo systemctl enable xrdp-sesman
```

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/2a216569-2b28-44df-aa35-656e570399b8/d64f9085-a2e0-437d-b005-de00da4cc5f4/Untitled.png)


# 2、ubutnu 挂载磁盘

[ubuntu20.04挂载新硬盘_ubuntu20.04挂载硬盘-CSDN博客](https://blog.csdn.net/qq_43318374/article/details/131691723)

<aside>
💡 1. 查看所有磁盘：`lsblk`

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/2a216569-2b28-44df-aa35-656e570399b8/31e066dd-09dd-48a0-b055-a4e5db79e02b/Untitled.png)

2.找到设备名称：`sudo fdisk -l` 

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/2a216569-2b28-44df-aa35-656e570399b8/776b1785-4e8b-4921-adf5-494043735c3f/Untitled.png)

1. 格式化硬盘

```bash
# 格式化这两个分区
sudo mkfs -t ext4 /dev/sda1
sudo mkfs -t ext4 /dev/sda2
```

1. 在 `/home/mi` 目录下创建两个目录来挂载这两个分区

```bash
# 创建目录
mkdir /home/mi/download
mkdir /home/mi/software

# 使用mount来挂载
# 挂载分区1
sudo mount -t ext4 /dev/sda1 /home/mi/download
# 挂载分区2
sudo mount -t ext4 /dev/sda2 /home/mi/software

# 若显示 mount: /home/mi/下载: /dev/sda1 already mounted on /media/mi/系统.则可以执行以下命令：
# 卸载/dev/sda1
sudo umount /dev/sda1
# 或者卸载挂载点目录
sudo umount /media/mi/系统
# 再次使用mount命令挂载到/home/mi/download
sudo mount -t ext4 /dev/sda1 /home/mi/download
```

1. 增加权限

```bash
# mi为你的用户名和用户组名
sudo chown mi:mi /home/mi/download
sudo chmod 755 /home/mi/download
```

1. 设置开机自动挂载

```bash
sudo vim /etc/fstab
# 最后一行添加
/dev/sda1 /home/mi/download ext4 defaults 0 2
/dev/sda2 /home/mi/software ext4 defaults 0 2
```

1. 查看是否挂载成功

```bash
df -h
```

</aside>

# grep 命令

`grep` 是一个强大的文本搜索工具，用于在文件中搜索指定的字符串或模式，并输出包含该字符串的行。`grep` 命令的格式通常如下：

```
grep [选项] [模式] [文件...]

```

下面是一些常用的 `grep` 选项：

- `i`: 忽略大小写。
- `v`: 反向选择，即输出不包含模式的行。
- `c`: 只输出匹配行的计数。
- `n`: 显示匹配行及其行号。
- `l`: 只输出包含匹配模式的文件名。
- `L`: 只输出不包含匹配模式的文件名。
- `r` 或 `R`: 递归搜索目录中的所有文件。
- `E`: 使用扩展的正则表达式。
- `o`: 只输出匹配到的部分，而不是整行。
- `A [num]`: 输出匹配行及其后[num]行。
- `B [num]`: 输出匹配行及其前[num]行。
- `C [num]` 或 `-context=[num]`: 输出匹配行及其前后的[num]行。
- `e [模式]`: 指定多个搜索模式。
- `f [文件]`: 从文件中读取搜索模式。
- `q`: 静默模式，不输出任何内容，仅用于检查是否匹配。
- `-color[=auto]`: 将匹配的文本高亮显示。
例如，要在文件 `example.txt` 中搜索字符串 "hello"，并显示包含该字符串的行，可以使用以下命令：

```
grep "hello" example.txt
```

要在多个文件中搜索并忽略大小写，可以使用：

```
grep -i "Hello" file1.txt file2.txt
```

要递归搜索目录中的所有文件，并输出不包含指定模式的行，可以使用：

```
grep -v -r "pattern" /path/to/directory
```

`grep` 还支持正则表达式，允许你进行更复杂的文本匹配。例如，要匹配以 "he" 开头，以 "o" 结尾的行，可以使用：

```
grep "^he.*o$" example.txt
```

这里的 `^` 表示行的开头，`$` 表示行的结尾，`.` 表示任意字符，`*` 表示前一个字符出现零次或多次。

# 3、ubuntu 终止进程

Ubuntu 中，你可以使用 **`kill`** 命令来终止进程。有两种常见的方式来使用 **`kill`** 命令：

1. **使用进程 ID (PID) 终止进程：**
    
    首先，你需要找到要终止的进程的进程 ID。可以使用 **`ps`** 命令来列出当前运行的进程，并找到你想要终止的进程的 PID。例如：
    
    ```bash
    ps aux | grep <进程名或关键字>
    ```
    
    然后，使用 **`kill`** 命令终止进程，将 **`<PID>`** 替换为实际的进程 ID：
    
    ```bash
    kill <PID>
    ```
    
    例如，如果要终止 PID 为 1234 的进程：
    
    ```bash
    bashCopy code
    kill 1234
    ```
    
2. **使用进程名称终止进程：**
    
    如果你知道进程的名称，也可以使用 **`pkill`** 命令。例如，要终止名为 **`process_name`** 的进程：
    
    ```bash
    bashCopy code
    pkill process_name
    ```
    

请注意，**`kill`** 命令默认发送 TERM 信号，这是一个优雅的终止信号，允许进程完成清理工作。如果需要立即终止进程，你可以使用 **`-9`** 选项：

```bash
bashCopy code
kill -9 <PID>
```

或者对于 **`pkill`**：

```bash
bashCopy code
pkill -9 process_name
```

但要注意，强制终止进程可能导致数据丢失或其他问题，应尽量避免过度使用。

# 4、telnet 命令

`telnet` 是一个用于在计算机之间建立交互式通信会话的网络协议和命令行工具。它通常用于以下目的：

1. **测试网络连接**：通过 `telnet` 命令，可以测试计算机和远程主机之间的连接是否正常。比如，检查某个端口是否开放。
2. **远程管理**：在早期，`telnet` 常用于远程登录到其他计算机，执行管理任务。但由于它不加密通信数据，现在不再推荐用于这个目的。
3. **调试和诊断**：网络管理员和开发人员使用 `telnet` 来调试网络服务和应用程序，确保它们按预期工作。

`telnet` 命令的基本语法是：

```bash
# 安装 telnet
sudo apt-get install telnet

telnet [hostname or IP address] [port]
# 要检查主机 example.com 的端口 80 是否开放，可以使用
telnet example.com 80

# 测试端口
# 要测试某个主机的特定端口是否开放，例如检查 example.com 的端口 25（通常用于邮件服务）
telnet example.com 25
# 可以手动发送 HTTP 请求，检查服务器响应
telnet example.com 80
# 连接成功后，输入以下内容。然后按两次回车键，服务器应该返回 HTTP 响应头和正文。
GET / HTTP/1.1
Host: example.com
```

# 5、netstat 命令

`sudo netstat -tanp` 是一个用于**查看网络连接和端口使用情况的命令**，具体选项的含义如下：

- `sudo`：以超级用户（root）权限运行命令，因为有些网络连接信息只有超级用户才能查看。
- `netstat`：网络统计工具，显示网络连接、路由表、接口统计、伪装连接、多播成员等。
- `t`：仅显示 TCP 连接。
- `a`：显示所有连接和监听端口。
- `n`：以数字形式显示地址和端口号，而不是尝试解析主机名和服务名。
- `p`：显示使用连接的程序的 PID 和名称。

### 示例输出

运行 `sudo netstat -tanp` 可能会产生类似于以下的输出：

```
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name
tcp        0      0 127.0.0.1:3306          0.0.0.0:*               LISTEN      1234/mysqld
tcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN      789/sshd
tcp        0      0 192.168.0.100:55432     93.184.216.34:80        ESTABLISHED 4567/chrome

```

### 各列的含义

- `Proto`：协议类型（例如，TCP）。
- `Recv-Q`：接收队列中等待处理的字节数。
- `Send-Q`：发送队列中等待处理的字节数。
- `Local Address`：本地地址和端口号。
- `Foreign Address`：远程地址和端口号。
- `State`：连接状态（例如，LISTEN，ESTABLISHED）。
- `PID/Program name`：使用该连接的进程 ID 和进程名称。

### 常见连接状态

- `LISTEN`：服务器在监听等待连接。
- `ESTABLISHED`：连接已建立并正在通信。
- `CLOSE_WAIT`：一方已关闭连接，等待关闭完成。
- `TIME_WAIT`：连接已关闭，等待一段时间以确保远程端收到关闭确认。

### 用途

- **排查网络问题**：查看当前哪些端口在监听，哪些连接是活跃的，排查网络问题。
- **安全性检查**：查看是否有不明进程在监听端口，防止安全漏洞。
- **性能监控**：监控网络连接数量和状态，识别可能的瓶颈或问题。

通过这个命令，你可以获得系统中所有 TCP 连接的详细信息，这对于网络诊断和管理非常有用。