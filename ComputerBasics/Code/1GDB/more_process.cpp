#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
  pid_t pid = fork();
  if (-1 == pid) {
    perror("fork error.\n");
    return -1;
  }

  if(0 == pid) { // 子进程
    int num = 1;
    while(num == 10) {
      sleep(10);
    }
    printf("This is child, pid = %d.\n", getpid());
  }
  else { // 父进程
    printf("This is parent, pid = %d.\n", getpid());
    wait(NULL); // 等待子进程退出
  }
}