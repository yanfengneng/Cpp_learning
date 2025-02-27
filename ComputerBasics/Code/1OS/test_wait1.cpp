#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  // 在子进程中`fork()` 函数返回 0，在父进程中 `fork()` 函数返回子进程的线程
  // ID。
  // pid_t pid = fork();
  // if (!pid) {  // 子1
  //   printf("child %d start running!\n", getpid());
  //   sleep(10);
  //   printf("child exit!\n");
  //   exit(10);  // 子进程退出码设为 10
  // }

  // pid = fork();
  // if (!pid) {  // 子2
  //   printf("child %d start running!\n", getpid());
  //   sleep(15);
  //   printf("child exit!\n");
  //   exit(30);  // 子进程退出码设为 30
  // }

  // // 父进程
  // // 等待子进程结束
  // int status = 0;
  // pid_t pid1 = 0;
  // pid1 = wait(&status);  // 等待任意一个子进程的结束
  // if (WIFEXITED(status)) {
  //   printf("%d正常结束!退出码 = %d\n", pid1, WEXITSTATUS(status));
  // }
  // if (WIFSIGNALED(status)) {
  //   printf("%d被信号打断!信号 = %d\n", pid1, WTERMSIG(status));
  // }

  // pid1 = wait(&status);  // 等待任意一个子进程的结束
  // if (WIFEXITED(status)) {
  //   printf("%d正常结束!退出码 = %d\n", pid1, WEXITSTATUS(status));
  // }
  // if (WIFSIGNALED(status)) {
  //   printf("%d被信号打断!信号 = %d\n", pid1, WTERMSIG(status));
  // }
  // 父进程
  // 等待子进程结束
  pid_t pid1 = fork();
  if(!pid1){//子1
      printf("child1  %d start running!\n",getpid());
      sleep(1);
      printf("child1 exit!\n");
      exit(10);
  }

  pid_t pid2 = fork();
  if(!pid2){//子2
      printf("child2  %d start running!\n",getpid());
      while(1);
      printf("child2 exit!\n");
      exit(30);
  }
  
  // 父进程
  // 等待子进程结束
  int status = 0;
  pid_t pid = 0;
  printf("等待child2结束 \n");
  pid = waitpid(pid2,&status,0);//指定子进程,堵塞
  if(pid==0){
      printf("没有等到子进程!\n");
      return -1;
  }
  printf("child2结束 \n");


  if(WIFEXITED(status)){
      printf("%d正常结束!退出码 = %d\n",pid1,WEXITSTATUS(status));
  }
  if(WIFSIGNALED(status)){
      printf("%d被信号打断!信号 = %d\n",pid1,WTERMSIG(status));
  }


  return 0;
}
