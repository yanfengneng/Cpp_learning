#include <iostream>
using namespace std;
 
class Student;
class Person
{
public:
    friend void Print(const Person& p, const Student& s);
    string _name;// 姓名
};
 
class Student :public Person
{
    // 由于友元关系不能被继承，因此需要在派生类中重新声明一下友元关系。若不声明则会报错
    friend void Print(const Person& p, const Student& s);
protected:
    int _stuNum;// 学号
};
 
void Print(const Person& p, const Student& s)
{
    cout << p._name << endl;
    cout << s._stuNum << endl; //在派生类中声明过后，就会编译通过
}
 
int main()
{
    Person p;
    Student s;
    Print(p, s);
    return 0;
}