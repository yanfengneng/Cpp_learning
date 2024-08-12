- [关键概念和类](#关键概念和类)
  - [1. **`std::chrono::duration`**](#1-stdchronoduration)
  - [2. **`std::chrono::time_point`**](#2-stdchronotime_point)
  - [3. **`std::chrono::system_clock`**](#3-stdchronosystem_clock)
  - [4. **`std::chrono::steady_clock`**](#4-stdchronosteady_clock)
  - [5. **`std::chrono::high_resolution_clock`**](#5-stdchronohigh_resolution_clock)
- [常用操作](#常用操作)
- [例子](#例子)
- [总结](#总结)

[c++ 标准库chrono 中duration、timepoint和clock的使用方法](https://blog.csdn.net/qq_33944628/article/details/130396296)、[C++ std::chrono库使用指南 (实现C++ 获取日期,时间戳,计时等功能)](https://blog.csdn.net/qq_21438461/article/details/131198438)

`std::chrono` 是 C++ 标准库中的一个时间处理库，提供了与时间相关的类型和功能。`std::chrono` 的设计基于 C++11，并引入了时间点、时间间隔和时钟等概念，用于简化和统一时间处理操作。

### 关键概念和类

#### 1. **`std::chrono::duration`**
   
`std::chrono::duration` 表示一个时间间隔（持续时间），即某种时间单位（如秒、毫秒、纳秒）内经过的时间。

- **模板参数**:
  - `Rep`（表示类型）: 时间单位的数值类型，通常是 `int` 或 `double`。
  - `Period`（周期）: 时间单位的类型，如秒 (`std::ratio<1>`) 或毫秒 (`std::milli`)。

- **常用成员函数**:
  - `count()` : 返回持续时间对象中的数值。
  - `zero()` : 返回一个持续时间为零的 `duration` 对象。
  - `min()` : 返回最小可能的持续时间。
  - `max()` : 返回最大可能的持续时间。

- **预定义类型**:
  - `std::chrono::nanoseconds` : 表示纳秒 (`std::chrono::duration<int64_t, std::nano>`).
  - `std::chrono::microseconds` : 表示微秒 (`std::chrono::duration<int64_t, std::micro>`).
  - `std::chrono::milliseconds` : 表示毫秒 (`std::chrono::duration<int64_t, std::milli>`).
  - `std::chrono::seconds` : 表示秒 (`std::chrono::duration<int64_t>`).
  - `std::chrono::minutes` : 表示分钟 (`std::chrono::duration<int64_t, std::ratio<60>>`).
  - `std::chrono::hours` : 表示小时 (`std::chrono::duration<int64_t, std::ratio<3600>>`).

#### 2. **`std::chrono::time_point`**

`std::chrono::time_point` 表示一个时间点，通常与某个时钟相关联，用于记录或计算特定的时间点。

- **模板参数**:
  - `Clock` : 时钟类型，指定时间点的来源时钟。
  - `Duration` : 持续时间类型，表示从起点到时间点的持续时间。

- **常用成员函数**:
  - `time_since_epoch()` : 返回自时钟纪元（epoch）以来的持续时间。
  - `now()` : 获取当前时间点（静态成员函数，与时钟类型相关联）。
  - `min()` : 返回最小可能的时间点。
  - `max()` : 返回最大可能的时间点。

#### 3. **`std::chrono::system_clock`**

`std::chrono::system_clock` 是一个代表系统时钟的类，通常用于获取当前时间和时间点。

- **常用成员函数**:
  - `now()` : 返回当前的系统时间点。
  - `to_time_t(const time_point&)` : 将 `time_point` 转换为 C 风格的 `std::time_t` 时间。
  - `from_time_t(std::time_t)` : 将 `std::time_t` 转换为 `time_point`。

#### 4. **`std::chrono::steady_clock`**

`std::chrono::steady_clock` 是一个单调时钟，不能倒退，适用于测量时间间隔。

- **常用成员函数**:
  - `now()` : 返回当前的时间点。

#### 5. **`std::chrono::high_resolution_clock`**

`std::chrono::high_resolution_clock` 是一个高分辨率时钟，通常是 `system_clock` 或 `steady_clock` 的别名，用于测量高精度的时间间隔。

- **常用成员函数**:
  - `now()` : 返回当前的时间点。

### 常用操作

- **时间点与时间点之间的相减**:
  - 两个时间点之间的差值是一个 `std::chrono::duration` 对象。
  ```cpp
  auto diff = end_time - start_time;
  ```

- **时间点加上持续时间**:
  - 可以将一个 `std::chrono::duration` 对象加到 `std::chrono::time_point` 对象上，得到一个新的时间点。
  ```cpp
  auto later = start_time + std::chrono::seconds(10);
  ```

- **持续时间的单位转换**:
  - 使用 `std::chrono::duration_cast` 进行不同时间单位间的转换。
  ```cpp
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
  ```

- **线程睡眠**:
  - 使用 `std::this_thread::sleep_for` 或 `std::this_thread::sleep_until` 让线程休眠指定的持续时间或直到指定的时间点。
  ```cpp
  std::this_thread::sleep_for(std::chrono::seconds(1));
  ```

### 例子

```cpp
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 休眠 500 毫秒
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "睡眠时间: " << duration.count() << " 毫秒" << std::endl;

    return 0;
}
```

### 总结

`std::chrono` 提供了强大的时间处理工具，涵盖了时间点、时间间隔、时钟等基本概念，支持高精度时间测量和线程休眠等操作。在多线程编程和性能分析中，`std::chrono` 是一个不可或缺的工具。