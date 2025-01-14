#include <cstring>
#include <iostream>
#include <stdexcept>

class MyString {
 private:
  char* data_;
  size_t len_;
  size_t capacity_;

  void ensure_capacity(size_t new_cap) {
    if (new_cap > capacity_) {
      size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
      while (new_capacity < new_cap) {
        new_capacity *= 2;
      }
      char* new_data = new char[new_capacity + 1];
      if (data_) {
        strcpy(new_data, data_);
        delete[] data_;
      }
      data_ = new_data;
      capacity_ = new_capacity;
    }
  }

 public:
  MyString() : data_(nullptr), len_(0), capacity_(0) {}

  MyString(const char* s) : data_(nullptr), len_(0), capacity_(0) {
    if (s) {
      len_ = strlen(s);
      ensure_capacity(len_);
      strcpy(data_, s);
    }
  }

  MyString(const MyString& other) : data_(nullptr), len_(other.len_), capacity_(0) {
    ensure_capacity(other.len_);
    strcpy(data_, other.data_);
  }

  MyString(MyString&& other) noexcept
      : data_(other.data_), len_(other.len_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.len_ = 0;
    other.capacity_ = 0;
  }

  ~MyString() { delete[] data_; }

  MyString& operator=(const MyString& other) {
    if (this != &other) {
      ensure_capacity(other.len_);
      strcpy(data_, other.data_);
      len_ = other.len_;
    }
    return *this;
  }

  MyString& operator=(MyString&& other) noexcept {
    if (this != &other) {
      delete[] data_;
      data_ = other.data_;
      len_ = other.len_;
      capacity_ = other.capacity_;
      other.data_ = nullptr;
      other.len_ = 0;
      other.capacity_ = 0;
    }
    return *this;
  }

  void push_back(char c) {
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
    return data_[len_ - 1];
  }

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

  MyString& operator+=(const MyString& other) {
    ensure_capacity(len_ + other.len_);
    strcat(data_, other.data_);
    len_ += other.len_;
    return *this;
  }

  const char* c_str() const { return data_ ? data_ : ""; }
};

int main() {
  MyString s("Hello, ");
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

  return 0;
}
