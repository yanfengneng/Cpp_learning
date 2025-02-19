#include <iostream>
using namespace std;

void hello() {
  printf("hello world!\n");
}

int main()
{
  int a[4] = {1, 2, 3, 4};
  int i = 0;
  for(i = 0; i < 4; i++) {
    printf("%d\n", a[i]);
  }
  hello();
  return 0;
}
