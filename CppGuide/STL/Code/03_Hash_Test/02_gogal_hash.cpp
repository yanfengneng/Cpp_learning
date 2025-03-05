#include <iostream>
#include <unordered_set>
using namespace std;

class Person {
 private:
  string firstname;
  string lastname;
  int age;
  friend size_t hasher(const Person& p);

 public:
  Person() {}
  Person(string fn, string ln, int a) : firstname(fn), lastname(ln), age(a) {}
  // 重载 operator ==
  bool operator==(const Person& p) const {
    return (firstname == p.firstname) && (lastname == p.lastname) &&
           (age == p.age);
  }
};

size_t hasher(const Person& p) {  // hash函数，得到hash码
  return hash<string>()(p.firstname) + hash<string>()(p.lastname) +
         hash<int>()(p.age);
}

int main() {
  unordered_set<Person, decltype(&hasher)> uset(
      3, hasher);  // 3为初始化元素个数
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
