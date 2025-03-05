#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd;
  int ret;
  ret = mkfifo("my_fifo", 0666);  // 创建命名管道
  if (ret != 0) {
    perror("mkfifo");
  }
  fd = open("my_fifo", O_WRONLY);  // 等着只读
  if (fd < 0) {
    perror("open fifo");
  }
  char send[100] = "Hello World";
  write(fd, send, strlen(send));  // 写数据
  printf("write to my_fifo buf=%s\n", send);
  while (1);  // 阻塞，保证读写进程保持着通信过程
  close(fd);
  return 0;
}
