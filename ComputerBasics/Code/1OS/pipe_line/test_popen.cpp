#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fp;
  char path[1035];

  // /* 打开用于读取的管道 */
  // fp = popen("ls -l", "r");
  // if (fp == NULL) {
  //   printf("Failed to run command\n");
  //   exit(1);
  // }

  // /* 读取命令的输出一行一行地读取 */
  // while (fgets(path, sizeof(path), fp) != NULL) {
  //   printf("%s", path);
  // }

  // /* 关闭管道 */
  // pclose(fp);
  FILE *fpr = NULL, *fpw = NULL;
  char buf[256];
  int ret;
  // 执行完这行代码，标准输出就装满，这里这个标准输出标记为out1，
  // 管道指向out1，fpr指向管道的读端。执行这句代码，会一直去读取标准输出，
  // 若标准输出为空，则会阻塞，直到标准输出不为空，执行命令后又会去指
  // 读取标准输出继续执行。这里这个标准输入标记为in2。
  // 管道指向int2，fpw指向管道的写端。
  fpr = popen("cat /etc/group", "r");
  fpw = popen("grep root", "w");
  // 从out1中读取256个字节数据，存放在buf中。
  while ((ret = fread(buf, 1, sizeof(buf), fpr)) > 0) {
    // 将buf的数据写到int2(此时gerp命令一直在获取int2，直到进行退出)。
    fwrite(buf, 1, ret, fpw);
  }
  pclose(fpr);
  pclose(fpw);
  return 0;
}
