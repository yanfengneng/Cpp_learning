#include <iostream>
#include <string>
using namespace std;

template <typename T1, typename T2>
class Pair {
 public:
  T1 key;
  T2 value;
  Pair(T1 k, T2 v) : key(k), value(v) {}
  bool operator<(const Pair<T1, T2>& p) const;
  T2 get_value(T1 k);
};

template <typename T1, typename T2>
bool Pair<T1, T2>::operator<(const Pair<T1, T2>& p) const {
  return key < p.key;
}

template <typename T1, typename T2>
T2 Pair<T1, T2>::get_value(T1 k) {
  if (k == this->key) {
    return this->value;
  } else {
    return T2();
  }
}

template <class T1>                // 定义新类型T1
class A
{
public:
    template <class T2>             // 定义新类型T2
    void Func(T2 t) { cout << t << endl; }  // 成员函数模板
};

template <class T>
void f(){ T d; }

template <>
void f<int>(){ int d; }

int main() {
  // A<int> a;  // 定义类A的对象a
  // a.Func<float>(1.1);  // 调用成员函数模板
  // a.Func<string>("hello");

  // Pair<string, int> p1("bob", 25);
  // Pair<string, int> p2("alice", 13);
  // cout << (p1 < p2) << endl;
  // cout << p1.get_value("bob") << endl;
  // cout << p1.get_value("alice") << endl;
  // cout << p1.get_value("charlie") << endl;
  return 0;
}