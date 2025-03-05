#include <iostream>
#include <unordered_set>
using namespace std;

class Person {
 private:
  string firstname;
  string lastname;
  int age;
  friend class Hasher;
  friend void operator<<(ostream& os, const Person& p);

 public:
  Person() {}
  Person(string fn, string ln, int a) : firstname(fn), lastname(ln), age(a) {}
  // 重载==运算符
  bool operator==(const Person& p) const {
    return (firstname == p.firstname) && (lastname == p.lastname) &&
           (age == p.age);
  }
};

// 重载 << 运算符
void operator<<(ostream& os, const Person& p)  
{
  os << p.firstname << " " << p.lastname << " " << p.age << endl;
}

// hash仿函数，用来得到 hash code
class Hasher { 
 public:
  size_t operator()(const Person& p) const {
    return hash<string>()(p.firstname) + hash<string>()(p.lastname) +
           hash<int>()(p.age);
  }
};

int main() {
  unordered_set<Person, Hasher> uset;
  uset.insert(Person("a", "a", 10));
  uset.insert(Person("b", "b", 11));
  uset.insert(Person("c", "c", 12));
  uset.insert(Person("d", "d", 13));
  uset.insert(Person("e", "e", 14));
  for (Person p : uset) {
    cout << p;
  }
  return 0;
}
