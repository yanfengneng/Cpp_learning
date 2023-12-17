#include <iostream>
using namespace std;

class Person //成人
{
public:
    virtual ~Person() { cout << "~Person()" << endl; }
};

class Student : public Person //学生
{
public:
    virtual ~Student() override{ cout << "~Student" << endl; }
};

class A
{
public:
    virtual void func(int val = 1){ std::cout<<"A->"<< val <<std::endl;}
    virtual void test(){ func();}
};

class B : public A
{
public:
    void func(int val=0){ std::cout<<"B->"<< val <<std::endl; }
};

int main()
{
    B *b = new B();
    b->test();
    // Person *p1 = new Person();
    // Person *p2 = new Student();
    // delete p1;
    // delete p2;
    return 0;
}
