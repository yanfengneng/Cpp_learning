#include <functional>  // For std::function
#include <iostream>
#include <utility>  // For std::move and std::swap

template <typename T>
class SharedPtr {
 public:
  // 构造函数，默认构造空指针
  explicit SharedPtr(T* ptr = nullptr)
      : ptr_(ptr), control_block_(ptr ? new ControlBlock(ptr) : nullptr) {}

  // 带自定义删除器的构造函数
  template <typename Deleter>
  SharedPtr(T* ptr, Deleter del)
      : ptr_(ptr), control_block_(new ControlBlock(ptr, std::move(del))) {}

  // 拷贝构造函数
  SharedPtr(const SharedPtr& other)
      : ptr_(other.ptr_), control_block_(other.control_block_) {
    if (control_block_) {
      control_block_->add_ref();
    }
  }

  // 拷贝赋值运算符
  SharedPtr& operator=(const SharedPtr& other) {
    if (this != &other) {
      release();
      ptr_ = other.ptr_;
      control_block_ = other.control_block_;
      if (control_block_) {
        control_block_->add_ref();
      }
    }
    return *this;
  }

  // 移动构造函数
  SharedPtr(SharedPtr&& other) noexcept
      : ptr_(other.ptr_), control_block_(other.control_block_) {
    other.ptr_ = nullptr;
    other.control_block_ = nullptr;
  }

  // 移动赋值运算符
  SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
      release();
      ptr_ = other.ptr_;
      control_block_ = other.control_block_;
      other.ptr_ = nullptr;
      other.control_block_ = nullptr;
    }
    return *this;
  }

  // 析构函数
  ~SharedPtr() { release(); }

  // 重载 * 操作符
  T& operator*() const { return *ptr_; }

  // 重载 -> 操作符
  T* operator->() const { return ptr_; }

  // 返回内部指针
  T* get() const { return ptr_; }

  // 获取当前引用计数
  size_t use_count() const {
    return control_block_ ? control_block_->get_ref_count() : 0;
  }

  // 判断指针是否为空
  explicit operator bool() const { return ptr_ != nullptr; }

  // 交换两个 shared_ptr 对象
  void swap(SharedPtr& other) noexcept {
    std::swap(ptr_, other.ptr_);
    std::swap(control_block_, other.control_block_);
  }

  // 重置指针，并更新管理的对象
  void reset(T* ptr = nullptr) {
    release();
    if (ptr) {
      ptr_ = ptr;
      control_block_ = new ControlBlock(ptr);
    }
  }

  // 重置指针并使用自定义删除器
  template <typename Deleter>
  void reset(T* ptr, Deleter del) {
    release();
    if (ptr) {
      ptr_ = ptr;
      control_block_ = new ControlBlock(ptr, std::move(del));
    }
  }

 private:
  // 控制块结构，负责引用计数和删除管理
  struct ControlBlock {
    T* ptr_;
    size_t ref_count_;
    std::function<void(T*)> deleter_;

    // 默认构造
    explicit ControlBlock(T* ptr)
        : ptr_(ptr), ref_count_(1), deleter_([](T* ptr) { delete ptr; }) {}

    // 自定义删除器的构造
    template <typename Deleter>
    ControlBlock(T* ptr, Deleter del)
        : ptr_(ptr), ref_count_(1), deleter_(std::move(del)) {}

    void add_ref() { ++ref_count_; }

    void release_ref() {
      if (--ref_count_ == 0) {
        deleter_(ptr_);
        delete this;
      }
    }

    size_t get_ref_count() const { return ref_count_; }
  };

  T* ptr_ = nullptr;                       // 管理的对象指针
  ControlBlock* control_block_ = nullptr;  // 控制块指针

  // 释放当前管理的对象
  void release() {
    if (control_block_) {
      control_block_->release_ref();
    }
    ptr_ = nullptr;
    control_block_ = nullptr;
  }
};

// 测试代码
int main() {
  // 使用默认删除器的 shared_ptr
  SharedPtr<int> sp1(new int(42));
  std::cout << "sp1 use count: " << sp1.use_count() << std::endl;
  std::cout << "sp1 value: " << *sp1 << std::endl;

  // 拷贝构造 shared_ptr
  SharedPtr<int> sp2 = sp1;
  std::cout << "sp1 use count: " << sp1.use_count() << std::endl;
  std::cout << "sp2 use count: " << sp2.use_count() << std::endl;

  // 使用自定义删除器的 shared_ptr
  SharedPtr<int> sp3(new int(100), [](int* ptr) {
    std::cout << "Custom deleter called for " << *ptr << std::endl;
    delete ptr;
  });
  std::cout << "sp3 value: " << *sp3 << std::endl;

  // 移动构造 shared_ptr
  SharedPtr<int> sp4 = std::move(sp3);
  std::cout << "sp4 value: " << *sp4 << std::endl;

  return 0;
}
