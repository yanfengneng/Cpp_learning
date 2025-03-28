#include <cstring>
#include <iostream>
#include <stdexcept>

class String {
 private:
  char* data_;
  size_t len_;
  size_t capacity_;

  // 确保当前 String 有足够多的容量来存储新数据
  void ensure_capacity(size_t new_cap) {
    if (new_cap > capacity_) {  // 新容量大于当前容量
      // 初始化扩容值
      size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
      // 扩容值小于新容量，则进行翻倍
      while (new_capacity < new_cap) {
        new_capacity *= 2;
      }
      // 申请新的容量
      char* new_data = new char[new_capacity + 1];
      if (data_) {  // data_ 存在数据，则进行拷贝，并释放原有数据内存
        strcpy(new_data, data_);
        delete[] data_;
      }
      data_ = new_data;          // 指向相同的地址，更新指针
      capacity_ = new_capacity;  // 更新容量
    }
  }

 public:
  String() : data_(nullptr), len_(0), capacity_(0) {}

  String(const char* s) : data_(nullptr), len_(0), capacity_(0) {
    if (s) {
      len_ = strlen(s);  // 更新长度
      // 申请 data_ 的内存空间与更新 capacity_
      ensure_capacity(len_);
      strcpy(data_, s);
    }
  }

  // 拷贝构造函数：深拷贝
  // 类的成员函数（包括拷贝赋值运算符）在类的作用域内，可以访问​任何同类对象
  // 的私有成员，无论这些对象是当前实例（this）还是其他实例（如参数 other）
  String(const String& other) : data_(nullptr), len_(other.len_), capacity_(0) {
    // 申请 data_ 的内存空间与更新 capacity_
    ensure_capacity(len_);
    // 更新 data_ 内容
    strcpy(data_, other.data_);
  }

  // 移动构造函数：直接接管 other 管理对象的内存空间，同时将 other 清空
  String(String&& other) noexcept
      : data_(other.data_), len_(other.len_), capacity_(other.capacity_) {
    // 将源对象置为空状态
    other.capacity_ = 0, other.len_ = 0, other.data_ = nullptr;
  }

  ~String() { delete[] data_; }

  // 拷贝赋值运算符
  String& operator=(const String& other) {
    if (this != &other) {
      // 申请 data_ 的内存空间与更新 capacity_
      ensure_capacity(other.len_);
      // 更新 data_ 的内容
      strcpy(data_, other.data_);
      // 更新 len_ 的长度
      len_ = other.len_;
    }
    return *this;
  }

  // 移动赋值运算符
  String& operator=(String&& other) noexcept {
    if (this != &other) {
      // 释放原有对象的内存空间
      delete[] data_;
      // 获得 other 管理对象的使用权
      data_ = other.data_, len_ = other.len_, capacity_ = other.capacity_;
      // 将 other 对象置为空状态
      other.data_ = nullptr, other.len_ = 0, other.capacity_ = 0;
    }
    return *this;
  }

  void push_back(char c) {
    // 确定 len_ + 1 空间是否够，不够则申请新的 data_ 与 capacity_
    ensure_capacity(len_ + 1);
    data_[len_++] = c;
    data_[len_] = '\0';
  }

  void pop_back() {
    if (len_ == 0) throw std::out_of_range("String is empty");
    data_[--len_] = '\0';
  }

  char& front() {
    if (len_ == 0) throw std::out_of_range("String is empty");
    return data_[0];
  }

  char& back() {
    if (len_ == 0) throw std::out_of_range("String is empty");
    // 不能返回局部变量的引用，不然在函数调用结束后，局部变量被销毁，引用失效
    // 局部变量，不能作为引用返回值
    // char c = data[0];
    // return c;
    return data_[len_ - 1];
  }

  // 返回 const 引用，禁止修改
  const char& front() const {
    if (len_ == 0) throw std::out_of_range("String is empty");
    return data_[0];
  }

  const char& back() const {
    if (len_ == 0) throw std::out_of_range("String is empty");
    return data_[len_ - 1];
  }

  size_t size() const { return len_; }

  size_t capacity() const { return capacity_; }

  bool empty() const { return len_ == 0; }

  void clear() {
    len_ = 0;
    if (data_) data_[0] = '\0';
  }

  // 返回引用是为了支持链式操作，连等于
  String& operator+=(const String& other) {
    // 确定 len_ + other.len_ 空间是否够，不够则申请新的 data_ 与 capacity_
    ensure_capacity(len_ + other.len_);
    // 拼接字符串
    strcat(data_, other.data_);
    len_ += other.len_;
    return *this;
  }

  // 添加友元运算符重载
  friend std::ostream& operator<<(std::ostream& os, const String& str) {
    os << (str.data_ ? str.data_ : "");
    return os;
  }

  const char* c_str() const { return data_ ? data_ : ""; }
};

int main() {
  String s("Hello, ");
  s.push_back('w');
  s += "orld";
  s.push_back('!');
  std::cout << "s contains: '" << s.c_str() << "' with length " << s.size()
            << std::endl;

  s.pop_back();
  std::cout << "After pop_back, s contains: '" << s.c_str() << "' with length "
            << s.size() << std::endl;

  std::cout << "Front of s: '" << s.front() << "'" << std::endl;
  std::cout << "Back of s: '" << s.back() << "'" << std::endl;

  char c = s.back();  // 拷贝构造
  c = '!';            // 修改的是临时变量，原数据并未改变
  std::cout << s << std::endl;

  char& c1 = s.back();  // 引用s[len_-1]
  c1 = 'D';             // 修改原数据
  std::cout << s << std::endl;
  return 0;
}
