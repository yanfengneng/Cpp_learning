#include <initializer_list>
#include <iostream>
#include <stdexcept>

template <typename T>
class MyVector {
 private:
  T* data;          // 动态数组指针
  size_t capacity;  // 当前容量
  size_t size;      // 当前元素数量

  void resize(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < size; ++i) {
      new_data[i] = std::move(data[i]);
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
  }

 public:
  // 构造函数
  MyVector() : data(nullptr), capacity(0), size(0) {}

  MyVector(size_t initial_size) : capacity(initial_size), size(initial_size) {
    data = new T[capacity];
  }

  MyVector(std::initializer_list<T> init_list)
      : capacity(init_list.size()), size(init_list.size()) {
    data = new T[capacity];
    std::copy(init_list.begin(), init_list.end(), data);
  }

  // 拷贝构造函数
  MyVector(const MyVector& other) : capacity(other.capacity), size(other.size) {
    data = new T[capacity];
    std::copy(other.data, other.data + size, data);
  }

  // 移动构造函数
  MyVector(MyVector&& other) noexcept
      : data(other.data), capacity(other.capacity), size(other.size) {
    other.data = nullptr;
    other.capacity = 0;
    other.size = 0;
  }

  // 赋值操作符
  MyVector& operator=(const MyVector& other) {
    if (this != &other) {
      delete[] data;
      capacity = other.capacity;
      size = other.size;
      data = new T[capacity];
      std::copy(other.data, other.data + size, data);
    }
    return *this;
  }

  // 移动赋值操作符
  MyVector& operator=(MyVector&& other) noexcept {
    if (this != &other) {
      delete[] data;
      data = other.data;
      capacity = other.capacity;
      size = other.size;
      other.data = nullptr;
      other.capacity = 0;
      other.size = 0;
    }
    return *this;
  }

  // 析构函数
  ~MyVector() { delete[] data; }

  // 元素访问
  T& operator[](size_t index) {
    if (index >= size) {
      throw std::out_of_range("Index out of bounds");
    }
    return data[index];
  }

  const T& operator[](size_t index) const {
    if (index >= size) {
      throw std::out_of_range("Index out of bounds");
    }
    return data[index];
  }

  T& at(size_t index) {
    if (index >= size) {
      throw std::out_of_range("Index out of bounds");
    }
    return data[index];
  }

  const T& at(size_t index) const {
    if (index >= size) {
      throw std::out_of_range("Index out of bounds");
    }
    return data[index];
  }

  T& front() {
    if (size == 0) {
      throw std::out_of_range("Vector is empty");
    }
    return data[0];
  }

  T& back() {
    if (size == 0) {
      throw std::out_of_range("Vector is empty");
    }
    return data[size - 1];
  }

  // 插入元素
  void push_back(const T& value) {
    if (size == capacity) {
      resize(capacity == 0 ? 1 : 2 * capacity);
    }
    data[size++] = value;
  }

  void push_back(T&& value) {
    if (size == capacity) {
      resize(capacity == 0 ? 1 : 2 * capacity);
    }
    data[size++] = std::move(value);
  }

  // 删除元素
  void pop_back() {
    if (size == 0) {
      throw std::out_of_range("Vector is empty");
    }
    --size;
  }

  // 插入指定位置的元素
  void insert(size_t index, const T& value) {
    if (index > size) {
      throw std::out_of_range("Index out of bounds");
    }
    if (size == capacity) {
      resize(capacity == 0 ? 1 : 2 * capacity);
    }
    for (size_t i = size; i > index; --i) {
      data[i] = std::move(data[i - 1]);
    }
    data[index] = value;
    ++size;
  }

  // 删除指定位置的元素
  void erase(size_t index) {
    if (index >= size) {
      throw std::out_of_range("Index out of bounds");
    }
    for (size_t i = index; i < size - 1; ++i) {
      data[i] = std::move(data[i + 1]);
    }
    --size;
  }

  // 清空向量
  void clear() { size = 0; }

  // 获取当前大小和容量
  size_t get_size() const { return size; }

  size_t get_capacity() const { return capacity; }

  bool empty() const { return size == 0; }

  // 迭代器类
  class Iterator {
   private:
    T* ptr;

   public:
    Iterator(T* p) : ptr(p) {}
    T& operator*() { return *ptr; }
    Iterator& operator++() {
      ++ptr;
      return *this;
    }
    Iterator operator++(int) {
      Iterator temp = *this;
      ++ptr;
      return temp;
    }
    bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
  };

  Iterator begin() { return Iterator(data); }

  Iterator end() { return Iterator(data + size); }
};

/*
https://blog.csdn.net/Z_Stand/article/details/106866871
*/
int main() {
  MyVector<int> vec = {1, 2, 3, 4, 5};

  vec.push_back(6);
  vec.insert(2, 10);
  vec.erase(4);

  for (int value : vec) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  return 0;
}
