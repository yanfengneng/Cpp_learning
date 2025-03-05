#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  mtrace();  // 开始跟踪

  char *p = (char *)malloc(100);

  free(p);
  p = NULL;

  p = (char *)malloc(100);

  muntrace();  // 结束跟踪，并生成日志信息

  return 0;
}
