#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
using namespace std;

int main() {
  // 子进程中fork()函数返回 0，在父进程中fork()函数返回子进程的进程ID
  // 正常执行是先执行父进程，然后在执行子进程
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