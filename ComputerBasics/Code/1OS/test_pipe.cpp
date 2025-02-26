#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd[2];  // 定义文件描述符
  pid_t pid;
  char str[1024] = "hello\n";
  char buf[1024];
  if (pipe(fd) < 0)  // 创建管道，成功返回0，失败返回-1
  {
    perror("pipe");
    exit(1);
  }
  pid = fork();  // 创建一个子进程
  // 功能：父写子读
  if (pid > 0)  // 父进程
  {
    close(fd[0]);  // 父进程关闭读端
    sleep(2);
    write(fd[1], str, strlen(str));  // 向管道里写数据
    wait(NULL);                      // 回收子进程
  } else if (pid == 0)               // 子进程
  {
    close(fd[1]);                             // 子进程关闭写端
    int len = read(fd[0], buf, sizeof(buf));  // 从管道里读数据
    write(STDOUT_FILENO, buf, len);           // 把读到的数据写到标准输出
  } else                                      // 创建子进程失败
  {
    perror("fork");
    exit(1);
  }
  return 0;
}
