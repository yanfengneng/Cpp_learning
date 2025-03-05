#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

template <class T>
class Compare {
 public:
  static bool IsEqual(const T& a, const T& b) {
    std::cout << "in the general class..." << std::endl;
    return a == b;
  }
};

// 全特化
template <>
class Compare<double> {
 public:
  static bool IsEqual(const double& a, const double& b) {
    std::cout << "in the double class..." << std::endl;
    return std::fabs(a - b) < 0.00001;
  }
};

template <>
class Compare<const char*> {
 public:
  static bool IsEqual(const char* a, const char* b) {
    std::cout << "in the char* class..." << std::endl;
    return std::strcmp(a, b) == 0;
  }
};

template <class T>
class Compare<T*> {
 public:
  static bool IsEqual(const T* lh, const T* rh) {
    return Compare<T>::IsEqual(*lh, *rh);
  }
};

template <class T>
class Compare<std::vector<T>> {
 public:
  static bool IsEqual(const std::vector<T>& lh, const std::vector<T>& rh) {
    if (lh.size() != rh.size()) {
      return false;
    }
    for (size_t i = 0; i < lh.size(); ++i) {
      if (!Compare<T>::IsEqual(lh[i], rh[i])) {
        return false;
      }
    }
    return true;
  }
};

// specialize for any template class type
template <class T1>
struct SpecializedType {
  T1 x1;
  T1 x2;
};
template <class T>
class Compare<SpecializedType<T>> {
 public:
  static bool IsEqual(const SpecializedType<T>& lh,
                      const SpecializedType<T>& rh) {
    return Compare<T>::IsEqual(lh.x1 + lh.x2, rh.x1 + rh.x2);
  }
};

int main() {
  Compare<int> c1;
  std::cout << c1.IsEqual(1, 2) << std::endl;
  std::cout << c1.IsEqual(1, 1) << std::endl;

  Compare<double> c2;
  std::cout << c2.IsEqual(1.0, 1.0) << std::endl;
  std::cout << c2.IsEqual(1.0, 1.1) << std::endl;

  Compare<const char*> c3;
  std::cout << c3.IsEqual("hello", "world") << std::endl;
  std::cout << c3.IsEqual("hello", "hello") << std::endl;

  Compare<int*> c4;
  int a = 1, b = 2;
  std::cout << c4.IsEqual(&a, &b) << std::endl;
  std::cout << c4.IsEqual(&a, &a) << std::endl;

  Compare<std::vector<int>> c5;
  std::vector<int> v1 = {1, 2, 3};
  std::vector<int> v2 = {1, 2, 3};

  std::cout << c5.IsEqual(v1, v2) << std::endl;
  std::vector<int> v3 = {1, 2, 4};
  std::cout << c5.IsEqual(v1, v3) << std::endl;

  return 0;
}
