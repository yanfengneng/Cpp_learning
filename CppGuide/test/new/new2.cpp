#include <bits/stdc++.h>

int main() 
{
  long long num =
      0x7fffffff;  // 0x7fffffff = 2,147,483,647 = 2047*1024*1024 = 2047M
  char* p = nullptr;

  // vs2015 x86 error C2148: 数组的总大小不得超过 0x7fffffff 字节
  p = new (std::nothrow) char[2047 * 1024 * 1024];  /// 1024 * 1024 * 1024
  if (nullptr == p) {
    std::cerr << " new (std::nothrow)char[2047 * 1024 * 1024] 内存分配失败"
              << std::endl;
  } else {
    std::cout << " new (std::nothrow)char[2047 * 1024 * 1024] 内存分配成功"
              << std::endl;
  }

  return 0;
}