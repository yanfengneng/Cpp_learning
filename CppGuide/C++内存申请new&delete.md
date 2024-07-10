这里对 new 运算符做一个简单的记录。

[C++中new和std::nothrow的使用避免抛异常](https://blog.csdn.net/a_Treasure/article/details/82106638)、[C++中nothrow的介绍及使用](https://blog.csdn.net/fengbingchun/article/details/63686673)

先总结下：

* 1）在 C 语言中，使用 `malloc` 等函数分配内存的函数时，一定要检查**其返回值是否为空指针**，并以此作为检查内存操作是否成功的依据。这种方式称为 `Test-For-NULL`。
* 2）在 C++ 中使用 new 申请内存时，若失败则抛出一个 `std::bad_alloc` 的异常。出现这个异常则表示**内存耗尽**，或是其他原因导致内存分配失败。按照 C++ 标准，如果想检查 new 是否成功，则应该通过 `try catch` 捕捉异常，但有些编译器不支持 `try catch`。C++标准化委员会不想遗弃这些 `Test-for-NULL` 的代码，所以他们提供了 `operator new` 的另一种可选形式---- `std::nothrow`，用以提供传统的 `Failure-yields-NULL` 行为。

# 1、std::bad_alloc

在使用 `new` 和 `new[]` 申请内存分配失败时会抛出 `std::bad_alloc` 的异常，此时申请内存的指针 `p` 不为 `nullptr`。

* 坏处：没法进行 `Test-for-NULL` 检查，同时记住使用 `Test-For-NULL` 是一个好习惯。

```cpp
#include <iostream>
#include <new>  // std::bad_alloc

int main() {
  long long num =
      0x7fffffff;  // 0x7fffffff = 2,147,483,647 = 2047*1024*1024 = 2047M
  char *p = nullptr;

  try {
    // vs2015 x86 error C2148: 数组的总大小不得超过 0x7fffffff 字节
    // 使用 new 来申请内存分配时，分配异常会报 bad_alloc
    // 的异常，而且此时申请内存分配的指针 p 不为空
    p = new char[2047 * 1024 * 1024];  /// 1024 * 1024 * 1024
  } catch (std::bad_alloc &ba) {
    std::cerr << "bad_alloc caught: " << ba.what()
              << '\n';  // bad_alloc caught: bad allocation
  }
  delete[] p;
  return 0;
}
```



# 2、std::nothrow

使用 `new (std::nothrow)` 在申请内存分配失败时，会返回一个空指针。而不是触发 `std::bad_alloc`，可以方便地进行 `Test-For-NULL` 检查。

```cpp
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
```

