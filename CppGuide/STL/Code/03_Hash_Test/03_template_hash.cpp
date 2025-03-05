#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

class Person {
 private:
  string firstname;
  string lastname;
  int age;
  friend class hash<Person>;

 public:
  Person() {}
  Person(string fn, string ln, int a) : firstname(fn), lastname(ln), age(a) {}
  // 重载==运算符
  bool operator==(const Person& p) const {
    return (firstname == p.firstname) && (lastname == p.lastname) &&
           (age == p.age);
  }
};

// 偏特化（这里使用了标准库已经提供的hash偏特化类hash<string>，hash<int>()）
namespace std {
template <>
struct hash<Person> {
 public:
  size_t operator()(const Person& p) const {
    return hash<string>()(p.firstname) + hash<string>()(p.lastname) +
           hash<int>()(p.age);
  }
};
}  // namespace std

int main() {
  unordered_set<Person> uset;
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
