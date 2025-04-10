#include <type_traits>  // for std::enable_if_t, std::is_convertible_v
#include <utility>      // for std::swap, std::move

template <typename T>
struct default_delete
{
  void operator()(T* p) const {
    delete p;
  }
};

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
 public:
  // 默认构造
  unique_ptr() noexcept : ptr(nullptr), deleter() {}

  // 接管裸指针
  explicit unique_ptr(T* p) noexcept : ptr(p), deleter() {}
  unique_ptr(T* p, Deleter d) noexcept : ptr(p), deleter(std::move(d)) {}

  // 移动构造
  unique_ptr(unique_ptr&& other) noexcept
      : ptr(other.ptr), deleter(std::move(other.deleter)) {
    other.ptr = nullptr;
  }

  // 支持派生类到基类的转换
  template <typename U, typename E,
            typename = std::enable_if_t<std::is_convertible_v<U*, T*> &&
                                        std::is_same_v<Deleter, E>>>
  unique_ptr(unique_ptr<U, E>&& other) noexcept
      : ptr(other.release()), deleter(std::move(other.get_deleter())) {}

  // 析构
  ~unique_ptr() { reset(); }

  // 禁用拷贝
  unique_ptr(const unique_ptr&) = delete;
  unique_ptr& operator=(const unique_ptr&) = delete;

  // 移动赋值
  unique_ptr& operator=(unique_ptr&& other) noexcept {
    if (this != &other) {
      reset(other.release());
      deleter = std::move(other.deleter);
    }
    return *this;
  }

  // 释放所有权
  T* release() noexcept {
    T* p = ptr;
    ptr = nullptr;
    return p;
  }

  // 重置指针
  void reset(T* p = nullptr) noexcept {
    if (ptr != p) {
      deleter(ptr);
      ptr = p;
    }
  }

  // 访问原始指针
  T* get() const noexcept { return ptr; }

  // 解引用操作符
  T& operator*() const noexcept { return *ptr; }
  T* operator->() const noexcept { return ptr; }

  // 显式 bool 转换
  explicit operator bool() const noexcept { return ptr != nullptr; }

  // 交换
  void swap(unique_ptr& other) noexcept {
    using std::swap;
    swap(ptr, other.ptr);
    swap(deleter, other.deleter);
  }

  // 获取删除器
  Deleter& get_deleter() noexcept { return deleter; }
  const Deleter& get_deleter() const noexcept { return deleter; }

 private:
  T* ptr;
  Deleter deleter;
};

// 数组特化版本
template <typename T, typename Deleter>
class unique_ptr<T[], Deleter> {
 public:
  unique_ptr() noexcept : ptr(nullptr), deleter() {}
  explicit unique_ptr(T* p) noexcept : ptr(p), deleter() {}
  unique_ptr(T* p, Deleter d) noexcept : ptr(p), deleter(std::move(d)) {}

  ~unique_ptr() { reset(); }

  // 移动构造
  unique_ptr(unique_ptr&& other) noexcept
      : ptr(other.ptr), deleter(std::move(other.deleter)) {
    other.ptr = nullptr;
  }

  // 禁用拷贝
  unique_ptr(const unique_ptr&) = delete;
  unique_ptr& operator=(const unique_ptr&) = delete;

  // 移动赋值
  unique_ptr& operator=(unique_ptr&& other) noexcept {
    if (this != &other) {
      reset(other.release());
      deleter = std::move(other.deleter);
    }
    return *this;
  }

  // 释放所有权
  T* release() noexcept {
    T* p = ptr;
    ptr = nullptr;
    return p;
  }

  // 重置指针
  void reset(T* p = nullptr) noexcept {
    if (ptr != p) {
      deleter(ptr);
      ptr = p;
    }
  }

  // 数组下标访问
  T& operator[](size_t idx) const { return ptr[idx]; }

  // 其他接口与主模板一致
  T* get() const noexcept { return ptr; }
  explicit operator bool() const noexcept { return ptr != nullptr; }
  void swap(unique_ptr& other) noexcept {
    using std::swap;
    swap(ptr, other.ptr);
    swap(deleter, other.deleter);
  }
  Deleter& get_deleter() noexcept { return deleter; }
  const Deleter& get_deleter() const noexcept { return deleter; }

 private:
  T* ptr;
  Deleter deleter;
};

// 工厂函数
template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
  return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// 数组版本工厂
template <typename T>
unique_ptr<T[]> make_unique(size_t size) {
  return unique_ptr<T[]>(new T[size]);
}

// 删除器示例
class Deletor {
 public:
  template <typename U>
  void operator()(U* p) noexcept {
    if (p) {
      delete p;
    }
  }
};

int main()
{
  return 0;
}