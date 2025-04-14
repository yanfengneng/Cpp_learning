#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

class Person {
 private:
  string firstname;
  string lastname;
  int age;
  friend class Hasher;

 public:
  Person() {}
  Person(string fn, string ln, int a) : firstname(fn), lastname(ln), age(a) {}
  // 重载==运算符
  bool operator==(const Person& p) const {
    return (firstname == p.firstname) && (lastname == p.lastname) &&
           (age == p.age);
  }
};

template <typename T>
void hashCombine(size_t& seed, const T& arg)  // 真正的hash在这里完成
{
  // 这里虽然也用到了标准库提供的hash函数，但是后面可以添加自己的一些数据（甚至hash<T>()(arg)操作也可以有我们自己来做）
  // 不同用户在这里可以有不同的数，只要能够将原始数据尽可能打乱即可
  // 0x9e3779b9涉及到数学中的黄金比例，实际上并不需要一定是这个数
  seed ^= hash<T>()(arg) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename T>
void hashValue(size_t& seed, const T& arg)  // 递归出口
{
  hashCombine(seed, arg);
}

template <typename T1, typename... T2>
void hashValue(
    size_t& seed, const T1& arg,
    const T2&... args)  // 在这里通过递归逐步拿到所有参数,当args...的大小为1时跳出该递归，接着进入③
{
  hashCombine(seed, arg);
  hashValue(seed, args...);  // 递归
}

// T为模板参数包，可以代表任意多个类型；args为函数参数包，可以代表任意多个函数参数
template <typename... T>
size_t hashValue(const T&... args)  // 在这里完成参数的第一次拆分，接着进入②
{
  size_t seed = 0;           // 种子，以引用方式传递
  hashValue(seed, args...);  // args...中为T类型对象中的所有用于hash的数据成员
  return seed;
}

class Hasher {  // hash函数
 public:
  size_t operator()(const Person& p) const {
    return hashValue(p.firstname, p.lastname, p.age);
  }
};

int main() {
  unordered_set<Person, Hasher> uset;
  uset.insert(Person("a", "a", 10));
  uset.insert(Person("a", "a", 10));
  uset.insert(Person("c", "c", 12));
  uset.insert(Person("d", "d", 13));
  uset.insert(Person("e", "e", 14));
  for (int i = 0; i < uset.bucket_count(); i++) {
    cout << "bucket " << i << " has " << uset.bucket_size(i) << " elements"
         << endl;
  }
  return 0;
}
