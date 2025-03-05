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
  fd = open("my_fifo", O_RDONLY);  // 等着只写
  if (fd < 0) {
    perror("open fifo");
  }
  while (1) {
    char recv[100] = {0};
    read(fd, recv, sizeof(recv));  // 读数据
    printf("read from my_fifo buf=[%s]\n", recv);
    sleep(1);
  }
  close(fd);
  return 0;
}
