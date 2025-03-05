#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define MSG_STR "Hello, my child! How are you?"

int main(int argc, char *argv[]) {
  int pipe_fd[2];
  int rv = -1;
  int pid;
  int w_status;
  char buf[64];

  pipe(pipe_fd);  // 创建管道

  if ((pid = fork()) < 0)  // 创建进程
  {
    printf("fork failure: %s\n", strerror(errno));
    return -1;
  } else if (0 == pid)  // 子进程,读消息
  {
    close(pipe_fd[1]);  // 关闭写端

    memset(buf, 0, sizeof(buf));
    rv = read(pipe_fd[0], buf, sizeof(buf));  // 开始读，没有消息就等待
    if (rv < 0) {
      printf("read failure: %s\n", strerror(errno));
      return -1;
    }
    printf("Child read data from parent: %s\n", buf);
  } else  // 父进程，写内容
  {
    close(pipe_fd[0]);  // 关闭读端

    write(pipe_fd[1], MSG_STR, strlen(MSG_STR));  // 写数据

    wait(&w_status);
  }

  return 0;
}
