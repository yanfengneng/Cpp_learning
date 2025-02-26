#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
using namespace std;

int main()
{
  printf("++process %d start running! ppid = %d\n", getpid(), getppid());
  // 子进程中fork()函数返回 0，在父进程中fork()函数返回子进程的进程ID
  pid_t pid = fork();

  // fork 完成之后先执行进程，然后再执行父进  (gdb) set follow-fork-mode child  (gdb) set follow-fork-mode child  (gdb) set follow-fork-mode child程
  if (pid == 0) // 在子进程中
  {
    printf("++child process %d start running! ppid = %d\n", getpid(), getppid());
    sleep(2);
    printf("++child process %d stop running! ppid = %d\n", getpid(), getppid());
  }
  else if (pid > 0) // 在父进程中
  {
    printf("++parent process %d start running! ppid = %d\n", getpid(), getppid());
    sleep(2);
    printf("++parent process %d stop running! ppid = %d\n", getpid(), getppid());
  }
  else
  {
    printf("++fork failed!\n");
  }
  return 0;
}