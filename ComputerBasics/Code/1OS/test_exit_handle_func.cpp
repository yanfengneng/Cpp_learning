#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void func1(void) { printf("%s\n", __func__); }

void func2(void) { printf("%s\n", __func__); }

void func3(void) { printf("%s\n", __func__); }

int main() {
  atexit(func1);  // 先登记
  atexit(func2);
  atexit(func3);

  printf("hello!\n");

  // exit(0);
  // _exit(0); // 无法调用退出处理函数
  // return 0; // 无法调用退出处理函数
}

/**
 * 退出处理函数是在程序正常退出时调用的，而_exit()和return 0;是直接退出程序，不会调用退出处理函数。
 * exit()会调用退出处理函数，然后调用_exit()退出程序。
 * 调用 exit(0) 的输出结果为：hello，func3 -> func2 -> func1。
 * 调用 _exit(0) 的输出结果为：hello。
 * 调用 return 0; 的输出结果为：hello。
*/
