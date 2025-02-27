#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  if (pid == 0) {  // 子进程
    printf("Child executing ls -l\n");
    execlp("ls", "ls", "-l", NULL);
    perror("execlp failed");  // 只有出错时执行
    exit(EXIT_FAILURE);
  } else if (pid > 0) {  // 父进程
    wait(NULL);          // 等待子进程结束
    printf("Child completed.\n");
  } else {
    perror("fork failed");
    exit(EXIT_FAILURE);
  }
  return 0;
}
