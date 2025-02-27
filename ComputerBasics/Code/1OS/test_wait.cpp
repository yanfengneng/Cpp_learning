#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid == 0) {  // 子进程
    printf("Child process (PID=%d) running.\n", getpid());
    sleep(2);
    exit(42);            // 子进程退出码设为 42
  } else if (pid > 0) {  // 父进程
    int status;
    pid_t child_pid = wait(&status);  // 等待子进程终止

    if (child_pid == -1) {
      perror("wait failed");
      exit(EXIT_FAILURE);
    }

    if (WIFEXITED(status)) {
      printf("Child (PID=%d) exited with code %d.\n", child_pid,
             WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
      printf("Child killed by signal %d.\n", WTERMSIG(status));
    }
  } else {  // fork 失败
    perror("fork failed");
    exit(EXIT_FAILURE);
  }

  return 0;
}
