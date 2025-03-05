#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("main func addr:%p\n", main);
  printf("start malloc\n");
  // char* pc1 = malloc(10);
  // char* pc2 = malloc(10);
  // char* pc3 = calloc(10, 1);
  // pc2 = realloc(pc2, 20);
  char* pc1 = (char*)malloc(10);
  char* pc2 = (char*)malloc(10);
  char* pc3 = (char*)calloc(10, 1);
  pc2 = (char*)realloc(pc2, 20);
  printf("start free\n");
  free(pc1);
  free(pc2);
  free(pc3);
}
