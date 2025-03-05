#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define _SCHED_H
#define __USE_GNU
#include <bits/sched.h>

#define STACK_SIZE 40960

int func(void *arg) {
  printf("thread enter.\n");
  sleep(1);
  printf("thread exit.\n");

  return 0;
}

int main() {
  int thread_pid;
  int status;
  int w;

  while (1) {
    void *addr = mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
    if (addr == NULL) {
      perror("mmap");
      goto error;
    }
    printf("creat new thread...\n");
    thread_pid = clone(&func, addr + STACK_SIZE,
                       CLONE_SIGHAND | CLONE_FS | CLONE_VM | CLONE_FILES, NULL);
    printf("Done! Thread pid: %d\n", thread_pid);
    if (thread_pid != -1) {
      do {
        w = waitpid(-1, NULL, __WCLONE | __WALL);
        if (w == -1) {
          perror("waitpid");
          goto error;
        }
      } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    sleep(10);
  }

error:
  return 0;
}
