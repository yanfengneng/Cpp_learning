#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void* pthread_run1(void* arg) {
  (void)arg;

  while (1) {
    printf("I am thread1,ID: %ld\n", pthread_self());
    sleep(1);
  }
}

void* pthread_run2(void* arg) {
  (void)arg;

  while (1) {
    printf("I am thread2,ID: %ld\n", pthread_self());
    sleep(1);
  }
}

int main() {
  pthread_t tid1;
  pthread_t tid2;

  pthread_create(&tid1, NULL, pthread_run1, NULL);
  pthread_create(&tid2, NULL, pthread_run2, NULL);

  printf("I am main thread\n");

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  return 0;
}
