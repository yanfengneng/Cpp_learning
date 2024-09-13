#include <bits/stdc++.h>

template <typename T>
class UniquePtr {
 public:
  explicit UniquePtr(T* ptr = nullptr) : ptr_(ptr) {}

  // 禁用拷贝构造函数
  UniquePtr(const UniquePtr&) = delete;

  // 禁用拷贝赋值运算符
  UniquePtr& operator=(const UniquePtr&) = delete;

  // 移动构造函数
  UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  // 移动赋值运算符
  UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  // 重载 * 操作符
  T& operator*() const { return *ptr_; }

  // 重载 -> 操作符
  T& operator->() const { return ptr_; }

  // 判断是否为空
  explicit operator bool() const {
    return ptr_ != nullptr;
  }  // 使用 explicit 关键字

  T* get() const { return ptr_; }

  // 释放控制的指针并返回
  T* release() {
    T* temp = ptr_;
    ptr_ = nullptr;
    return temp;
  }

  // 交换指针
  void swap(UniquePtr& other) noexcept { std::swap(ptr_, other.ptr_); }

  // 重置指针
  void reset(T* ptr = nullptr) {
    delete ptr_;
    ptr_ = ptr;
  }

  ~UniquePtr() { delete ptr_; }

 private:
  T* ptr_;
};

template <typename T>
class SharedPtr {
 public:
  // 构造函数，接受一个原生指针
  explicit SharedPtr(T* ptr = nullptr) : ptr_(ptr) {
    if (ptr_) {
      ref_count_ = new size_t(1);
    }
  }

  // 拷贝构造函数
  SharedPtr(const SharedPtr& other)
      : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    if (ptr_) {
      ++(*ref_count_);
    }
  }

  // 拷贝赋值运算符
  SharedPtr& operator=(const SharedPtr& other) {
    if (this != &other) {
      release();
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      if (ptr_) {
        ++(*ref_count_);
      }
    }
    return *this;
  }

  // 移动构造函数
  SharedPtr(SharedPtr&& other) noexcept
      : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    other.ptr_ = nullptr;
    other.ref_count_ = nullptr;
  }

  // 移动赋值运算符
  SharedPtr& operator=(const SharedPtr&& other) noexcept {
    if (this != &other) {
      release();
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      other.ptr_ = nullptr;
      other.ref_count_ = nullptr;
    }
    return *this;
  }

  // 拷贝赋值运算符，能传一个空指针
  SharedPtr& operator=(std::nullptr_t) {
    release();
    ptr_ = nullptr;
    ref_count_ = nullptr;
    return *this;
  }

  T& operator*() const { return *ptr_; }
  T* operator->() const { return ptr_; }
  explicit operator bool() const { return ptr_ != nullptr; }
  size_t use_count() const { return ref_count_ ? *ref_count_ : 0; }

  // 获取原生指针
  T* get() const { return ptr_; }

  // 交换指针
  void swap(SharedPtr& other) noexcept {
    std::swap(ptr_, other.ptr_);
    std::swap(ref_count_, other.ref_count_);
  }

  // 重置指针
  void reset(T* ptr = nullptr) {
    release();
    if (ptr) {
      ptr_ = ptr;
      ref_count_ = new size_t(1);
    }
  }

  ~SharedPtr() { release(); }

 private:
  void release() {
    if (ref_count_ && --(*ref_count_) == 0) {
      delete ptr_;
      delete ref_count_;
    }
  }
  T* ptr_ = nullptr;
  size_t* ref_count_ = nullptr;
};

int main() {
  UniquePtr<int> uptr1(new int(10));
  std::cout << *uptr1 << std::endl;  // 输出 10

  UniquePtr<int> uptr2 = std::move(uptr1);  // 转移所有权
  if (!uptr1) {
    std::cout << "uptr1 is empty" << std::endl;
  }
  std::cout << *uptr2 << std::endl;  // 输出 10

  SharedPtr<int> sptr1(new int(20));
  SharedPtr<int> sptr2 = sptr1;  // 共享所有权

  std::cout << "sptr1 use count: " << sptr1.use_count() << std::endl;  // 输出 2
  std::cout << "sptr2 use count: " << sptr2.use_count() << std::endl;  // 输出 2

  sptr1 = nullptr;  // 释放 sptr1
  std::cout << "sptr2 use count: " << sptr2.use_count() << std::endl;  // 输出 1

  std::cout << *sptr2 << std::endl;  // 输出 20
  return 0;
}
