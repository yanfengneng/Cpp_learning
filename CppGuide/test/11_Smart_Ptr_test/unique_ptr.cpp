#include <type_traits>  // for std::enable_if_t, std::is_convertible_v
#include <utility>      // for std::swap, std::move
#include <iostream>

// 处理单一对象
template <typename T>
struct default_delete {
  void operator()(T* p) const { delete p; }
};

// 数组特化：处理数组对象
template <typename T>
struct default_delete<T[]> {
  void operator()(T* p) const noexcept { delete[] p; }
};

template <typename T, typename Deleter = default_delete<T>>
class Unique_Ptr {
 private:
  T* ptr_;
  Deleter deleter;

 public:
  // 使用 explicit 防止隐式转换
  explicit Unique_Ptr(T* p = nullptr, Deleter d = Deleter()) noexcept
      : ptr_(p), deleter(std::move(d)) {}

  // 移动构造
  Unique_Ptr(Unique_Ptr&& other) noexcept
      : ptr_(other.ptr_), deleter(std::move(other.deleter)) {
    other.ptr_ = nullptr;
  }

  // 支持派生类到基类的转换，允许兼容的删除器
  template <typename U, typename E,
            typename = std::enable_if_t<std::is_convertible_v<U*, T*> &&
                                        std::is_constructible_v<Deleter, E&&>>>
  Unique_Ptr(Unique_Ptr<U, E>&& other) noexcept
      : ptr_(other.release()), deleter(std::move(other.get_deleter())) {}

  // 析构
  ~Unique_Ptr() { reset(); }

  // 禁用拷贝
  Unique_Ptr(const Unique_Ptr&) = delete;
  Unique_Ptr& operator=(const Unique_Ptr&) = delete;

  // 移动赋值
  Unique_Ptr& operator=(Unique_Ptr&& other) noexcept {
    if (this != &other) {
      reset(other.release());
      deleter = std::move(other.deleter);
    }
    return *this;
  }

  // 释放所有权
  T* release() noexcept {
    T* p = ptr_;
    ptr_ = nullptr;
    return p;
  }

  // 重置指针
  void reset(T* p = nullptr) noexcept {
    if (ptr_) {
      deleter(ptr_);
    }
    ptr_ = p;
  }

  // 访问原始指针
  T* get() const noexcept { return ptr_; }

  // 解引用操作符
  T& operator*() const noexcept { return *ptr_; }
  T* operator->() const noexcept { return ptr_; }

  // 显式 bool 转换
  explicit operator bool() const noexcept { return ptr_ != nullptr; }

  // 交换
  void swap(Unique_Ptr& other) noexcept {
    using std::swap;
    swap(ptr_, other.ptr_);
    swap(deleter, other.deleter);
  }

  // 获取删除器
  Deleter& get_deleter() noexcept { return deleter; }
  const Deleter& get_deleter() const noexcept { return deleter; }
};

// 数组特化版本
template <typename T, typename Deleter>
class Unique_Ptr<T[], Deleter> {
 public:
  explicit Unique_Ptr(T* p = nullptr, Deleter d = Deleter()) noexcept
      : ptr_(p), deleter(std::move(d)) {}

  ~Unique_Ptr() { reset(); }

  // 移动构造
  Unique_Ptr(Unique_Ptr&& other) noexcept
      : ptr_(other.ptr_), deleter(std::move(other.deleter)) {
    other.ptr_ = nullptr;
  }

  // 禁用拷贝
  Unique_Ptr(const Unique_Ptr&) = delete;
  Unique_Ptr& operator=(const Unique_Ptr&) = delete;

  // 移动赋值
  Unique_Ptr& operator=(Unique_Ptr&& other) noexcept {
    if (this != &other) {
      reset(other.release());
      deleter = std::move(other.deleter);
    }
    return *this;
  }

  // 释放所有权
  T* release() noexcept {
    T* p = ptr_;
    ptr_ = nullptr;
    return p;
  }

  // 重置指针
  void reset(T* p = nullptr) noexcept {
    if (ptr_) {
      deleter(ptr_);
    }
    ptr_ = p;
  }

  // 数组下标访问
  T& operator[](size_t idx) const { return ptr_[idx]; }

  // 其他接口与主模板一致
  T* get() const noexcept { return ptr_; }
  explicit operator bool() const noexcept { return ptr_ != nullptr; }
  void swap(Unique_Ptr& other) noexcept {
    using std::swap;
    swap(ptr_, other.ptr_);
    swap(deleter, other.deleter);
  }
  Deleter& get_deleter() noexcept { return deleter; }
  const Deleter& get_deleter() const noexcept { return deleter; }

 private:
  T* ptr_;
  Deleter deleter;
};

// 工厂函数
// template <typename T, typename... Args>
// Unique_Ptr<T> make_unique(Args&&... args) {
//   return Unique_Ptr<T>(new T(std::forward<Args>(args)...));
// }
template <typename T, typename... Args>
std::enable_if_t<!std::is_array_v<T>, Unique_Ptr<T>> // SFINAE 约束
make_unique(Args&&... args) {
  return Unique_Ptr<T>(new T(std::forward<Args>(args)...));
}
// // 数组版本工厂
// template <typename T>
// Unique_Ptr<T[]> make_unique(size_t size) {
//   return Unique_Ptr<T[]>(new T[size]);
// }
template <typename T>
typename std::enable_if_t<std::is_array_v<T> && (std::extent_v<T> == 0), Unique_Ptr<T>>
make_unique(size_t size) {
  using element_type = std::remove_extent_t<T>;
  return Unique_Ptr<T>(new element_type[size]);
}

int main() {
  // 管理单个对象
  Unique_Ptr<int> p1 = make_unique<int>(42);
  std::cout << *p1 << std::endl;  // 42

  // 管理数组
  Unique_Ptr<int[]> arr = make_unique<int[]>(5);
  arr[0] = 10;
  std::cout << arr[0] << std::endl;

  // 自定义删除器
  struct FileDeleter {
    void operator()(FILE* f) noexcept {
      if (f) {
        fclose(f);
        std::cout << "File closed.\n";
      }
    }
  };

  FILE* fp = fopen("test.txt", "w");
  Unique_Ptr<FILE, FileDeleter> file(fp, FileDeleter());
  return 0;
}
