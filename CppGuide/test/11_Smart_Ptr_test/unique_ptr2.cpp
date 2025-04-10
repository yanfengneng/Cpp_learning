#include <utility>
#include <iostream>

// 默认删除器
template <typename T>
struct default_delete {
  void operator()(T* p) const { delete p; }
};

template <typename T, typename Deleter = default_delete<T>>
class Unique_Ptr {
 private:
  T* ptr_;
  Deleter deleter;

 public:
  // 构造函数，接收原始指针和删除器，同时防止隐式转换
  explicit Unique_Ptr(T* ptr = nullptr, Deleter d = Deleter())
      : ptr_(ptr), deleter(std::move(d)) {}

  // 禁止拷贝
  Unique_Ptr(const Unique_Ptr& other) = delete;
  Unique_Ptr& operator=(const Unique_Ptr& other) = delete;

  // 移动构造函数
  Unique_Ptr(Unique_Ptr&& other)
      : ptr_(other.ptr_), deleter(std::move(other.deleter)) {
    other.ptr_ = nullptr;
  }

  // 移动赋值运算符函数
  Unique_Ptr& operator=(Unique_Ptr&& other) {
    if (this != &other) {
      // 先释放当前指针管理的对象
      reset();
      // 进行资源转移
      ptr_ = other.ptr_, deleter = std::move(other.deleter);
      // 制空原对象
      other.ptr_ = nullptr;
    }
    return *this;
  }

  // 析构函数
  ~Unique_Ptr() { reset(); }

  // 重置资源
  void reset(T* p = nullptr) noexcept {
    if (ptr_) {
      deleter(ptr_);
    }
    ptr_ = p;
  }

  // 释放资源所有权，返回原始指针
  T* release() noexcept {
    T* temp = ptr_;
    ptr_ = nullptr;
    return temp;
  }

  // 交换两个 Unique_Ptr
  void swap(Unique_Ptr& other) noexcept {
    using std::swap;
    swap(ptr_, other.ptr_);
    swap(deleter, other.deleter);
  }

  // 获取原始指针
  T* get() const noexcept { return ptr_; }

  // 获得删除器
  Deleter& get_deleter() noexcept { return deleter; }
  const Deleter& get_deleter() const noexcept { return deleter; }

  // 解引用运算符
  T& operator*() const noexcept { return *ptr_; }

  // 成员访问运算符
  T* operator->() const noexcept { return ptr_; }

  // 显示布尔转换
  explicit operator bool() const noexcept { return ptr_ != nullptr; }
};

// make_unique 函数
// template <typename T, typename... Args>
// Unique_Ptr<T> make_unique(Args&&... args) {
//   return Unique_Ptr<T>(new T(std::forward<Args>(args)...));
// }
template <typename T, typename... Args>
Unique_Ptr<T> make_unique(Args&&... args) {
  return Unique_Ptr<T>(new T(std::forward<Args>(args)...));
}

// 全局 swap 特化
namespace std {
template <typename T, typename Deleter>
void swap(Unique_Ptr<T, Deleter>& a, Unique_Ptr<T, Deleter>& b) noexcept {
  a.swap(b);
}
}  // namespace std

// 自定义删除器示例
struct FileDeleter {
  void operator()(FILE* fp) const {
    if (fp) {
      fclose(fp);
      std::cout << "File closed.\n";
    }
  }
};

int main() {
  // 使用默认删除器
  Unique_Ptr<int> ptr = make_unique<int>(42);
  std::cout << *ptr << "\n";  // 输出: 42

  // 移动语义
  Unique_Ptr<int> ptr2 = std::move(ptr);
  std::cout << (ptr ? "non-null" : "null") << "\n";  // 输出: null
  std::cout << *ptr2 << "\n";                        // 输出: 42

  // 自定义删除器
  FILE* fp = fopen("test.txt", "w");
  Unique_Ptr<FILE, FileDeleter> file_ptr(fp, FileDeleter());
  // 文件在 file_ptr 析构时自动关闭

  return 0;
}
